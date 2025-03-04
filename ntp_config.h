#ifndef NTP_CONFIG_H
#define NTP_CONFIG_H

/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

typedef struct NTP_T_
{
    ip_addr_t ntp_server_address;
    bool dns_request_sent;
    struct udp_pcb *ntp_pcb;
    absolute_time_t ntp_test_time;
    alarm_id_t ntp_resend_alarm;
} NTP_T;

#define NTP_SERVER "a.st1.ntp.br"
#define NTP_MSG_LEN 48
#define NTP_PORT 123
#define NTP_DELTA 2208988800 // seconds between 1 Jan 1900 and 1 Jan 1970
#define NTP_TEST_TIME (30 * 1000)
#define NTP_RESEND_TIME (2 * 1000)

static time_t ntp_received_time = 0; // Variável global para armazenar o tempo recebido

// Called with results of operation
static void ntp_result(NTP_T *state, int status, time_t *result)
{
    if (status == 0 && result)
    {
        time_t local_time = *result - (3 * 3600);
        
        struct tm *utc = gmtime(&local_time);
        
        printf("got ntp response: %02d/%02d/%04d %02d:%02d:%02d\n", utc->tm_mday, utc->tm_mon + 1, utc->tm_year + 1900,
               utc->tm_hour, utc->tm_min, utc->tm_sec);
    }

    if (state->ntp_resend_alarm > 0)
    {
        cancel_alarm(state->ntp_resend_alarm);
        state->ntp_resend_alarm = 0;
    }
    state->ntp_test_time = make_timeout_time_ms(NTP_TEST_TIME);
    state->dns_request_sent = false;
}

static int64_t ntp_failed_handler(alarm_id_t id, void *user_data);

// Make an NTP request
static void ntp_request(NTP_T *state)
{
    // cyw43_arch_lwip_begin/end should be used around calls into lwIP to ensure correct locking.
    // You can omit them if you are in a callback from lwIP. Note that when using pico_cyw_arch_poll
    // these calls are a no-op and can be omitted, but it is a good practice to use them in
    // case you switch the cyw43_arch type later.
    cyw43_arch_lwip_begin();
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, NTP_MSG_LEN, PBUF_RAM);
    uint8_t *req = (uint8_t *)p->payload;
    memset(req, 0, NTP_MSG_LEN);
    req[0] = 0x1b;
    udp_sendto(state->ntp_pcb, p, &state->ntp_server_address, NTP_PORT);
    pbuf_free(p);
    cyw43_arch_lwip_end();
}

static int64_t ntp_failed_handler(alarm_id_t id, void *user_data)
{
    NTP_T *state = (NTP_T *)user_data;
    printf("ntp request failed\n");
    ntp_result(state, -1, NULL);
    return 0;
}

// Call back with a DNS result
static void ntp_dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg)
{
    NTP_T *state = (NTP_T *)arg;
    if (ipaddr)
    {
        state->ntp_server_address = *ipaddr;
        printf("ntp address %s\n", ipaddr_ntoa(ipaddr));
        ntp_request(state);
    }
    else
    {
        printf("ntp dns request failed\n");
        ntp_result(state, -1, NULL);
    }
}

// NTP data received
static void ntp_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port) {
    NTP_T *state = (NTP_T *)arg;
    uint8_t mode = pbuf_get_at(p, 0) & 0x7;
    uint8_t stratum = pbuf_get_at(p, 1);

    // Verifica o resultado
    if (ip_addr_cmp(addr, &state->ntp_server_address) && port == NTP_PORT && p->tot_len == NTP_MSG_LEN &&
        mode == 0x4 && stratum != 0) {
        uint8_t seconds_buf[4] = {0};
        pbuf_copy_partial(p, seconds_buf, sizeof(seconds_buf), 40);
        uint32_t seconds_since_1900 = seconds_buf[0] << 24 | seconds_buf[1] << 16 | seconds_buf[2] << 8 | seconds_buf[3];
        uint32_t seconds_since_1970 = seconds_since_1900 - NTP_DELTA;
        ntp_received_time = seconds_since_1970; // Armazena o tempo recebido

        ntp_result(state, 0, &ntp_received_time);
    } else {
        printf("Resposta NTP inválida\n");
        ntp_result(state, -1, NULL);
    }
    pbuf_free(p);
}

// Perform initialisation
static NTP_T *ntp_init(void)
{
    NTP_T *state = (NTP_T *)calloc(1, sizeof(NTP_T));
    if (!state)
    {
        printf("failed to allocate state\n");
        return NULL;
    }
    state->ntp_pcb = udp_new_ip_type(IPADDR_TYPE_ANY);
    if (!state->ntp_pcb)
    {
        printf("failed to create pcb\n");
        free(state); // Libera memória antes de retornar
        return NULL;
    }
    udp_recv(state->ntp_pcb, ntp_recv, state);
    return state;
}

// Executa o teste NTP uma única vez
void run_ntp_test(void)
{
    NTP_T *state = ntp_init();
    if (!state)
        return;

    // Configura o alarme para reenvio em caso de falha
    state->ntp_resend_alarm = add_alarm_in_ms(NTP_RESEND_TIME, ntp_failed_handler, state, true);

    // Faz a requisição DNS para o servidor NTP
    cyw43_arch_lwip_begin();
    int err = dns_gethostbyname(NTP_SERVER, &state->ntp_server_address, ntp_dns_found, state);
    cyw43_arch_lwip_end();

    state->dns_request_sent = true;
    if (err == ERR_OK)
    {
        ntp_request(state); // Requisição direta se o DNS estiver em cache
    }
    else if (err != ERR_INPROGRESS)
    {
        printf("dns request failed\n");
        ntp_result(state, -1, NULL);
    }

    // Aguarda a resposta do NTP (não entra em loop infinito)
#if PICO_CYW43_ARCH_POLL
    while (state->dns_request_sent)
    {
        cyw43_arch_poll();
    }
#else
    // Se não estiver usando pico_cyw43_arch_poll, aguarda um tempo suficiente para a resposta
    sleep_ms(5000); // Aguarda 5 segundos para a resposta
#endif

    // Libera recursos
    if (state->ntp_pcb)
    {
        udp_remove(state->ntp_pcb);
    }
    free(state);
    state = NULL;
}

int get_ntp_hour(void) {
    if (ntp_received_time == 0) {
        return -1; // Retorna -1 se o tempo ainda não foi recebido
    }

    // Ajusta o fuso horário (subtrai 3 horas para o horário de Brasília)
    time_t local_time = ntp_received_time - (3 * 3600);

    // Converte o tempo para uma estrutura tm
    struct tm *utc = gmtime(&local_time);

    // Retorna a hora
    return utc->tm_hour;
}

int get_ntp_minute(void) {
    if (ntp_received_time == 0) {
        return -1; // Retorna -1 se o tempo ainda não foi recebido
    }

    // Ajusta o fuso horário (subtrai 3 horas para o horário de Brasília)
    time_t local_time = ntp_received_time - (3 * 3600);

    // Converte o tempo para uma estrutura tm
    struct tm *utc = gmtime(&local_time);

    // Retorna os minutos
    return utc->tm_min;
}


#endif
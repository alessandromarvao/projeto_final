#ifndef NTP_CONFIG_H
#define NTP_CONFIG_H

#include <time.h>
#include "pico/stdlib.h"
#include "lwip/udp.h"
#include "lwip/dns.h"

// Definições do NTP
#define NTP_SERVER "pool.ntp.org"
#define NTP_PORT 123
#define NTP_MSG_LEN 48
#define NTP_DELTA 2208988800U
#define NTP_TEST_INTERVAL_MS (30 * 1000) // 30 segundos entre requisições

// Estrutura do cliente NTP
typedef struct {
    ip_addr_t ntp_server_address;
    bool dns_request_sent;
    struct udp_pcb *ntp_pcb;
    absolute_time_t next_ntp_request;
    alarm_id_t ntp_resend_alarm;
} ntp_client_t;

// Função para iniciar a sincronização NTP
void ntp_start();

#endif // NTP_CONFIG_H

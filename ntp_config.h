#include "pico/stdlib.h"
#include "cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "time.h"

#define NTP_SERVER "pool.ntp.org"
#define NTP_PORT 123
#define NTP_DELTA 2208988800UL
#define BRAZIL_FORTALEZA_TIMEZONE_OFFSET (-3 * 3600) // UTC-3, ou seja, -3 horas (em segundos)

void set_time_from_ntp()
{
    struct sockaddr_in server_addr;
    int sockfd;
    char buffer[48] = {0};

    // Preenche o pacote NTP
    buffer[0] = 0x1B;

    // Cria o socket UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0)
    {
        printf("Erro ao criar socket!\n");
        return;
    }

    // Configura o endereço do servidor NTP
    struct hostent *he = gethostbyname(NTP_SERVER);
    if (he == NULL)
    {
        printf("Erro ao resolver nome do servidor NTP\n");
        close(sockfd);
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(NTP_PORT);
    memcpy(&server_addr.sin_addr, he->h_addr, he->h_length);

    // Envia o pedido NTP
    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Erro ao enviar o pedido NTP\n");
        close(sockfd);
        return;
    }

    // Recebe a resposta NTP
    if (recv(sockfd, buffer, sizeof(buffer), 0) < 0)
    {
        printf("Erro ao receber resposta NTP\n");
        close(sockfd);
        return;
    }

    // Fecha o socket
    close(sockfd);

    // Obtém o timestamp NTP da resposta
    unsigned long long ntp_time = 0;
    ntp_time = ((unsigned long long)buffer[43] << 24) | ((unsigned long long)buffer[42] << 16) |
               ((unsigned long long)buffer[41] << 8) | (unsigned long long)buffer[40];

    // Converte para hora Unix
    ntp_time -= NTP_DELTA;

    // Ajusta para o fuso horário de Fortaleza (UTC-3)
    ntp_time += BRAZIL_FORTALEZA_TIMEZONE_OFFSET;

    // Converte o timestamp para a estrutura de tempo
    struct tm *tm_info;
    tm_info = gmtime((time_t *)&ntp_time);

    // Configura o RTC com a hora obtida
    set_time(tm_info);
}

void set_time(struct tm *tm_info)
{
    // Aqui você deve configurar o RTC do Raspberry Pi Pico com a hora obtida
    // O Pico SDK não possui suporte direto para RTC, então você pode configurar o relógio de software se necessário.
    // Isso depende do ambiente que você está usando para configurar o relógio (RTC externo ou RTC de software).
    // Aqui, você pode apenas exibir a data/hora para verificação.

    printf("Data e Hora ajustada para Fortaleza (UTC-3): %d-%d-%d %d:%d:%d\n", tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
}

#include <stdio.h>
#include "pico/stdlib.h"

// Biblioteca que exibe as imagens na matriz de LED RGB
#include "neopixel.h"
// Biblioteca de configuração e acesso à rede sem fio
#include "wifi_config.h"
// Biblioteca de configuração e acesso ao servidor NTP
#include "ntp_config.h"
// biblioteca responsável pelo gerenciamento do temporizador
#include "config_timer.h"

// Estado do temporizador (ligado ou deslgado)
static const bool timer_on = false;

// Configuração do botão A no pino 5
static const uint BTN_A_PIN = 5;
// Configuração do botão B no pino 6
static const uint BTN_B_PIN = 6;

// Estado atual do botão A
bool btn_A_state = false;
// Estado anterior do botão A
volatile bool last_btn_A_state = false;

// Estado atual do botão A
bool btn_B_state = false;
// Estado anterior do botão A
volatile bool last_btn_B_state = false;

static void init_button(uint gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
}

/**
 * Função que é acionada assim que o botão A for pressionado
 */
void btn_callback(uint gpio, uint32_t events)
{
    if (events & GPIO_IRQ_EDGE_RISE)
    {
        // Faça aqui o seu código
        if (!last_btn_A_state && btn_A_state)
        {
            btn_A_state = !gpio_get(BTN_A_PIN);
            printf("Botão A pressionado.\n");
        }
        else if (!last_btn_B_state && btn_B_state)
        {
            btn_B_state = !gpio_get(BTN_B_PIN);
            printf("Botão B pressionado.\n");
        }
    }
}

/**
 * Função que verifica o estado da conexão com o Wi-Fi.
 * Se houver conexão estabelecida: Exibe o relógio analógico com o horário extraído do servidor NTP
 * Se não houver conexão: Exibe um efeito de fogueira ou chuva
 * @param is_connected boolean indicando se a conexão está estabelecida
 * @return runtime Velocidade do efeito apresentado na matriz de LED
 */
int init_led_matrix(bool is_connected)
{
    int runtime = 50;

    if (is_connected)
    {
        run_ntp_test();

        // Ajusta o tempo de contagem para 30 segundos
        runtime = 30 * 1000;

        int hora = get_ntp_hour();
        int minuto = get_ntp_minute();

        if (hora != -1 && minuto != -1)
        {
            display_analogic_watch(hora, minuto);
        }
    }
    else
    {
        display_rain_screen();
    }

    return runtime;
}

// Função de IRQ quando os botões A ou B forem pressionados
void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    init_button(BTN_A_PIN);
    init_button(BTN_B_PIN);

    display_splash_screen();
    
    display_embarcatech();

    // Estado da conexão com o Wi-Fi
    bool is_wifi_connected = false;

    is_wifi_connected = wifi_config();

    sleep_ms(10);

    while (true)
    {
        int runtime;
        // Exibe as horas apenas quando o temporizador estiver desligado.
        if (!timer_on)
        {
            runtime = init_led_matrix(is_wifi_connected);
        }

        // Verificação das interrupções
        tight_loop_contents();

        sleep_ms(runtime);
    }
}

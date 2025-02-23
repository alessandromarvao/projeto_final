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
            // printf("Botão A pressionado.\n");
        }
        else if (!last_btn_B_state && btn_B_state)
        {
            btn_B_state = !gpio_get(BTN_B_PIN);
            // printf("Botão B pressionado.\n");
        }
    }
}

int main()
{
    stdio_init_all();

    init_button(BTN_A_PIN);
    init_button(BTN_B_PIN);

    display_splash_screen();

    wifi_config();

    sleep_ms(10);

    // Função de callback
    void gpio_irq_handler(uint gpio, uint32_t events)
    {

        if (gpio == BTN_A_PIN)
        {
            printf("Estado do botão A: %s\n", btn_A_state ? "ligado" : "desligado");
            printf("Último estado registrado do botão A: %s\n", last_btn_A_state ? "ligado" : "desligado");
            // printf("Pressionou o botão A\n");
            
            btn_A_state = !gpio_get(BTN_A_PIN);
            
            if (!last_btn_A_state && btn_A_state)
            {
            }
            // Atualiza o estado anterior do botão para o próximo ciclo
            last_btn_A_state = btn_A_state;
        }

        if (gpio == BTN_B_PIN)
        {
            printf("Estado do botão B: %s\n", btn_B_state ? "ligado" : "desligado");
            printf("Último estado registrado do botão B: %s\n", last_btn_B_state ? "ligado" : "desligado");
            // printf("Pressionou o botão B\n");
            
            btn_B_state = !gpio_get(BTN_B_PIN);
            
            if (!last_btn_B_state && btn_B_state)
            {
            }
            last_btn_B_state = btn_B_state;
        }
    }

    gpio_set_irq_enabled_with_callback(BTN_A_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BTN_B_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_irq_handler);

    while (true)
    {
        int runtime;
        // Exibe as horas apenas quando o temporizador estiver desligado.
        if (!timer_on)
        {
            run_ntp_test();

            // Reduz o tempo de contagem para 30 segundos para pegar o valor mais exato
            runtime = 30 * 1000;

            int hora = get_ntp_hour();
            int minuto = get_ntp_minute();

            if (hora != -1 && minuto != -1)
            {
                display_analogic_watch(hora, minuto);
            }
        }

        // Verificação das interrupções
        tight_loop_contents();

        sleep_ms(runtime);
    }
}

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Biblioteca que exibe as imagens na matriz de LED RGB
#include "neopixel.h"
// Biblioteca de configuração e acesso à rede sem fio
#include "wifi_config.h"
// Biblioteca de configuração e acesso ao servidor NTP
#include "ntp_config.h"
// biblioteca responsável pelo gerenciamento do temporizador
#include "config_timer.h"

// Configuração do temporizador para 25 minutos de estudo e 5 minutos de descanso
#define TIMER_STUDY 25 * 60 * 1000 // 25 minutos em milissegundos
#define TIMER_REST 5 * 60 * 1000   // 5 minutos em milissegundos
// Configuração do total de ciclos de estudo e descanso
#define TOTAL_CICLOS 4
// Valor inicial do ciclo
static int ciclo_atual = 0;

// Estado do temporizador (ligado ou deslgado)
static bool timer_on = false;

// Configuração do botão A no pino 5
static const uint BTN_A_PIN = 5;
// Configuração do botão B no pino 6
static const uint BTN_B_PIN = 6;

// Estado atual do botão A
bool btn_A_state = false;
// Estado anterior do botão A
volatile bool last_btn_A_state = false;

static void init_button(uint gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
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
        for (int i = 0; i < 15; i++)
        {
            display_rain_screen();
        }
        for (int i = 0; i < 15; i++)
        {
            display_fire_2_screen();
        }
    }

    return runtime;
}


/**
 * Função de temporizador para os 25 minutos de estudo.
 */
int64_t study_timer_callback(alarm_id_t id, void *user_data)
{
    timer_on = true;
    int timer = 510;

    display_mario_clothes_counter(timer);

    // Após os 25 minutos, inicia o período de descanso
    return TIMER_REST; // Retorna o tempo do descanso para agendar automaticamente
}

/**
 * Função de temporizador para os 5 minutos de descanso.
 */
int64_t rest_timer_callback(alarm_id_t id, void *user_data)
{
    timer_on = true;
    int timer = 102;

    display_pokebola_counter(timer);

    ciclo_atual++;

    if (ciclo_atual < TOTAL_CICLOS)
    {
        // Se ainda não completamos os ciclos, inicia um novo período de estudo
        return TIMER_STUDY;
    }
    else
    {
        // Se os 4 ciclos foram concluídos, desativa o temporizador
        timer_on = false;
        ciclo_atual = 0;
        return 0; // Retorna 0 para encerrar a sequência de alarmes
    }
}

// Função de IRQ quando os botões A ou B forem pressionados
void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    init_button(BTN_A_PIN);
    init_button(BTN_B_PIN);

    display_splash_screen();

    // Estado da conexão com o Wi-Fi
    bool is_wifi_connected = false;

    // Recebe o status da conexão com a rede Wi-Fi
    is_wifi_connected = wifi_config();

    // Tempo de espera para não sobrecarregar o processador
    sleep_ms(10);

    // Ativa a interrupção para o botão B (detecção de borda de descida)
    gpio_set_irq_enabled_with_callback(BTN_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true)
    {
        // Tempo de execução do efeito na matriz de LED
        int runtime;

        // Exibe as horas apenas quando o temporizador estiver desligado.
        if (!timer_on)
        {
            // Inicializa a matriz de LED de acordo com o estado da conexão com a rede Wi-Fi
            runtime = init_led_matrix(is_wifi_connected);
        }

        btn_A_state = !gpio_get(BTN_A_PIN);

        if (!last_btn_A_state && btn_A_state)
        {
            printf("Botão A pressionado. Iniciando o contador\n");

            ciclo_atual = 0; // Reset do contador de ciclos
            add_alarm_in_ms(TIMER_STUDY, study_timer_callback, NULL, false);
        }

        sleep_ms(runtime);
    }
}

// Função de callback
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Interrompe o temporizador
}

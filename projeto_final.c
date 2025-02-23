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

// Valor inicial do ciclo
static int ciclo_atual = 0;
// Configuração do total de ciclos de estudo e descanso
static const int TOTAL_CICLOS = 4;

// Estado do temporizador (ligado ou deslgado)
static bool timer_on = false;

// Configuração do botão A no pino 5
static const uint BTN_A_PIN = 5;
// Configuração do botão B no pino 6
static const uint BTN_B_PIN = 6;

// Variável para armazenar a tela de estudo a ser apresentada na matriz de LED
static uint study_screen = 0;

// Tempo das apresentações para os temporizadores de estudo e descanso
static int presentation_time = 0;

// Variável para armazenar o ID do alarme de estudo (para uso da interrupção do temporizador)
static alarm_id_t study_alarm_id;
// Variável para armazenar o ID do alarme de descanso (para uso da interrupção do temporizador)
static alarm_id_t rest_alarm_id;

/**
 * Inicializa e configura o botão selecionado como resistor de pull-up
 * @param gpio Pino do botão
 */
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
    // Todo: informar a interrupção do temporizador
    printf("Alarme de 25 minutos concluído! Descanse um pouco.\n");
    // Marca o tempo atual (que atingiu os 25 minutos)
    uint32_t init_time = to_ms_since_boot(get_absolute_time());

    while (true)
    {
        uint32_t time_now = to_ms_since_boot(get_absolute_time());

        if (time_now - init_time >= TIMER_REST){
            break;
        }

        display_rain_screen();
    }
    
    /*

    // Confere se já concluiu o total de ciclos de estudo
    if (ciclo_atual < TOTAL_CICLOS)
    {
        // Inicia o temporizador de descanso
        // rest_alarm_id = add_alarm_in_ms(TIMER_REST, rest_timer_callback, NULL, false);

        // apresentação da tela de descanso

        display_rain_screen();

        // Incrementa o ciclo atual
        ciclo_atual++;
    }
    else
    {
        printf("Ciclo de estudo finalizado\n");
        ciclo_atual = 0;
    }
    */
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

    // Ativa a interrupção para o botão A (detecção de borda de descida)
    gpio_set_irq_enabled_with_callback(BTN_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

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

        sleep_ms(runtime);
    }

    return 0;
}

// Função de callback
void gpio_irq_handler(uint gpio, uint32_t events)
{
    if (gpio == BTN_A_PIN)
    {
        if (!timer_on)
        {
            printf("Botão A pressionado. Iniciando a contagem de 25 minutos\n");

            study_alarm_id = add_alarm_in_ms(TIMER_STUDY, study_timer_callback, NULL, false);

            // Altera o estado do temporizador para ligado
            timer_on = true;
        }
    }
    else if (gpio == BTN_B_PIN)
    {

        // Garante que o botão A não seja pressionado novamente antes de ser liberado
        if (timer_on)
        {
            // Inicia o temporizador/
            printf("Botão B pressionado. Interrompendo o contador\n");

            // Cancela o alarme de estudo e descanso
            if (study_alarm_id != 0)
            {
                cancel_alarm(study_alarm_id);
            }

            // Cancela o alarme de descanso
            if (rest_alarm_id != 0)
            {
                cancel_alarm(rest_alarm_id);
            }

            timer_on = false;
        }
    }
}

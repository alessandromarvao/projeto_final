#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"

// Biblioteca que exibe as imagens na matriz de LED RGB
#include "neopixel.h"
// Biblioteca de configuração e acesso à rede sem fio
#include "wifi_config.h"
// Biblioteca de configuração e acesso ao servidor NTP
#include "ntp_config.h"
// biblioteca responsável pelo gerenciamento do temporizador
#include "config_timer.h"
#include "buzzer_config.h"

#define STUDY_TIMER 500
#define REST_TIMER 100

// Configuração do total de ciclos de estudo e descanso
#define STUDY_CYCLE 4
// Valor atual do ciclo (inicia em 0)
static int cycle = 0;

// Estado do temporizador (ligado ou deslgado)
static volatile bool timer_on = false;
int runtime;

// Configuração do botão A no pino 5
static const uint BTN_A_PIN = 5;
// Configuração do botão B no pino 6
static const uint BTN_B_PIN = 6;

// Estado atual do botão A
bool btn_A_state = false;
// Estado anterior do botão A
volatile bool btn_A_last_state = false;

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
    // Tempo de sincronização com o servidor NTP: 2 segundos
    runtime = 2 * 1000;

    if (is_connected)
    {
        run_ntp_test();

        // Ajusta o tempo de contagem para 30 segundos
        runtime = 1 * 1000;

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

void display_timer_animation(int time_ms)
{
    // Gera um número aleatório entre 0 e 5
    srand(time(NULL));
    int random_number = rand() % 7;

    switch (random_number)
    {
    case 0:
        display_iron_man_counter(time_ms);
        break;
    case 2:
        display_kirby_counter(time_ms);
        break;
    case 3:
        display_luighi_counter(time_ms);
        break;
    case 4:
        display_mario_clothes_counter(time_ms);
        break;
    case 5:
        display_pikachu_counter(time_ms);
    default:
        display_pokebola_counter(time_ms);
    }
}

void core1_entry()
{
    uint32_t action;

    action = multicore_fifo_pop_blocking();

    // iniciar conexão wireless e sincronização com servidor NTP
    if (action == 1)
    {
        printf("Apresentando Splash Screen...\n");
        display_splash_screen();
    }
    else if (action == 2)
    { // Tocar música enquanto apresenta animação na matriz de led
        
        display_timer_animation(REST_TIMER);
    }
    while (1)
        tight_loop_contents();
}

// Função de IRQ quando os botões A ou B forem pressionados
void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    init_button(BTN_A_PIN);
    init_button(BTN_B_PIN);
    pwm_init_buzzer(BUZZER_PIN_2);

    // Inicializando o core1
    multicore_launch_core1(core1_entry);
    // Enviando instrução para o core1
    multicore_fifo_push_blocking(1);

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
        runtime = 10;

        // Exibe as horas apenas quando o temporizador estiver desligado.
        if (!timer_on)
        {
            // Inicializa a matriz de LED de acordo com o estado da conexão com a rede Wi-Fi
            runtime = init_led_matrix(is_wifi_connected);
        }

        btn_A_state = !gpio_get(BTN_A_PIN);

        if (!btn_A_last_state && btn_A_state)
        {
            // Altera o estado do temporizador para ligado
            timer_on = true;

            printf("Botão A pressionado. Iniciando o contador\n");

            // Reset do contador de ciclos
            cycle = 0;
        }

        btn_A_last_state = btn_A_state;

        // Inicia os ciclos de estudos
        while (timer_on && (cycle < STUDY_CYCLE))
        {
            if (cycle == 0)
            {
                printf("Iniciando o temporizador. Bons estudos!\n");
            }
            else
            {
                printf("Ciclo %d de %d.\n", cycle, STUDY_CYCLE);
            }

            // Executa as apresentações durante o tempo de descanso
            display_timer_animation(STUDY_TIMER);

            // Apaga a matriz de LED
            turn_off();

            // Alerta sonoro para início do tempo de repouso
            play_song();

            // Só executa o tempo de descanso até o penúltimo ciclo de estudo
            // (não faz sentido marcar o tempo de descanso depois que terminar os estudos)
            if (cycle < 3)
            {
                printf("Ciclo de estudo concluído, descanse um pouco.\n");

                // Enviando instrução para o core1
                multicore_fifo_push_blocking(2);

                // Alerta sonoro para retorno do estudo
                play_alarm();
            }

            // Apaga a matriz de LED
            turn_off();

            cycle++;
        }

        // Garante que o ciclo de estudos esteja desligado
        timer_on = false;

        cycle = 0;

        sleep_ms(runtime);
    }
}

// Função de callback
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Interrompe o temporizador
    printf("Botão B pressionado. Interrompendo o contador\n");
    timer_on = false;
}

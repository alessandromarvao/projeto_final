#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "neopixel.h"
#include "ntp_config.h"
#include "wifi_config.h"
#include "buzzer_config.h"

// Configurações atualizadas
#define STUDY_TIMER 25 * 60 * 1000 // 25 minutos em microssegundos
#define REST_TIMER 5 * 60 * 1000   // 5 minutos em microssegundos
#define TOTAL_STUDY_SESSIONS 4     // 4 sessões de estudo
#define TOTAL_REST_SESSIONS 3      // 3 sessões de descanso
#define BTN_A_PIN 5
#define BTN_B_PIN 6
#define DEBOUNCE_MS 50

// Estados do sistema
typedef enum
{
    STATE_IDLE,
    STATE_STUDY,
    STATE_REST
} timer_state_t;

// Variáveis compartilhadas
static volatile bool button_pressed = false;
static volatile bool should_stop = false;

// Contexto do timer
static struct
{
    timer_state_t state;
    absolute_time_t start_time;
    uint8_t study_count;
    uint8_t rest_count;
    uint32_t duration;
} timer_ctx;

void init_hardware();
void handle_buttons();
void update_display();
void start_study_session();
void start_rest_session();
void stop_timer();
void gpio_irq_handler(uint gpio, uint32_t events);

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
        printf("Apresentando sprites...\n");
        int random_number = (rand() % 2) + 1; // Gera um número aleatório entre 1 e 2

        if (random_number == 1)
        {
            for (int i = 0; i < 10; i++)
            {
                display_fire_2_screen();
            }
        }
        else
        {
            for (int i = 0; i < 10; i++)
            {
                display_rain_screen();
            }
        }
    }
    while (1)
        tight_loop_contents();
}

int main()
{
    stdio_init_all();
    init_hardware();
    // Inicializando o core1
    multicore_launch_core1(core1_entry);
    // Enviando instrução para o core1
    multicore_fifo_push_blocking(1);

    bool wifi_connected = wifi_config();
    
    sleep_ms(4500);

    while (true)
    {
        if (wifi_connected)
        {
            run_ntp_test();
        }
        else
        {
            display_fire_2_screen();
        }
        handle_buttons();
        update_display();
        sleep_ms(10);
    }
}

void init_hardware()
{
    gpio_init(BTN_A_PIN);
    gpio_init(BTN_B_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);
    gpio_pull_up(BTN_B_PIN);

    gpio_set_irq_enabled_with_callback(BTN_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BTN_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    timer_ctx.state = STATE_IDLE;
    timer_ctx.study_count = 0;
    timer_ctx.rest_count = 0;
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    static absolute_time_t last_press = 0;

    if (absolute_time_diff_us(last_press, get_absolute_time()) < DEBOUNCE_MS * 1000)
    {
        return;
    }
    last_press = get_absolute_time();

    if (gpio == BTN_A_PIN)
    {
        button_pressed = true;
    }
    else if (gpio == BTN_B_PIN)
    {
        should_stop = true;
    }
}

void handle_buttons()
{
    static absolute_time_t last_update = 0;

    if (!button_pressed ||
        absolute_time_diff_us(last_update, get_absolute_time()) < DEBOUNCE_MS * 1000)
    {
        return;
    }

    button_pressed = false;
    last_update = get_absolute_time();

    if (timer_ctx.state == STATE_IDLE)
    {
        timer_ctx.study_count = 0;
        timer_ctx.rest_count = 0;
        start_study_session();
    }
}

void start_study_session()
{
    timer_ctx.state = STATE_STUDY;
    timer_ctx.start_time = get_absolute_time();
    timer_ctx.duration = STUDY_TIMER;
    timer_ctx.study_count++;
    printf("Iniciando estudo %d/%d\n", timer_ctx.study_count, TOTAL_STUDY_SESSIONS);
}

void start_rest_session()
{
    timer_ctx.state = STATE_REST;
    timer_ctx.start_time = get_absolute_time();
    timer_ctx.duration = REST_TIMER;
    timer_ctx.rest_count++;
    printf("Iniciando descanso %d/%d\n", timer_ctx.rest_count, TOTAL_REST_SESSIONS);
}

void stop_timer()
{
    timer_ctx.state = STATE_IDLE;
    should_stop = false;
    printf("Timer finalizado!\n");
}

void update_display()
{
    static absolute_time_t last_display_update = 0;

    if (absolute_time_diff_us(last_display_update, get_absolute_time()) < 100000)
    {
        return;
    }
    last_display_update = get_absolute_time();

    if (should_stop)
    {
        stop_timer();
        return;
    }

    switch (timer_ctx.state)
    {
    case STATE_IDLE:
        display_analogic_watch(get_ntp_hour(), get_ntp_minute());
        break;

    case STATE_STUDY:
    {
        int64_t elapsed = absolute_time_diff_us(timer_ctx.start_time, get_absolute_time());

        srand(time(NULL));                    // Inicializa a semente com o tempo atual
        int random_number = (rand() % 2) + 1; // Gera um número aleatório entre 1 e 2

        if (random_number == 1)
        {
            display_mario_clothes_counter(5);
        }
        else
        {
            display_pokebola_counter(5);
        }

        if (timer_ctx.study_count < TOTAL_STUDY_SESSIONS)
        {

            if (timer_ctx.rest_count < TOTAL_REST_SESSIONS)
            {
                // Enviando instrução para o core1
                multicore_fifo_push_blocking(2);
                play_song();
                display_number_screen(timer_ctx.rest_count);

                start_rest_session();
            }
            else
            {
                stop_timer();
            }
        }
        else
        {
            stop_timer();
        }

        // Atualizar display do estudo
        break;
    }

    case STATE_REST:
    {
        int64_t elapsed = absolute_time_diff_us(timer_ctx.start_time, get_absolute_time());

        if (elapsed >= timer_ctx.duration)
        {
            if (timer_ctx.study_count < TOTAL_STUDY_SESSIONS)
            {
                start_study_session();
            }
            else
            {
                stop_timer();
            }
        }
        // Atualizar display do descanso
        break;
    }
    }
}
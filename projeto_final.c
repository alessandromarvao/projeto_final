#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "neopixel.h"
#include "wifi_config.h"
#include "ntp_config.h"

// Configurações
#define STUDY_TIMER 10 * 1000000  // 25 minutos em microssegundos
#define REST_TIMER  5 * 1000000   // 5 minutos em microssegundos
#define TOTAL_CICLOS 4
#define BTN_A_PIN 5
#define BTN_B_PIN 6
#define DEBOUNCE_MS 50

// Estados do sistema
typedef enum {
    STATE_IDLE,
    STATE_STUDY,
    STATE_REST
} timer_state_t;

// Variáveis compartilhadas (volatile para acesso atômico)
static volatile bool timer_on = false;
static volatile bool should_stop = false;
static volatile bool button_pressed = false;

// Contexto do timer
static struct {
    timer_state_t state;
    absolute_time_t start_time;
    uint8_t current_cycle;
    uint32_t duration;
} timer_ctx;

// Protótipos de funções
void init_hardware();
void handle_buttons();
void update_display();
void start_study_session();
void start_rest_session();
void stop_timer();
void gpio_irq_handler(uint gpio, uint32_t events);

int main() {
    stdio_init_all();
    init_hardware();
    display_splash_screen();

    // Inicialização do WiFi
    bool wifi_connected = wifi_config();
    if(wifi_connected) {
        run_ntp_test();
    }

    // Loop principal
    while(true) {
        handle_buttons();
        update_display();
        sleep_ms(10);
    }
}

void init_hardware() {
    // Configuração dos botões
    gpio_init(BTN_A_PIN);
    gpio_init(BTN_B_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);
    gpio_pull_up(BTN_B_PIN);

    // Configuração de interrupções
    gpio_set_irq_enabled_with_callback(BTN_A_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BTN_B_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    // Inicialização do contexto do timer
    timer_ctx.state = STATE_IDLE;
    timer_ctx.current_cycle = 0;
}

void gpio_irq_handler(uint gpio, uint32_t events) {
    static absolute_time_t last_press = 0;
    
    // Debounce simples
    if(absolute_time_diff_us(last_press, get_absolute_time()) < DEBOUNCE_MS * 1000) {
        return;
    }
    last_press = get_absolute_time();

    if(gpio == BTN_A_PIN) {
        button_pressed = true;
    } else if(gpio == BTN_B_PIN) {
        should_stop = true;
    }
}

void handle_buttons() {
    static absolute_time_t last_update = 0;
    
    if(!button_pressed || 
       absolute_time_diff_us(last_update, get_absolute_time()) < DEBOUNCE_MS * 1000) {
        return;
    }

    button_pressed = false;
    last_update = get_absolute_time();

    if(timer_ctx.state == STATE_IDLE) {
        start_study_session();
    }
}

void start_study_session() {
    timer_ctx.state = STATE_STUDY;
    timer_ctx.start_time = get_absolute_time();
    timer_ctx.duration = STUDY_TIMER;
    timer_ctx.current_cycle = 0;
    printf("Study session started\n");
}

void start_rest_session() {
    timer_ctx.state = STATE_REST;
    timer_ctx.start_time = get_absolute_time();
    timer_ctx.duration = REST_TIMER;
    printf("Rest session started\n");
}

void stop_timer() {
    timer_ctx.state = STATE_IDLE;
    should_stop = false;
    printf("Timer stopped\n");
}

void update_display() {
    static absolute_time_t last_display_update = 0;
    
    // Atualização do display a cada 100ms
    if(absolute_time_diff_us(last_display_update, get_absolute_time()) < 100000) {
        return;
    }
    last_display_update = get_absolute_time();

    // Lógica do timer
    if(should_stop) {
        stop_timer();
    }

    switch(timer_ctx.state) {
        case STATE_IDLE:
            display_analogic_watch(get_ntp_hour(), get_ntp_minute());
            break;

        case STATE_STUDY: {
            int64_t elapsed = absolute_time_diff_us(timer_ctx.start_time, get_absolute_time());
            if(elapsed >= timer_ctx.duration || should_stop) {
                if(++timer_ctx.current_cycle >= TOTAL_CICLOS) {
                    stop_timer();
                } else {
                    start_rest_session();
                }
            }
            // Atualizar display do timer de estudo
            break;
        }

        case STATE_REST: {
            int64_t elapsed = absolute_time_diff_us(timer_ctx.start_time, get_absolute_time());
            if(elapsed >= timer_ctx.duration || should_stop) {
                start_study_session();
            }
            // Atualizar display do timer de descanso
            break;
        }
    }
}
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

// Configuração do temporizador para 25 minutos de estudo e 5 minutos de descanso
#define TIMER_STUDY 25 * 60 * 1000 // 25 minutos em milissegundos
#define TIMER_REST 5 * 60 * 1000    // 5 minutos em milissegundos

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
        for (int i = 0; i < 15; i++) {
            display_rain_screen();
        }
        for (int i = 0; i < 15; i++) {
            display_fire_2_screen();
        }
    }

    return runtime;
}

/**
 * Função de temporizador para os 25 minutos de estudo
 * @param id Identificador do alarme
 * @param user_data Dados do usuário
 * @return bool Retorna verdadeiro se o temporizador estiver ativo
 */
bool study_timer_callback(alarm_id_t id, void *user_data)
{
    // Ativa o temporizador
    timer_on = true;
    // Inicializa o contador das apresentações
    int apresentacao = 0;
    // Inicializa o tempo de contagem
    int timer = 510;

    switch (apresentacao)
    {
    // Apresentação do contador do Super Mario
    case 0:
        display_mario_clothes_counter();
        apresentacao++;
        break;
    // Apresentação do contador da pokebola  
    default:
        display_pokebola_counter();
        apresentacao = 0;
        break;
    }
}

/**
 * Função de temporizador para os 5 minutos de descanso
 */
void rest_timer_callback(uint gpio, uint32_t events)
{
    // Ativa o temporizador
    timer_on = true;
    // Inicializa o contador das apresentações
    int apresentacao = 0;
    // Inicializa o tempo de contagem (102 ms para o total de 5 minutos)
    int timer = 102;

    switch (apresentacao)
    {
    // Apresentação do contador do Super Mario
    case 0:
        display_mario_clothes_counter();
        apresentacao++;
        break;
    // Apresentação do contador da pokebola  
    default:
        display_pokebola_counter();
        apresentacao = 0;
        break;
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
    
    display_embarcatech();

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
            // Contagem de 4 ciclos de estudo e descanso
            for (int i = 0; i < 4; i++)
            {
                // Aciona o temporizador de 25 minutos para estudo
                add_alarm_in_ms(TIMER_STUDY, study_timer_callback, NULL, false);
                // Aciona o temporizador de 5 minutos para descanso
                add_alarm_in_ms(TIMER_REST, rest_timer_callback, NULL, false);
            }
        }

        sleep_ms(runtime);
    }
}

// Função de callback
void gpio_irq_handler(uint gpio, uint32_t events)
{    
    // Interrompe o temporizador
}

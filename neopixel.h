#ifndef NEOPIXEL_H
#define NEOPIXEL_H


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

// Biblioteca que gera um array de elementos RGB contendo todos os sprites a serem configurados na matriz de led
#include "sprites/splash_screen.h"
#include "sprites/super_mario.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição das GPIOs dos botões A e B
#define BTN_A 5 // Quando apertado, inicia ou para o contador
#define BTN_B 6 // Para o alarme

// Variável que indica se está no tempo de repouso
bool rest = false;
// Variável que indica se está no tempo de estudar (O contador começa com os 25 minutos para estudar e depois 5 minutos para repousar)
bool study = true;
// Variável que indica se o temporizador está ligado ou não
bool timer_on = false;

// Definição de pixel GRB
struct pixel_t
{
    uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin)
{

    // Cria programa PIO.
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    // Toma posse de uma máquina PIO.
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0)
    {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
    }

    // Inicia programa na máquina PIO obtida.
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

    // Limpa buffer de pixels.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear()
{
    for (uint i = 0; i < LED_COUNT; ++i)
        npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite()
{
    // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        // Aplica o brilho de 30% aos valores de cor antes de enviá-los.
        // 0.77
        // 0.55 muito forte
        // 0.33 forte
        // 0.22 bonm
        // 0.66
        // 0.44
        // 0.88
        uint8_t r = leds[i].R * 0.66;
        uint8_t g = leds[i].G * 0.66;
        uint8_t b = leds[i].B * 0.66;

        // Envia os valores ajustados ao PIO
        pio_sm_put_blocking(np_pio, sm, g);
        pio_sm_put_blocking(np_pio, sm, r);
        pio_sm_put_blocking(np_pio, sm, b);
    }
    sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Modificado do github: https://github.com/BitDogLab/BitDogLab-C/tree/main/neopixel_pio
// Função para converter a posição do matriz para uma posição do vetor.
int getIndex(int x, int y)
{
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0)
    {
        return 24 - (y * 5 + x); // Linha par (esquerda para direita).
    }
    else
    {
        return 24 - (y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
    }
}

/**
 * Recebe a matriz de cores em RGB e converte em um vetor linear
 */
void set_sprite(int matriz[5][5][3])
{
    // Desenhando Sprite contido na matriz.c
    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz[coluna][linha][0], matriz[coluna][linha][1], matriz[coluna][linha][2]);
        }
    }
}

/**
 * Função que exibe os sprites de inicialização do sistema na matriz de LEDs
 */
void splash_screen()
{
    // Matriz que receberá todos os sprites da Matriz de LEDs
    uint32_t matriz[35][25][3];

    // Armazena os sprites na matriz
    splash_screen_array(matriz);

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PIN);

    npClear();

    // Aqui, você desenha nos LEDs.

    // Executa a apresentação de LED do splash screen apenas uma vez no código
    for (int i = 0; i < 35; i++)
    {
        // Desenhando Sprite contido na matriz.c
        set_sprite(matriz[i]);

        // Faz a gravação da matriz para os leds
        npWrite();

        sleep_ms(300);

        // Limpa os dados gravados na matriz de led
        npClear();
    }

    // Escreve os dados nos LEDs.
    npWrite();
}

/**
 * Função que exibe os sprites do Super Mario na matriz de LEDs
 */
void super_mario_sprite()
{
    // Matriz que receberá todos os sprites da Matriz de LEDs
    uint32_t matriz[25][25][3];

    // Armazena os sprites na matriz
    splash_screen_array(matriz);

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PIN);

    npClear();

    // Aqui, você desenha nos LEDs.

    // Executa a apresentação de LED do splash screen apenas uma vez no código
    for (int i = 0; i < 25; i++)
    {
        // Desenhando Sprite contido na matriz.c
        set_sprite(matriz[i]);

        // Faz a gravação da matriz para os leds
        npWrite();

        // Tempo para cada apresentação dos sprites (padrão de 1 minuto para cada = total de 25 minutos)
        sleep_ms(2000);
    }

    // Limpa os dados gravados na matriz de led
    npClear();

    // Escreve os dados nos LEDs.
    npWrite();
}

// Função de interrupção gerada pela interação do usuário através de botões
static void timer_callback(uint gpio, uint32_t events);

int main()
{
    // Inicializa entradas e saídas.
    stdio_init_all();

    // Inicializa e configura o botão A como resistor de pull-up
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    // Inicializa e configura o botão B como resistor de pull-up
    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    splash_screen();

    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &timer_callback);

    // Não faz mais nada. Loop infinito.
    while (true)
    {
        sleep_ms(100);
    }

    return 0;
}

void timer_callback(uint gpio, uint32_t events)
{
    // Verifica se o botão foi pressionado e o temporizador está desligado
    if (gpio_get(BTN_A) == 0 && !timer_on)
    {
        sleep_ms(50);
        // Indica que o temporizador foi ligado
        timer_on = true;

        // Inicia o temporizador
        super_mario_sprite();
    }
    // Verifica se o botão foi pressionado e o temporizador está ligado
    else if (gpio_get(BTN_A) == 0 && timer_on)
    {
    }
}

int64_t stop_timer_callback() {}


#endif
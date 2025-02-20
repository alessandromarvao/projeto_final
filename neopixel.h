#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

// Animação de fogo
#include "sprites/fire.h"
// Animação para o temporizador no formato de coração
#include "sprites/heart_shape.h"
// Animação para o temporizador com a logo do IF
#include "sprites/if_logo.h"
// Animação de chuva
#include "sprites/rain.h"
// Animação para tela inicial
#include "sprites/splash_screen.h"
// Animação para o temporizador do Super Mario
#include "sprites/super_mario.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição dos elementos da Matriz de LED NeoPixel ws2818b (5x5 em cores RGB)
#define MATRIX_ROWS 5
#define MATRIX_COLS 5
#define MATRIX_DEPTH 3

// Definição de pixel GRB
static struct pixel_t
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
static void npInit(uint pin)
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
static void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
static void npClear()
{
    for (uint i = 0; i < LED_COUNT; ++i)
        npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
static void npWrite()
{
    // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Modificado do github: https://github.com/BitDogLab/BitDogLab-C/tree/main/neopixel_pio
// Função para converter a posição do matriz para uma posição do vetor.
int getIndex(int x, int y) {
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0) {
        return 24-(y * 5 + x); // Linha par (esquerda para direita).
    } else {
        return 24-(y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
    }
}

/**
 * Função que exibe os sprites na matriz de LED neopixel
 */
static void display_matrix(int time_ms, int rgb_array[5][5][3])
{
    // Inicializa a matriz de LEDs NeoPixel.
    npInit(LED_PIN);

    // Limpa os dados do buffer de pixels.
    npClear();

    // Desenhando sprite contido na matriz.
    for (int linha = 0; linha < 5; linha++)
    {
        for (int coluna = 0; coluna < 5; coluna++)
        {
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, rgb_array[coluna][linha][0], rgb_array[coluna][linha][1], rgb_array[coluna][linha][2]);
        }
    }

    // Faz a gravação da matriz para os LEDs.
    npWrite();

    // Pausa entre as animações para visualização.
    sleep_ms(time_ms);

    // Limpa os dados gravados na matriz de LED.
    npClear();

    // Escreve os dados finais nos LEDs.
    npWrite();
}

/**
 * Função que apaga os LEDs da matriz
 */
static void turn_off()
{
    // Limpa os dados de todos os LEDs.
    npClear();
    // Aplica as alterações nos LEDs.
    npWrite();
}

/**
 * Converte as cores de um array com n elementos em hexadecimais para um array com n elementos em rgb.
 * @param size Tamanho do array de cores hexadecimais
 * @param hex_array Array de cores hexadecimais (N elementos de 25 caracteres em hexadecimal (cores))
 * @param rgb_array Array de cores rgb[N][5][5][3] (N elementos de 5 linhas e 5 colunas de cores rgb ({r, g, b}))
 */
static void hex_to_rgb(const uint32_t hex_array[25], int rgb_array[size][5][5][3])
{
    // Array que receberá os valores RGB
    int rgb[3];
    // Preencher a matriz RGB com a conversão dos valores ARGB
    for (int i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++)
    {
        rgb[0] = hex_array[size][i] & 0xFF;         // Blue
        rgb[2] = (hex_array[size][i] >> 16) & 0xFF; // Red
        rgb[1] = (hex_array[size][i] >> 8) & 0xFF;  // Green

        int row = i / MATRIX_COLS; // Cálculo da linha
        int col = i % MATRIX_COLS; // Cálculo da coluna

        // Armazenar os valores RGB na matriz 5x5x3
        rgb_array[pos][row][col][0] = rgb[0]; // Red
        rgb_array[pos][row][col][1] = rgb[1]; // Green
        rgb_array[pos][row][col][2] = rgb[2]; // Blue
    }
}

/**
 * Executa a animação do sprite da tela inicial na matriz de LED
 */
void display_splash_screen()
{
    // Define o tamanho do array de cores RGB
    int rgb_array[5][5][3];

    // Define a quantidade de elementos a serem exibidos na Matriz de LED
    int size = 37;

    // Converte as animações do splash_screen_data (em hexadecimal) para o formato RGB
    for (int i = 0; i < size; i++)
    {
        hex_to_rgb(splash_screen_data[i], rgb_array);
        
        display_matrix(300, rgb_array);
    }
}

#endif
#include <stdio.h>
#include "pico/stdlib.h"

// Biblioteca que exibe as imagens na matriz de LED RGB
#include "neopixel.h"
// Biblioteca de configuração e acesso à rede sem fio
#include "wifi_config.h"
// Biblioteca de configuração e acesso ao servidor NTP
#include "ntp_config.h"

static const bool timer_on = false;

int main()
{
    stdio_init_all();

    // display_splash_screen();

    wifi_config();

    sleep_ms(10);

    // display_heart_counter();
    // display_if_logo_counter();
    // display_mario_counter();

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

        sleep_ms(runtime);
    }
}

#include <stdio.h>
#include "pico/stdlib.h"


// Biblioteca que exibe as imagens na matriz de LED RGB
#include "neopixel.h"
// Biblioteca de configuração e acesso à rede sem fio
#include "wifi_config.h"
// Biblioteca de configuração e acesso ao servidor NTP
#include "ntp_config.h"



int main()
{
    stdio_init_all();
    
    run_ntp_test();

    display_splash_screen();
    // display_heart_counter();
    // display_if_logo_counter();
    // display_mario_counter();

    while (true) {
        for (int i = 0; i < 10; i++) {
            display_rain_screen();
        }
        for (int i = 0; i < 10; i++) {
            display_fire_screen();
        }
        sleep_ms(10);
    }
}

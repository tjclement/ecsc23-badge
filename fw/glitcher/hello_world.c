#include <stdio.h>
#include "pico/stdlib.h"

int main() {

    const uint LED_PIN = 26;
 
    // Initialize the GPIO to blink the LED
    //
    gpio_init(LED_PIN);
    gpio_init(LED_PIN+1);
    gpio_init(LED_PIN+2);
    gpio_init(LED_PIN+3);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_set_dir(LED_PIN+1, GPIO_OUT);
    gpio_set_dir(LED_PIN+2, GPIO_OUT);
    gpio_set_dir(LED_PIN+3, GPIO_OUT);
 
    // Initialize the serial port.
    //
    stdio_init_all();
 
    // Loop to blink the LED and print the message.
    //
    while (true)
    {
        printf("Wax on!\n");
        gpio_put(LED_PIN, 1);
        gpio_put(LED_PIN+1, 1);
        gpio_put(LED_PIN+2, 1);
        gpio_put(LED_PIN+3, 1);
        sleep_ms(500);
 
        printf("Wax off!\n");
        gpio_put(LED_PIN, 0);
        gpio_put(LED_PIN+1, 0);
        gpio_put(LED_PIN+2, 0);
        gpio_put(LED_PIN+3, 0);
        sleep_ms(500);
    }
 
    setup_default_uart();
    printf("Hello, world!\n");
    return 0;
}

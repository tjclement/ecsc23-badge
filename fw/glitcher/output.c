
#include <pico/stdlib.h>
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/pwm.h"
#include "hardware/structs/bus_ctrl.h"
#include "output.h"


int gpio_pio_prog_offset;

static void init_gpio_gpio() {
  for (int i = 0; i < 4; i++) {
    gpio_init(GPIO_D0+i);
    pio_gpio_init(GPIO_PIO, GPIO_D0+i);
  } 
}

static void gpio_pio_program(void) {
    uint16_t prog[] = {
        pio_encode_pull(false, true),
        pio_encode_out(pio_pins, 1),
        pio_encode_mov(pio_x, pio_osr),
        pio_encode_jmp_x_dec(3),
        pio_encode_jmp(0)
    };
    struct pio_program program = {
        .instructions = prog,
        .length = count_of(prog),
        .origin = -1};
    gpio_pio_prog_offset = pio_add_program(GPIO_PIO, &program);
}

void gpio_pio_init(void) {
    pio_sm_config c;
    
    gpio_pio_program();
    init_gpio_gpio();
    // loop the IN instruction forewer (8-bit and 16-bit version)
  
    for (int i = 0; i < 4; i++) {
        c = pio_get_default_sm_config();
        sm_config_set_out_pins(&c, GPIO_D0+i, 1);
        sm_config_set_out_shift(&c, true, false, 0);
        sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
        sm_config_set_clkdiv_int_frac(&c, 1, 64); //100MHz

        pio_claim_sm_mask(GPIO_PIO, 1u << i);
        pio_sm_set_consecutive_pindirs(GPIO_PIO, i, GPIO_D0+i, 1, true);
        pio_sm_init(GPIO_PIO, i, gpio_pio_prog_offset, &c);
        pio_sm_set_enabled(GPIO_PIO, i, true);
        GPIO_PIO->txf[i] = (1000000 << 1) + 0;
        GPIO_PIO->txf[i] = (2000000 << 1) + 1;
        GPIO_PIO->txf[i] = (1000000 << 1) + 0;
        GPIO_PIO->txf[i] = (1000000 << 1) + 1;
    }
}
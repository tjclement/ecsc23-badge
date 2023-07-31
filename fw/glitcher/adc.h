#ifndef __ADC_H__
#define __ADC_H__

#define ADC_PIO pio1
#define ADC_PIO_SM 1u
#define ADC_CLK (14)
#define ADC_D0 (15)

void adc_pio_init(void);

#endif
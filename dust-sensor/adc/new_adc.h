#ifndef NEW_ADC_H
#define NEW_ADC_H

#define ADC_REF_VOLTAGE 5.0


void adc_init();

uint8_t adc_read_bits();

float adc_read_voltage();

#endif
#ifndef NEW_ADC_H
#define NEW_ADC_H

#define ADC_REF_VOLTAGE 5.0
#define ADC_CONVERSION_TIME_US 104  // (13 / ADC_clock)

void adc_init();

uint8_t adc_read_bits();

float adc_read_voltage();

#endif
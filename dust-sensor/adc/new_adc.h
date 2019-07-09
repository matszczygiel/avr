#ifndef NEW_ADC_H
#define NEW_ADC_H

#include <stdint.h>

#define ADC_REF_VOLTAGE 5.0
#define ADC_CONVERSION_TIME_US 104  // (13 / ADC_clock)

//initialize ADC
void adc_init();

//read high bits of ADC register
uint16_t adc_read_bits();

//get measured ADC voltage
double adc_read_voltage();

#endif
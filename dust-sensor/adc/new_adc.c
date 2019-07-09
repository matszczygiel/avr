#include "new_adc.h"

#include <avr/io.h>

void adc_init()
{
    ADCSRA = (1 << ACEN);                                 //ADC startup
    ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //prescaler 8

    ADMUX = (0 << REFS1) | (1 << REFS0); //Vref = AVcc with capacitor on AREF pin
    ADMUX |= (1 << MUX2) | (1 << MUX0);  // ADC input set to pin PC5

    ADMUX |= (1 << ADLAR); //adjust to left
}

uint8_t adc_read_bits()
{
    ADCSRA |= (1 << ADSC); //start adc conversion
    while (ADCSRA & (1 << ADSC))
        ; //wait for conversion to complete

    return ADCH;
}

float adc_read_voltage()
{
    float adc_res = adc_read_bits();
    return adc_res * ADC_REF_VOLTAGE / 1024.0; //rescale from reference voltage (from Atmega8 datasheet)
}
#ifndef LEDDISP_H
#define LEDDISP_H

#include<avr/io.h>

#define LED_DIGITS_DDR DDRB
#define LED_SEGMENT_DDR DDRD
#define LED_DIGITS_PORT PORTB
#define LED_SEGMENT_PORT PORTD

#define LED_DOT 0b10000000
#define LED_MINUS 0b01000000;

const char led_digit[10];

const char led_seg[4];

void led_display_for(double value, int miliseconds, int dot_position_from_right);
void led_init();

#endif

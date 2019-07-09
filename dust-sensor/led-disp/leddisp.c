#include "leddisp.h"

#include <avr/io.h>
#include <util/delay.h>

const char led_digit[] = {0b00111111,
                          0b00000110,
                          0b01011011,
                          0b01001111,
                          0b01100110,
                          0b01101101,
                          0b01111101,
                          0b00000111,
                          0b01111111,
                          0b01101111};

const char led_seg[] = {0b00000001,
                        0b00000010,
                        0b00000100,
                        0b00001000};

void led_display_for(int val, int miliseconds)
{
    if ((val > 9999) | (val < 0))
        return;
    int turns = miliseconds / 4;
    int temp, num;


    for (int i = 0; i < turns; ++i)
    {
        num = val;
        temp = num / 1000;
        num = num % 1000;
        LED_SEGMENT_PORT |= 0x0F;
        LED_SEGMENT_PORT &= ~led_seg[0];
        LED_DIGITS_PORT = led_digit[temp];
        _delay_ms(1);

        temp = num / 100;
        num = num % 100;
        LED_SEGMENT_PORT |= 0x0F;
        LED_SEGMENT_PORT &= ~led_seg[1];
        LED_DIGITS_PORT = led_digit[temp];
        _delay_ms(1);

        LED_SEGMENT_PORT &= ~0x0F;

        temp = num / 10;
        num = num % 10;
        LED_SEGMENT_PORT |= 0x0F;
        LED_SEGMENT_PORT &= ~led_seg[2];
        LED_DIGITS_PORT = led_digit[temp];
        _delay_ms(1);

        LED_SEGMENT_PORT &= ~0x0F;

        temp = num;
        LED_SEGMENT_PORT |= 0x0F;
        LED_SEGMENT_PORT &= ~led_seg[3];
        LED_DIGITS_PORT = led_digit[temp];
        _delay_ms(1);
    }

    LED_SEGMENT_PORT |= 0x0F;
    LED_DIGITS_PORT = 0x00;
}

void led_init()
{
    LED_DIGITS_DDR = 0xFF;
    LED_SEGMENT_DDR |= 0x0F;
}
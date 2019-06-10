#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB = 1;
    while(1)
    {
        PORTB = 0;
        _delay_ms(100);
        PORTB = 1;
        _delay_ms(1000);
        PORTB = 0;
        _delay_ms(500);
        PORTB = 1;
        _delay_ms(1000);
    }
} 
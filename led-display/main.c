#include <avr/io.h>
#include <util/delay.h>

char digit[] = {0b00111111,
                0b00000110,
                0b01011011,
                0b01001111,
                0b01100110,
                0b01101101,
                0b01111101,
                0b00000111,
                0b01111111,
                0b01101111};

#define DOT 0b10000000

char seg[] = {0b00001110,
              0b00001101,
              0b00001011,
              0b00000111};

int main()
{
  DDRB = 0xFF;
  DDRC = 0xFF;

  int num, cnt, temp;

  while (1)
  {
    for (cnt = 0; cnt <= 9999; ++cnt) // loop to display 0-9999
    {
      for (int i = 0; i < 250; ++i)
      {
        num = cnt;
        temp = num / 1000;
        num = num % 1000;
        PORTC = seg[0];
        PORTB = digit[temp];
        _delay_ms(1);

        temp = num / 100;
        num = num % 100;
        PORTC = seg[1];
        PORTB = digit[temp];
        _delay_ms(1);

        temp = num / 10;
        PORTC = seg[2];
        PORTB = digit[temp];
        _delay_ms(1);

        temp = num % 10;
        PORTC = seg[3];
        PORTB = digit[temp];
        _delay_ms(1);
      }
    }
  }
}
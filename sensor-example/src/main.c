/*
dust meter 01

copyright (c) Davide Gironi, 2013

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "adc/adc.h"

#include "lcd/lcd.h"

#include "gp2y1010au0f/gp2y1010au0f.h"

#define DEBUG_PRINT 0 // enable or disable debug print

#if DEBUG_PRINT == 1
#define UART_BAUD_RATE 2400
#include "uart/uart.h"
#endif

int main(void) {
	#if DEBUG_PRINT == 1
	char printbuff[100];
	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	#endif

	//init adc
	adc_init();

	//init interrupt
	sei();

	//init lcd
	lcd_init(LCD_DISP_ON);

	//startup message
	lcd_puts_p(PSTR("dust meter 01\n"));
	lcd_puts_p(PSTR("starting..."));
	_delay_ms(1000);

	//init gp2y1010au0f
	gp2y1010au0f_init();

	lcd_clrscr();

	lcd_puts_p(PSTR("PM >0.5micron"));
	lcd_gotoxy(10, 1);
	lcd_puts_p(PSTR("ug/m^3"));
	for (;;) {
		//get dust value
		double dust = gp2y1010au0f_getdust();

		//clear lcd line
		lcd_gotoxy(0, 1);
		lcd_puts_p(PSTR("      "));
		//print new value to lcd
		lcd_gotoxy(0, 1);
		char dustbuf[10];
		dtostrf(dust, 3, 2, dustbuf);
		lcd_puts(dustbuf);

		#if DEBUG_PRINT == 1
		//print dust
		dtostrf(dust, 3, 3, printbuff);
		uart_puts("dust "); uart_puts(printbuff); uart_puts("\r\n");

		uart_puts("\r\n");
		#endif

		_delay_ms(1000);
	}
	
	return 0;
}

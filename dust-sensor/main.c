#include "adc/adc.h"
#include "gp2y1010au0f/gp2y1010au0f.h"
#include "led-disp/leddisp.h"


int main(void) {
	//init adc
	adc_init();

	//init interrupt
	sei();

	//init gp2y1010au0f
	gp2y1010au0f_init();

	led_init();

	for (;;) {
		//get dust value
		int dust = (int) gp2y1010au0f_getdust();

	//	int dustint = dust * 1000;
		led_display_for(dust, 1000);

	}
	
	return 0;
}

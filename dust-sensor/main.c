
//#include "adc/adc.h"
//#include "gp2y1010au0f/gp2y1010au0f.h"

#include "led-disp/leddisp.h"

#include "adc/new_adc.h"
#include "gp2y1010au0f/sensor.h"

int main(void)
{
	adc_init();	//initialize ADC
	sensor_init(); //initialize sensor
	led_init();	//initialize led display

	while (1)
	{

		double volt = sensor_read_voltage(); //read voltage from the dust sensor
		int dust = sensor_compute_dust_concentration(volt);
		led_display_for(123, 500);
	}
}

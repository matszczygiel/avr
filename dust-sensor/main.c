
#include "led-disp/leddisp.h"
#include "adc/adc.h"
#include "sensor/sensor.h"

int main(void)
{
	adc_init();	//initialize ADC
	sensor_init(); //initialize sensor
	led_init();	//initialize led display

	while (1)
	{
		double volt = sensor_read_voltage(); //read voltage from the dust sensor
		double dust = sensor_compute_dust_concentration(volt);
		led_display_for(dust, 500, 1);
	}
}

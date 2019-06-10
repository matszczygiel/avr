/*
GP2Y1010AU0F library 0x01

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#include <avr/io.h>
#include <util/delay.h>

#include "../adc/adc.h"

#include "gp2y1010au0f.h"


/*
 * read sensor raw output
 */
uint16_t gp2y1010au0f_getraw() {
	static uint16_t dustadc = 0;

	adc_setchannel(GP2Y1010AU0F_LEDIN_CHANNEL); //set adc channel

	uint16_t dustadclast = 0;
	uint32_t dustadctot = 0;
	uint8_t i=0;
	for(i=0; i<GP2Y1010AU0F_SAMPLES; i++) {
		PORTC ^= (1<<PC5);
		GP2Y1010AU0F_LEDOUT_PORT &= ~(1<<GP2Y1010AU0F_LEDOUT_PIN); //off, power led on
		_delay_us(GP2Y1010AU0F_SAMPLEDELAYUS); //delay
		dustadclast = adc_readsel(); //read the dust value
		dustadctot += dustadclast;
		_delay_us(GP2Y1010AU0F_SAMPLEENDDELAYUS); //delay
		GP2Y1010AU0F_LEDOUT_PORT |= (1<<GP2Y1010AU0F_LEDOUT_PIN); //on, power led off
		_delay_us(GP2Y1010AU0F_PAUSEDELAYUS); //delay
		_delay_ms(GP2Y1010AU0F_PAUSEDELAYMS); //correction delay
	}
	dustadclast = dustadctot/GP2Y1010AU0F_SAMPLES;

	#if GP2Y1010AU0F_FILTERENABLED == 1
	dustadc = ((64-GP2Y1010AU0F_EMAFILTERALPHA)*dustadc+GP2Y1010AU0F_EMAFILTERALPHA*dustadclast)>>6; //apply smooth filter
	#else
	dustadc = dustadclast;
	#endif

	return dustadc;
}


/*
 * convert raw data to ug/m^3
 */
double gp2y1010au0f_computedust(uint16_t dustadc, double refvoltage) {
	double voltage = (double)(dustadc*refvoltage/(double)1024);
	//conversion based on the fig 3 datasheet
	double ret = GP2Y1010AU0F_SLOPE*voltage+GP2Y1010AU0F_INTERCEPT;
	if(ret < 0)
		ret = 0;
	else if(ret > 0.5)
		ret = 0.5;
	ret = ret *1000; //convert milligrams to micrograms
	return ret;
}


/*
 * return sensor dust >0.5micron values ug/m^3
 */
double gp2y1010au0f_getdust() {
	//get raw data
	uint16_t dustadc = gp2y1010au0f_getraw();
	//get reference voltage
	double refvoltage = acd_getrealvref();
	//convert raw data
	return gp2y1010au0f_computedust(dustadc, refvoltage);
}


/*
 * init gp2y1010au0f
 */
void gp2y1010au0f_init() {
	//init led out port
	GP2Y1010AU0F_LEDOUT_DDR |= (1<<GP2Y1010AU0F_LEDOUT_PIN); //output

	#if GP2Y1010AU0F_FILTERENABLED == 1
	//do same start reading to initialize the filter
	uint8_t i = 0;
	for(i=0; i<20; i++) {
		gp2y1010au0f_getraw();
	}
	#endif
}


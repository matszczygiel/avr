/*
GP2Y1010AU0F library 0x01

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References:
  + Air Quality Monitoring by Chris Nafis
    http://www.howmuchsnow.com/arduino/airquality/
*/

#ifndef GP2Y1010AU0F_H_
#define GP2Y1010AU0F_H_

//define out led port
#define GP2Y1010AU0F_LEDOUT_DDR DDRB
#define GP2Y1010AU0F_LEDOUT_PORT PORTB
#define GP2Y1010AU0F_LEDOUT_PIN PB0

//define in led channel
#define GP2Y1010AU0F_LEDIN_CHANNEL 4

//define slop and intercept to convert values
//derived using linear interpolation on datasheet fig 3.
#define GP2Y1010AU0F_SLOPE 0.172
#define GP2Y1010AU0F_INTERCEPT -0.0999

//setup delay (based on ADC and FCPU clock)
//GP2Y1010AU0F_SAMPLEDELAY should be 280us to perform the correct reading (datasheet fig.2)
//this delay should consider that ADC conversion takes 13 ADC clock cycles
//ADCtime(s) = (1/ADCclock)*13 = (1/FCPU/ADCprescaler)*13
// es. (1/(8000000/64))*13 = 0.000104s = 104us
//so to perform reading at correct time
//280 - (1/FCPU/ADCprescaler)*13*1000000   , 1000000 is the conversion factor from s to us
// es. 280 - 104 = 176
#define GP2Y1010AU0F_SAMPLEDELAYUS 176
//from datasheet 320us - 280us
#define GP2Y1010AU0F_SAMPLEENDDELAYUS 40
//from datasheet 10000us - 320us
#define GP2Y1010AU0F_PAUSEDELAYUS 9680
//this delay is here for the mean, without this delay reading are not consistend
//(anything from 50 to 200 will work)
#define GP2Y1010AU0F_PAUSEDELAYMS 80

//samples for average
#define GP2Y1010AU0F_SAMPLES 20

//smooth filter
#define GP2Y1010AU0F_FILTERENABLED 1 //enabled disabled
#define GP2Y1010AU0F_EMAFILTERALPHA 10 //select from 1 to 64 (bigger values means less filter)


//functions
extern void gp2y1010au0f_init();
extern uint16_t gp2y1010au0f_getraw();
extern double gp2y1010au0f_computedust(uint16_t dustadc, double refvoltage);
extern double gp2y1010au0f_getdust();

#endif

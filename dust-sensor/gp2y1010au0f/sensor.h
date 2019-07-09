#ifndef SENSOR_H
#define SENSOR_H

#define SENSOR_IRLED_DDR DDRD
#define SENSOR_IRLED_PORT PORTD
#define SENSOR_IRLED_PIN PD7
#define SENSOR_SAMPLES 10

#define SENSOR_SAMPLING_DELAY_US 280
#define SENSOR_PULSE_WIDTH_US 320

//initialize sensor setting - change macros before
void sensor_init();

//compute the dust concentration [ug /m^3] from
float sensor_compute_dust_concentration(float voltage);

//read averaged voltage
float sensor_read_voltage();

#endif
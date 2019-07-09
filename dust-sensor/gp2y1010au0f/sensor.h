#ifndef SENSOR_H
#define SENSOR_H

#define SENSOR_IRLED_DDR DDRD
#define SENSOR_IRLED_PORT PORTD
#define SENSOR_IRLED_PIN PD7
#define SENSOR_SAMPLES 10

#define SENSOR_SAMPLING_DELAY_US 280
#define SENSOR_PULSE_WIDTH_US 320
#define SENSOR_CYCLE_MS 10

//initialize sensor setting - change macros before
void sensor_init();

//compute the dust concentration [ug /m^3] from
double sensor_compute_dust_concentration(double voltage);

//read averaged voltage
double sensor_read_voltage();

#endif
#include "sensor.h"

#include <util/delay.h>
#include <avr/io.h>

#include "../adc/adc.h"

void sensor_init()
{
    SENSOR_IRLED_DDR |= (1 << SENSOR_IRLED_PIN); // set IR led pin as output
    SENSOR_IRLED_PORT |= (1 << SENSOR_IRLED_PIN); //turn IR led off
}

double sensor_compute_dust_concentration(double voltage)
{
    const double A = 0.17;
    const double B = 0.15;
    double ret = A * (voltage - B);
    if (ret < 0.0)
        ret = 0.0;
    else if (ret > 0.5)
        ret = 0.5;
    ret *= 1000; // to micrograms
    return ret;
}

double sensor_read_voltage()
{
    double vtot = 0.0;

    for (int i = 0; i < SENSOR_SAMPLES; ++i)
    {
        SENSOR_IRLED_PORT &= ~(1 << SENSOR_IRLED_PIN);                  // turn on IR led
        _delay_us((SENSOR_SAMPLING_DELAY_US  - ADC_CONVERSION_TIME_US)); // delay
        vtot += adc_read_voltage();                                     // read the dust value
        _delay_us((SENSOR_PULSE_WIDTH_US - SENSOR_SAMPLING_DELAY_US));  // wait until end of pulse
        SENSOR_IRLED_PORT |= (1 << SENSOR_IRLED_PIN);                   // turn off IR led
        _delay_ms(SENSOR_CYCLE_MS);                                     // wait until reading cycle completes
    }
    return (vtot / SENSOR_SAMPLES);
}
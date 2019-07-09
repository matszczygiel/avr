#include "sensor.h"

#include "../adc/new_adc.h"

void sensor_init() {
    SENSOR_IRLED_DDR |= (1 << SENSOR_IRLED_PIN);  //set IR led pin as output
}

float sensor_compute_dust_concentration(float voltage) {
    const float A = 0.172;
    const float B = -0.0999;
    float ret     = A * voltage + B;
    if (ret < 0)
        ret = 0;
    else if (ret > 0.5)
        ret = 0.5;
    ret *= 1000;  //to micrograms
    return ret;
}

float sensor_read_voltage() {
    float vtot  = 0.0;

    for (int i = 0; i < SENSOR_SAMPLES; ++i) {
        SENSOR_IRLED_PORT &= ~(1 << SENSOR_IRLED_PIN);                 //turn off IR led
        _delay_us(SENSOR_SAMPLING_DELAY_US - ADC_CONVERSION_TIME_US);  //delay
        float volt = adc_read_voltage();                                   //read the dust value
        vtot += volt;
        _delay_us(GP2Y1010AU0F_SAMPLEENDDELAYUS);                    //delay
        GP2Y1010AU0F_LEDOUT_PORT |= (1 << GP2Y1010AU0F_LEDOUT_PIN);  //on, power led off
        _delay_us(GP2Y1010AU0F_PAUSEDELAYUS);                        //delay
        _delay_ms(GP2Y1010AU0F_PAUSEDELAYMS);                        //correction delay
    }
    dustadclast = dustadctot / GP2Y1010AU0F_SAMPLES;
}
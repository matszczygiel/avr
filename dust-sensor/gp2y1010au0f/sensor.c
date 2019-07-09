#include "sensor.h"

void sensor_init() {
    SENSOR_IRLED_DDR |= (1<<SENSOR_IRLED_PIN); //set IR led pin as output
}
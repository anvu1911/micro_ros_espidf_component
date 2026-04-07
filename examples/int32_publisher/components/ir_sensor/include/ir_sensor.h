#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <stdint.h>

// Initialize GPIO and Interrupts
void ir_sensor_init(int gpio_num);

// Get the current count
int32_t ir_sensor_get_count();

// Reset count if needed
void ir_sensor_reset();

#endif
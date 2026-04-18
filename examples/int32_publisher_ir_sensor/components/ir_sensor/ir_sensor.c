#include "ir_sensor.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_timer.h"

static volatile int32_t count = 0;
static volatile int64_t last_interrupt_time = 0;
static int saved_gpio_num = 0;
const int64_t DEBOUNCE_TIME_US = 10000;

static void IRAM_ATTR gpio_isr_handler(void* arg) {
    int64_t now = esp_timer_get_time();
    if ((now - last_interrupt_time) > DEBOUNCE_TIME_US) {
        // Use the saved pin number to check the level
        if (gpio_get_level(saved_gpio_num) == 0) { 
            count++;
            last_interrupt_time = now;
        }
    }
}

void ir_sensor_init(int gpio_num) {
    saved_gpio_num = gpio_num; // Store the pin for the ISR to use later
    
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_NEGEDGE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << gpio_num),
        .pull_up_en = 1,
    };
    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(gpio_num, gpio_isr_handler, NULL);
}

int32_t ir_sensor_get_count() { return count; }
void ir_sensor_reset() { count = 0; }
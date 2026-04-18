idf_component_register(SRCS "ir_sensor.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES driver esp_timer) # Add this to fix the gpio.h error

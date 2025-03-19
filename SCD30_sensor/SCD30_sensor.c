/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * 1. Dikshanya Ramaswamy
 * 2. 
 * 3. 
 */
// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Include PICO libraries
#include "pico/stdlib.h"

#include "hardware/i2c.h"
#include "SCD30_sensor.h"

void SCD30_reset() {
    // Reset the sensor
    uint8_t buf[] = {0xD3, 0x04}; // Command found in datasheet 
    i2c_write_blocking(I2C_CHAN, ADDRESS, buf, 2, false);
}

void SCD30_start_measurement() {
    // Command to start continuous measurement
    uint8_t buf[] = {0x00, 0x10}; // Start measurement command
    i2c_write_blocking(I2C_CHAN, ADDRESS, buf, 2, false);
}

void SCD30_stop_measurement() {
    // Command to stop continuous measurement
    uint8_t buf[] = {0x00, 0x00}; // Stop measurement command
    i2c_write_blocking(I2C_CHAN, ADDRESS, buf, 2, false);
}

void SCD30_read_measurement() {
    uint8_t cmd[] = {0x03, 0x00}; // Command to read measurement
    uint8_t buffer[18]; // 18 bytes of data

    i2c_write_blocking(I2C_CHAN, ADDRESS, cmd, 2, true);
    i2c_read_blocking(I2C_CHAN, ADDRESS, buffer, 18, false);

    // Extract CO2 concentration (Skip CRC bytes)
    // uint16_t co2_raw = (buffer[0] << 8) | buffer[1];
    uint32_t co2_raw;
    co2_raw = (co2_raw << 8) | buffer[0];
    co2_raw = (co2_raw << 8) | buffer[1]; 
    co2_raw = (co2_raw << 8) | buffer[3]; 
    co2_raw = (co2_raw << 8) | buffer[4]; 

    // Extract Temperature
    uint16_t temp_raw = (buffer[7] << 8) | buffer[8];
    temp_raw = (temp_raw << 8) | buffer[10]; 
    temp_raw = (temp_raw << 8) | buffer[11];

    // Extract Humidity
    uint16_t hum_raw = (buffer[13] << 8) | buffer[14];
    hum_raw = (hum_raw << 8) | buffer[16]; 
    hum_raw = (hum_raw << 8) | buffer[17];

    float co2 = (float)co2_raw;
    uint16_t temperature = temp_raw;
    uint16_t humidity = hum_raw;


    printf("CO2: %ld ppm, Temperature: %ld C, Humidity: %ld%%\n", co2_raw, temperature, humidity);
}


int main() {
    stdio_init_all();
    
    // Initialize I2C
    i2c_init(I2C_CHAN, I2C_BAUD_RATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);  // SDA
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);  // SCL
    
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    printf("Sending reset command to SCD30...\n");
    SCD30_reset();
    printf("Reset command sent.\n");
    SCD30_start_measurement();
    printf("Starting measurement...\n");

    while (1) {
        sleep_ms(2000);  // SCD30 updates every 2 seconds
        // if (SCD30_data_ready()) {
        SCD30_read_measurement();
        // } else {
        //     printf("Waiting for measurement data...\n");
        // }
    }
    return 0;
}

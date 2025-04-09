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
    i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 2, false);
}

void SCD30_start_measurement() {
    // Command to start continuous measurement
    uint8_t buf[] = {0x00, 0x10}; // Start measurement command
    int x = i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 2, false);
}

int SCD30_set_measurement_interval(){
    uint8_t buf[] = {0x46, 0x00};
    int x = i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 2, false);
    return x;

}

void SCD30_data_ready()
{
    uint8_t buf[] = {0x02, 0x02};
    uint8_t rdy;
    // i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 2, true);
    int x = i2c_read_blocking(I2C_PORT, SCD30_ADDR, buf, 2, false);

    // for (int i=0;i<x;i++)
    // {
        printf("\nrdy = %d", rdy);
    // }
    //return x;
}

// void SCD30_stop_measurement() {
//     // Command to stop continuous measurement
//     uint8_t buf[] = {0x00, 0x00}; // Stop measurement command
//     i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 2, false);
// }



// void SCD30_read_measurement() {
//     uint8_t cmd[] = {0x03, 0x00}; // Command to read measurement
//     uint8_t buffer[18]; // 18 bytes of data

//     i2c_write_blocking(I2C_PORT, SCD30_ADDR, cmd, 2, true);
//     int x = i2c_read_blocking(I2C_PORT, SCD30_ADDR, buffer, 18, false);

//     for (int i=0;i<x;i++)
//     {
//         printf("\nBuffer[%d] = %x", i, buffer[i]);
//     }
//     // Extract CO2 concentration (Skip CRC bytes)
//     // uint16_t co2_raw = (buffer[0] << 8) | buffer[1];
//     // uint32_t co2_raw;
//     // co2_raw = (co2_raw << 8) | buffer[0];
//     // co2_raw = (co2_raw << 8) | buffer[1]; 
//     // co2_raw = (co2_raw << 8) | buffer[3]; 
//     // co2_raw = (co2_raw << 8) | buffer[4]; 

//     // // Extract Temperature
//     // uint16_t temp_raw = (buffer[7] << 8) | buffer[8];
//     // temp_raw = (temp_raw << 8) | buffer[10]; 
//     // temp_raw = (temp_raw << 8) | buffer[11];

//     // // Extract Humidity
//     // uint16_t hum_raw = (buffer[13] << 8) | buffer[14];
//     // hum_raw = (hum_raw << 8) | buffer[16]; 
//     // hum_raw = (hum_raw << 8) | buffer[17];

//     // float co2 = (float)co2_raw;
//     // uint16_t temperature = temp_raw;
//     // uint16_t humidity = hum_raw;

//     //printf("CO2: %0.02f\n", co2);
//     //printf("CO2: %ld ppm, Temperature: %ld C, Humidity: %ld%%\n", co2_raw, temperature, humidity);
//     // return x; // from read or write blocking
// }


int main() {
    stdio_init_all();
    
    // Initialize I2C
    i2c_init(I2C_PORT, I2C_BAUD_RATE);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);  // SDA
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);  // SCL
    
    // DATA and CLK PULL UP
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    gpio_init(RDY_PIN);
    gpio_set_dir(RDY_PIN, GPIO_IN);

    //RESET CALL
    printf("Sending reset command to SCD30...\n");
    SCD30_reset();    
    printf("Reset command sent.\n");
    sleep_ms(50);
    // int reset_out = SCD30_reset();
    //printf("\nPrinting reset output: %d", reset_out);

    // START MEASUREMENT
    SCD30_start_measurement();
    printf("STARTING data...:\n");
    sleep_ms(50);

    // MEASUREMENT INTERVAL
    int y = SCD30_set_measurement_interval();
    printf("SET INTERVAL CHECK%d", y);
    //int measure_start = SCD30_start_measurement();
    //printf("Starting measurement...: %d\n", measure_start);
    sleep_ms(50);

    // READ SIGNAL  
    // int rdy_sig = SCD30_data_ready();
    // printf("Check Ready Signal...: %d\n",rdy_sig);
    int ctr = 0;
    while (1)
    {
        SCD30_data_ready();
        //printf("Check Ready Signal...: %d\n",rdy_sig);
        ctr+=1;
        sleep_ms(100);
    }

    // READ MEASUREMENT
    // int ctr = 0;
    // while (ctr<20)
    // {
    //     SCD30_read_measurement();
    //     ctr+=1;
    //     sleep_ms(50);
    // }
    //int read_data_sig = SCD30_read_measurement();
    //printf("READING data...: %d\n",read_data_sig);
    // if (SCD30_data_ready()) {
    //     printf("\nREady to read\n");
    //     //     SCD30_read_measurement();
    // }

    // while (1) {
    //     sleep_ms(2000);  // SCD30 updates every 2 seconds
    //     // if (SCD30_data_ready()) {
    //     SCD30_read_measurement();
    //     // } else {
    //     //     printf("Waiting for measurement data...\n");
    //     // }
    // }
    return 0;
}

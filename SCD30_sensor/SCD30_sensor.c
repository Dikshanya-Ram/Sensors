/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * 1. Dikshanya Ramaswamy
 * 2. Nicholas Ricci
 * 3. Ao Ruan
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <string.h>
 #include "pico/stdlib.h"
 #include "hardware/i2c.h"
 #include "SCD30_sensor.h"
 
 
 // Function Definitions
 void SCD30_reset() {
     uint8_t buf[] = {0xD3, 0x04};
     i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 2, false);
 }
 
 void SCD30_start_measurement() {
     uint8_t buf[] = {0x00, 0x10, 0x00, 0x00};
     i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 4, false);
 }

 void SCD30_set_measurement_interval() {
     uint8_t buf[] = {0x46, 0x00, 0x00, 0x02};
     i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 4, false);
 }

 void SCD30_set_auto_self_calibration(){
    //b'\x53\x06\x00\x01\x00';
    uint8_t buf[] = {0x53, 0x06, 0x00, 0x01};
    i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 4, false);
 }

 bool SCD30_data_ready() {
     uint8_t buf[] = {0x03, 0x00};
     uint8_t data[2];
     i2c_write_blocking(I2C_PORT, SCD30_ADDR, buf, 2, true); // Send command
     i2c_read_blocking(I2C_PORT, SCD30_ADDR, data, 2, false); // Read response
     return (data[0] == 0x01) && (data[1] == 0x01); // Check if MSB and LSB are both 1
 }
 
  float unpack_scd30_float(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
    uint8_t tmp[4];
    tmp[0] = b0;
    tmp[1] = b1;
    tmp[2] = b2;
    tmp[3] = b3;

    float f;
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        // Reverse byte order for little-endian systems
        uint8_t reversed[4] = {tmp[3], tmp[2], tmp[1], tmp[0]};
        memcpy(&f, reversed, 4);
    #else
        // Direct copy on big-endian systems
        memcpy(&f, tmp, 4);
    #endif
        return f;
    }


 int SCD30_read_measurement(float *co2, float *temperature, float *humidity) {
     uint8_t cmd[] = {0x03, 0x00}; // Command to read measurement
     uint8_t buffer[18]; // 18 bytes of data
 
     i2c_write_blocking(I2C_PORT, SCD30_ADDR, cmd, 2, true);
     int bytes_read = i2c_read_blocking(I2C_PORT, SCD30_ADDR, buffer, 18, false);
 
     if (bytes_read != 18) {
         printf("Error reading data: %d bytes read\n", bytes_read);
         return -1;
     }

     for(int i=0; i<18; i++)
     {
        printf("\nBuffer Data[%d]: %x\n", i, buffer[i]);
     }
     *co2 = unpack_scd30_float(buffer[0], buffer[1], buffer[3], buffer[4]);
     *temperature = unpack_scd30_float(buffer[6], buffer[7], buffer[9], buffer[10]);
     *humidity = unpack_scd30_float(buffer[12], buffer[13], buffer[15], buffer[16]);
 
     return 0;
 }
 
 uint8_t cmd_read[] = {0x03, 0x00}; // Command to read measurement


 int main() {
     stdio_init_all();
 
     // Initialize I2C
     i2c_init(I2C_PORT, I2C_BAUD_RATE);
     gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
     gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
     gpio_pull_up(SDA_PIN);
     gpio_pull_up(SCL_PIN);
 
     // Initialize RDY pin
     gpio_init(RDY_PIN);
     gpio_set_dir(RDY_PIN, GPIO_IN);
 
     // Initialize SCD30 sensor
     printf("Resetting SCD30...\n");
     SCD30_reset();
     sleep_ms(100);
 
     printf("Starting continuous measurement...\n");
     SCD30_start_measurement();
     sleep_ms(100);
 
     printf("Setting measurement interval...\n");
     SCD30_set_measurement_interval();
     sleep_ms(100);
 
     printf("Calibrating...\n");
     SCD30_set_auto_self_calibration();
     sleep_ms(100);

     float co2, temperature, humidity;
 
     while (1) {
         if (gpio_get(RDY_PIN)) {
            uint8_t buffer[18]; // 18 bytes of data
            i2c_write_blocking(I2C_PORT, SCD30_ADDR, cmd_read, 2, true);
            sleep_ms(3); // suggested in data sheet
            int bytes_read = i2c_read_burst_blocking(I2C_PORT, SCD30_ADDR, buffer, 18); // read_blocking
            for(int i=0;i<18;i++)
                printf("\nbuffer[%d]:%x", i, buffer[i]);
         } else {
             printf("Data not ready yet...\n");
         }
         sleep_ms(2000); // Measurement interval is 2 seconds
     }
 
     return 0;
 }
# Sensors

**Main System:**  RP2040 microcontroller on the Raspberry Pi Pico development board
![image](https://github.com/user-attachments/assets/dcb6092a-de06-4195-be44-7cabcdcf27f4)


## Sparkfun SEN-22395
Measures:
A. Co2
B. Temperature
C. Humidity

### Commands
From Datasheet
| Domain                                      | Command                                | Hex. Code | I²C sequence type                 | Execution time [ms] | During meas.* |
|---------------------------------------------|----------------------------------------|-----------|-----------------------------------|---------------------|---------------|
| **Basic Commands Chapter 3.5**              | start_periodic_measurement             | 0x21b1    | send command                      | -                   | no            |
|                                             | read_measurement                       | 0xec05    | read                               | 1                   | yes           |
|                                             | stop_periodic_measurement              | 0x3f86    | send command                      | 500                 | yes           |
| **On-chip output signal compensation Chapter 3.6** | set_temperature_offset                | 0x241d    | write                             | 1                   | no            |
|                                             | get_temperature_offset                 | 0x2318    | read                               | 1                   | no            |
|                                             | set_sensor_altitude                    | 0x2427    | write                             | 1                   | no            |
|                                             | get_sensor_altitude                    | 0x2322    | read                               | 1                   | no            |
|                                             | set_ambient_pressure                   | 0xe000    | write                             | 1                   | yes           |
| **Field calibration Chapter 3.7**           | perform_forced_recalibration           | 0x362f    | send command and fetch result     | 400                 | no            |
|                                             | set_automatic_self_calibration_enabled | 0x2416    | write                             | 1                   | no            |
|                                             | get_automatic_self_calibration_enabled | 0x2313    | read                               | 1                   | no            |
| **Low power Chapter 3.8**                   | start_low_power_periodic_measurement   | 0x21ac    | send command                      | -                   | no            |
|                                             | get_data_ready_status                  | 0xe4b8    | read                               | 1                   | yes           |
| **Advanced features Chapter 3.9**           | persist_settings                       | 0x3615    | send command                      | 800                 | no            |
|                                             | get_serial_number                      | 0x3682    | read                               | 1                   | no            |
|                                             | perform_self_test                      | 0x3639    | read                               | 10000               | no            |
|                                             | perform_factory_reset                  | 0x3632    | send command                      | 1200                | no            |
|                                             | reinit                                 | 0x3646    | send command                      | 20                  | no            |
| **Low power single shot (SCD41 only) Chapter 3.10** | measure_single_shot                   | 0x219d    | send command                      | 5000                | no            |
|                                             | measure_single_shot_rht_only           | 0x2196    | send command                      | 50                  | no            |


References: 
RpiPico: https://www.circuitstate.com/news/rp2040-pico-all-new-microcontroller-and-development-board-from-raspberry-pi/ <br>
git: https://github.com/sparkfun/SparkFun_SCD4x_Arduino_Library/tree/main <br>
Datasheet: https://cdn.sparkfun.com/assets/d/4/9/a/d/Sensirion_CO2_Sensors_SCD4x_Datasheet.pdf <br>
SCD40: https://www.sparkfun.com/products/22395 <br>
Sensor Diagram: https://cdn.sparkfun.com/assets/9/b/f/5/2/SparkFun_Qwiic_CO2_Sensor_SCD40.pdf <br>
[Link to purchase](https://www.digikey.com/en/products/detail/sparkfun-electronics/SEN-22395/21703931?utm_adgroup=Development%20Boards&utm_source=bing&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_RLSA_Cart&utm_term=products%20development%20boards%20kits%20programmers%20&utm_content=Development%20Boards&utm_id=bi_cmp-384476623_adg-1311717597280063_ad-81982399195108_dat-2333782149503789:loc-190_dev-c_ext-_prd-&msclkid=9d8c381431a715bd3e875f0aa96a73a0) <br>
[Link to github](https://github.com/Dikshanya-Ram/Sensors) <br>

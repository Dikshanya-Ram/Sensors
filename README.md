# Sensors

**Main System:**  RP2040 microcontroller on the Raspberry Pi Pico development board
![image](https://github.com/user-attachments/assets/dcb6092a-de06-4195-be44-7cabcdcf27f4)


## Sparkfun SEN-22395
Measures:
A. Co2
B. Temperature
C. Humidity

### Commands
| **Command**                     | **Code (Hex)** | **Description**                                              | **Typical Use**                          |
|---------------------------------|----------------|--------------------------------------------------------------|------------------------------------------|
| **Start Periodic Measurement**  | `0x21B1`        | Begins continuous CO2 measurement.                            | Normal operation to monitor CO2 levels.  |
| **Stop Periodic Measurement**   | `0x3F86`        | Halts continuous measurement.                                 | Stop monitoring to save power.           |
| **Read Measurement**            | `0xEC05`        | Retrieves CO2, temperature, and humidity values.              | Fetch the latest sensor data.            |
| **Set Temperature Offset**      | `0x241D`        | Sets offset for temperature measurements.                     | Compensate for temperature discrepancies.|
| **Set Sensor Altitude**         | `0x2427`        | Configures sensor altitude above sea level (meters).          | Adjust for local altitude effects.       |
| **Perform Forced Recalibration**| `0x362F`        | Initiates a manual recalibration using a known CO2 level.     | Recalibrate for accuracy maintenance.    |
| **Persist Settings**            | `0x3615`        | Saves the current settings to non-volatile memory.            | Ensure settings are retained on restart. |
| **Perform Self-Test**           | `0x3639`        | Runs an internal self-check to verify sensor functionality.   | Diagnose potential sensor issues.        |
| **Enter Sleep Mode**            | `0x36E0`        | Puts the sensor into a low-power sleep state.                 | Reduce power consumption when inactive.  |


References: 
RpiPico: https://www.circuitstate.com/news/rp2040-pico-all-new-microcontroller-and-development-board-from-raspberry-pi/ <br>
git: https://github.com/sparkfun/SparkFun_SCD4x_Arduino_Library/tree/main <br>
Datasheet: https://cdn.sparkfun.com/assets/d/4/9/a/d/Sensirion_CO2_Sensors_SCD4x_Datasheet.pdf <br>
SCD40: https://www.sparkfun.com/products/22395 <br>

Sensor Diagram: https://cdn.sparkfun.com/assets/9/b/f/5/2/SparkFun_Qwiic_CO2_Sensor_SCD40.pdf <br>

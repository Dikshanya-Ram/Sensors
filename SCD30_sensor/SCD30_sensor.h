/**
 * Based on Hunter Adams (vha3@cornell.edu) MPU code
 * 
 *
 * https://sensirion.com/media/documents/4EAF6AF8/61652C3C/Sensirion_CO2_Sensors_SCD30_Datasheet.pdf
 *
 * VDD (Sensor) ---- PIN 36 (Vout - 3v3)
 * GND (any gnd) --- PIN 18
 *  
 * SDA (Sensor) --- PIN 11 (GPIO 8) I2C0 SDA
 * SCL (Sensor) --- PIN 12 (GPIO 9) I2C0 SCL
 * 
 */
  
  // Configuration
  #define I2C_PORT i2c0 // set to i2c0
  #define RDY_PIN 7 // Pin 10 - GPIO 7
  #define SDA_PIN  8 // Pin 11 - GPIO 8
  #define SCL_PIN  9 // Pin 12 - GPIO 9
  
  #define I2C_BAUD_RATE 100000 // Max - 100KHz : advised below 50KHz
  #define SCD30_ADDR 0x61  // Sensor address (7-bit, shifted left 1 bit in i2c functions) // verified with datasheet

//  // Fixed point data type
//  typedef signed int fix15 ;
//  #define multfix15(a,b) ((fix15)(((( signed long long)(a))*(( signed long long)(b)))>>16)) 
//  #define float2fix15(a) ((fix15)((a)*65536.0f)) // 2^16
//  #define fix2float15(a) ((float)(a)/65536.0f) 
//  #define int2fix15(a) ((a)<<16)
//  #define fix2int15(a) ((a)>>16)
//  #define divfix(a,b) ((fix15)(((( signed long long)(a) << 16 / (b)))))
 
//  // Parameter values
//  #define oneeightyoverpi 3754936
//  #define zeropt001 65
//  #define zeropt999 65470
//  #define zeropt01 655
//  #define zeropt99 64880
//  #define zeropt1 6553
//  #define zeropt9 58982

 // Function Declarations
  void SCD30_reset();
  void SCD30_start_measurement();
  void SCD30_set_measurement_interval();
  bool SCD30_data_ready();
  int SCD30_read_measurement(float *co2, float *temperature, float *humidity);
  float unpack_scd30_float(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);
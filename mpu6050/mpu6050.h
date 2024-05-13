#ifndef _mpu6050_
#define _mpu6050_

#include <stdbool.h>
#include <stdio.h>
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include <math.h>

//I2C INTERFACE//
#define SDA_Pin 26
#define SCL_Pin 27

typedef struct MPU6050_REG
{
    const uint8_t address;      //device address
    const uint8_t who_i_am_add;
    const uint8_t reset_add;    //reset address
    const uint8_t accel_add;    //accelerator data address register
    const uint8_t gyro_add;     //gryoscope data address register
    const uint8_t temp_add;     //temperature data address register
    const uint8_t gyro_res;  // gyroscope resolution config and calibration
    const uint8_t acc_config;   // accelerometer resolution config and calibration
    const uint8_t XA_TEST;      //XA_TEST and XG_test register 
    const uint8_t YA_TEST;      //YA_TEST and YG_test register
    const uint8_t ZA_TEST;      //ZA_TEST and ZG_test register
    const uint8_t A_TEST;       //second accelerometer test register XA_TEST[1:0]
}MPU6050_REG;

typedef struct MPU6050
{
    int16_t acceleration[3]; // X - Y - Z Acceleration
    int16_t gyro[3];         // X - Y - Z Gyroscope Data
    float temp;              // Temperature

    float accel_convert[3]; // converted acceleration measures
    double gyro_convert[3];  // converted gyroscope measures 

    uint8_t accel_res;   // 0=> 16384, 1=>8192, 2=>4096, 3=>2048  
    uint8_t gyro_res;    // 0=> 131,   1=>65.5, 2=>32.8, 3=>16.4     
}MPU6050;

typedef struct MPU6050_SELFTEST
{
    uint8_t STR_X, STR_Y, STR_Z;            //STR => SELFT-TEST-RESPONSE
    double FT_X, FT_Y, FT_Z;                //FT => FACTORY TRIMMER
    uint8_t X_TEST, Y_TEST, Z_TEST, A_TEST; // TEST REGISTER
    double X_ERROR, Y_ERROR, Z_ERROR;       //Errors given in %
}MPU6050_SELFTEST;


//write_i2c()//
/// @param i2c_address => device address
/// @param reg => device register(place to write data)
/// @param data => data to write in register  
void i2c_write_reg(uint8_t i2c_address, uint8_t reg, uint8_t data);

/// mpu I2C init//
/// @param mpu6050 =>mpu6050 data structure
void mpu_init(MPU6050* mpu6050); 

//who_i_am//
///@brief save MPU6050 I2C address in mpu_address param
void who_i_am(uint8_t* mpu_address); 

//device reset//
void mpu_reset(); 

//mpu_setresolution
/// @param gyro_res => gyrometer resolution <=> ±250 ±500g ±1000g ±2000g  <=user enter=> 0, 1, 2, 3
/// @param acc_res => acceleroeter resolution <=> ±2g, ±4g, ±8g, or ±16g  <=user enter=> 0, 1, 2, 3 
/// @param mpu6050 => mpu6050 data structure 
void mpu_setresolution(uint8_t gyro_res, uint8_t acc_res, MPU6050* mpu6050); 

//mpu_read
/// @brief data from sensor
/// @param mpu6050 => mpu6050 data structure 
void mpu_read(MPU6050* mpu6050); // read data from mpu6050

/// @brief mpu6050 accelerometer sensor self test, return true if selftest goes properly and false otherwise//
/// @param mpu6050 => mpu6050 data structure 
/// @param mpu6050_accel_st => mpu6050 accel self test data structure
bool mpu_accel_st(MPU6050* mpu6050, MPU6050_SELFTEST* mpu6050_accel_st); 

/// @brief => mpu6050 gyrometer sensor self test, return true if selftest goes properly and false otherwise//
/// @param mpu6050 => mpu6050 data structure 
/// @param mpu6050_gyro_st => mpu6050 gyro self test data structure
bool mpu_gyro_st(MPU6050* mpu6050, MPU6050_SELFTEST* mpu6050_gyro_st); 

/// @brief => convert data measured as ADC value into acceleration in [m/s2] and gyroscope [*]
/// @param mpu6050 => mpu6050 data structure 
void mpu_convert(MPU6050* mpu6050);

#endif
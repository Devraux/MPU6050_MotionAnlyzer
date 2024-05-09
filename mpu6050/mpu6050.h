#ifndef _mpu6050_
#define _mpu6050_

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "hardware/uart.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

//I2C INTERFACE//
#define SDA_Pin 26
#define SCL_Pin 27

typedef struct MPU6050_REG
{
    const uint8_t address; //device address
    const uint8_t who_i_am_add;
    const uint8_t reset_add; //reset address
    const uint8_t accel_add; //accelerator data address register
    const uint8_t gyro_add; //gryoscope data address register
    const uint8_t temp_add; //temperature data address register
    const uint8_t gyro_config; // gyroscope resolution config and calibration
    const uint8_t acc_config; // accelerometer resolution config and calibration
}MPU6050_REG;

typedef struct MPU6050
{
    int16_t acceleration[3]; // X - Y - Z Acceleration
    int16_t gyro[3];         // X - Y - Z Gyroscope Data
    float temp;              // Temperature

    uint8_t accel_config;   // 0=> 16384, 1=>8192, 2=>4096, 3=>2048  
    uint8_t gyro_config;    // 0=>131, 1=>65.5, 2=>32.8, 3=>16.4     
}MPU6050;

typedef struct MPU6050_SELFTEST
{
    int16_t accel_TEST[3];
    int16_t gyro_TEST[3];
}MPU6050_SELFTEST;


//write_i2c()//
//@param i2c_address => device address
//@param reg => device register(place to write data)
//@param data => data to write in register  
void i2c_write_reg(uint8_t i2c_address, uint8_t reg, uint8_t data);

//mpu I2C init//
//@param mpu6050 =>mpu6050 data structure
void mpu_init(MPU6050* mpu6050); 

// mpu6050 sensor self test, return true if selftest goes properly and false otherwise//
bool mpu_self_test(); 

//who_i_am//
// save MPU6050 I2C address in mpu_address param
void who_i_am(uint8_t* mpu_address); 

//device reset//
void mpu_reset(); 

//mpu_setresolution
//@param gyro_res => gyrometer resolution
//@param acc_res => acceleroeter resolution <=> ±2g, ±4g, ±8g, or ±16g  <=user enter=> 0, 1, 2, 3 
//@param mpu6050 => mpu6050 data structure <=> ±250 ±500g ±1000g ±2000g <=user enter=> 0, 1, 2, 3
void mpu_setresolution(uint8_t gyro_res, uint8_t acc_res, MPU6050* mpu6050); 

//mpu_read
//reaad data from sensor
//@param mpu6050 => mpu6050 data structure 
void mpu_read(MPU6050* mpu6050); // read data from mpu6050

#endif
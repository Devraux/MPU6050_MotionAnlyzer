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
    int16_t acceleration[3];
    int16_t gyro[3];
    float temp;
}MPU6050;

typedef struct MPU6050_SELFTEST
{
    int16_t accel_TEST[3];
    int16_t gyro_TEST[3];
}MPU6050_SELFTEST;


//write_i2c()//
//i2c_address => device address, reg => device register(place to write data), data => data to write in register  
void write_i2c(uint8_t i2c_address, uint8_t reg, uint8_t data);
void mpu_init(); //mpu I2C init
bool mpu_self_test(); // mpu6050 sensor self test, return true if selftest goes properly and false otherwise
void who_i_am(uint8_t* mpu_address); // get I2C address
void mpu_reset(); // device reset
void mpu_setresolution(uint8_t gyro_res, uint8_t acc_res); //±2g, ±4g, ±8g, or ±16g 
void mpu_read(MPU6050* mpu6050); // read data from mpu6050

#endif
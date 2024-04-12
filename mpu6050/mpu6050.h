#ifndef _mpu6050_
#define _mpu6050_

//#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "hardware/uart.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"


#define address 0x68 //I2C address
#define reset 0x6B //reset address
#define accel_add 0x3B //accelerator data address register
#define gyro_add 0x43 //gryoscope data address register
#define temp_add 0x41 //temperature data address register
#define SDA_Pin 26
#define SCL_Pin 27

void mpu_init(); //mpu I2C init
void mpu_cal(); // mpu6050 sensor self test to get accuraate results
void mpu_reset(); // reset
void who_i_am();
void mpu_read(int16_t accel[3], int16_t gyro[3], int16_t *temp); //read data from mpu6050


#endif
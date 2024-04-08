#include "mpu6050.h"



void mpu_reset()
{
    uint8_t buf[] = {reset, 0x80}; //0x80 => 1000 0000
    i2c_write_blocking(i2c1, address, buf, sizeof(buf), false);
}

void mpu_init()
{
    i2c_init(i2c1,400000);
    gpio_set_function(SDA_Pin, GPIO_FUNC_I2C); //27 and 26
    gpio_set_function(SCL_Pin, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_Pin);
    gpio_pull_up(SCL_Pin);

    mpu_reset();
}

void mpu_read(int16_t accel[3], int16_t gyro[3], int16_t *temp)
{
    uint8_t buffer[6];

    mpu_cal(); //calibration

    i2c_write_blocking(i2c0, address, (uint8_t*)accel_add, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c0, address, buffer, 6, false);

    for (int i = 0; i < 3; i++)
    {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }


    i2c_write_blocking(i2c_default, address, (uint8_t*)gyro_add, 1, true);
    i2c_read_blocking(i2c_default, address, buffer, 6, false);  

    for (int i = 0; i < 3; i++)
    {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }
    

    i2c_write_blocking(i2c_default, address,(uint8_t*)temp_add, 1, true);
    i2c_read_blocking(i2c_default, address, buffer, 2, false);  

    *temp = buffer[0] << 8 | buffer[1];

    
}
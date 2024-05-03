#include "mpu6050.h"

MPU6050_REG mpu6050_reg = {
    .address = 0x68, //device address
    .who_i_am_add = 0x75,
    .reset_add = 0x6B, //reset address
    .accel_add = 0x3B, //accelerator data address register
    .gyro_add = 0x43, //gryoscope data address register
    .temp_add = 0x41, //temperature data address register
};

void who_i_am(uint8_t* mpu_address)
{
    uint8_t who_i_am;
    i2c_write_blocking(i2c1, mpu6050_reg.address, &mpu6050_reg.who_i_am_add, 2, true); 
    i2c_read_blocking(i2c1, mpu6050_reg.address, &who_i_am, 2, false); 
    *mpu_address = who_i_am;

    if (who_i_am != 0x68) 
        printf("Address is not 0x68:, addres is: %d", who_i_am);
    else 
        printf("Address is 0x68, adress is : %d", who_i_am);
}

void mpu_reset()
{
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(i2c1, mpu6050_reg.address, buf, 2, false);
    sleep_ms(50);
    uint8_t buf2[] = {0x6B, 0x80}; //0x80 => 1000 0000
    i2c_write_blocking(i2c1, mpu6050_reg.address, &buf2[0], 1, true);
    i2c_write_blocking(i2c1, mpu6050_reg.address, &buf2[1], 1, false);

}

void mpu_init()
{
    i2c_init(i2c1, 400000);
    gpio_set_function(SDA_Pin, GPIO_FUNC_I2C); //27 and 26
    gpio_set_function(SCL_Pin, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_Pin);
    gpio_pull_up(SCL_Pin);

    mpu_reset();
}

void mpu_read(MPU6050* mpu6050)
{
    uint8_t buffer[6];
    
    i2c_write_blocking(i2c1, mpu6050_reg.address, &mpu6050_reg.accel_add, 1, true); 
    i2c_read_blocking(i2c1, mpu6050_reg.address, buffer, 6, false);

    for (int i = 0; i < 3; i++)
    {
        mpu6050->acceleration[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

   
    i2c_write_blocking(i2c1,mpu6050_reg.address, &mpu6050_reg.gyro_add, 1, true);
    i2c_read_blocking(i2c1, mpu6050_reg.address, buffer, 6, false);  

    for (int i = 0; i < 3; i++)
    {
        mpu6050->gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }


    i2c_write_blocking(i2c1,mpu6050_reg.address, &mpu6050_reg.temp_add, 1, true);
    i2c_read_blocking(i2c1, mpu6050_reg.address, buffer, 2, false);  

    mpu6050->temp = buffer[0] << 8 | buffer[1];
}


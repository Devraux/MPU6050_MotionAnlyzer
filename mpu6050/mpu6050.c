#include "mpu6050.h"

MPU6050_REG mpu6050_reg = {
    .address = 0x68, //device address
    .who_i_am_add = 0x75,
    .reset_add = 0x6B, //reset address
    .accel_add = 0x3B, //accelerator data address register
    .gyro_add = 0x43, //gryoscope data address register
    .temp_add = 0x41, //temperature data address register
    .acc_config = 0x1C, //accelerometer resolution config regisrer and calibration
    .gyro_config = 0x1B // gyroscope resolution config register and calibration
};

void write_i2c(uint8_t i2c_address, uint8_t reg, uint8_t data)
{
    uint8_t tab[] = {reg, data};
    i2c_write_blocking(i2c1, i2c_address, tab, sizeof(tab), false);
}

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

    mpu_setresolution(1, 3); // set +-16 g and +- resolution
}

void mpu_read(MPU6050* mpu6050)
{
    uint8_t buffer[6];
    int16_t temperature = 0;

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

    temperature = buffer[0] << 8 | buffer[1];
    mpu6050->temp = (temperature / 340.f) + 36.53;
}

bool mpu_self_test()
{
    MPU6050_SELFTEST mpu6050_selftest;



    return true;
}

void mpu_setresolution(uint8_t gyro_res, uint8_t acc_res)
{
    uint8_t check, resolution = 0;

    switch(gyro_res)
    {
        case 0: //+- 250
            resolution = 0b00000000;
            break;

        case 1: //+- 500
            resolution = 0b00001000;
            break;

        case 2: //+- 1000
            resolution = 0b00010000;
            break;

        case 3: //+- 2000
            resolution = 0b00011000;
            break;
    }

    // SET GYRO RESOLUTION
    write_i2c(mpu6050_reg.address, mpu6050_reg.gyro_config, resolution);


    switch(acc_res)
    {
        case 0: //+- 2
            resolution = 0b00000000;
            break;

        case 1: //+- 4
            resolution = 0b00001000;
            break;

        case 2: //+- 8
            resolution = 0b00010000;
            break;

        case 3: //+- 16
            resolution = 0b00011000;
            break;
    }
    
    // SET ACCEL RESOLUTION
    write_i2c(mpu6050_reg.address,mpu6050_reg.acc_config ,resolution);

    //CHECK GYRO RESOLUTION
    i2c_write_blocking(i2c1, mpu6050_reg.address, &mpu6050_reg.gyro_config, 1, true);
    i2c_read_blocking(i2c1, mpu6050_reg.address, &check ,1 , false);
    if(check != resolution)
        printf("\ncheck:%d\n", check);


    //CHECK ACC RESOLUTION
    i2c_write_blocking(i2c1, mpu6050_reg.address, &mpu6050_reg.acc_config, 1, true);
    i2c_read_blocking(i2c1, mpu6050_reg.address, &check ,1 , false); 
    if(check != resolution)
        printf("\ncheck:%d\n", check);

}
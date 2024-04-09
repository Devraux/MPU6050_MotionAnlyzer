#include "mpu6050.h"

static int address = 0x68;
void mpu_reset()
{
    uint8_t buf[] = {0x6B, 0x80}; //0x80 => 1000 0000
    i2c_write_blocking(i2c1, address, buf, 2, false);
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
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c1, address, &val, 1, true); 
    i2c_read_blocking(i2c1, address, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }
    //printf("%d", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);

    val = 0x43;
    i2c_write_blocking(i2c1, address, &val, 1, true);
    i2c_read_blocking(i2c1, address, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    val = 0x41;
    i2c_write_blocking(i2c1, address, &val, 1, true);
    i2c_read_blocking(i2c1, address, buffer, 2, false);  // False - finished with bus

    *temp = buffer[0] << 8 | buffer[1];
}
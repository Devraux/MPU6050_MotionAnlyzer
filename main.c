#include "main.h"
//#include "mylib/mylib.h"

int main()
{
    stdio_init_all();
    mpu_init();
    MPU6050 mpu6050;

    
    while(1)
    {
        mpu_read(&mpu6050);
        printf("Acc. X = %d, Y = %d, Z = %d\n", mpu6050.acceleration[0], mpu6050.acceleration[1], mpu6050.acceleration[2]);
        printf("Gyro. X = %d, Y = %d, Z = %d\n", mpu6050.gyro[0], mpu6050.gyro[1], mpu6050.gyro[2]);
        printf("Temp. = %f\n", mpu6050.temp);
        sleep_ms(1000);
    }
    return 0;
}
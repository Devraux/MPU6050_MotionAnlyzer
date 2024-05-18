#include "main.h"
//#include "mylib/mylib.h"

int main()
{
    stdio_init_all();
    sleep_ms(5000);
    MPU6050_RAW mpu6050_raw = {0};
    MPU6050 mpu6050 = {0};
    MPU6050_DATA mpu6050_data = {0};
    mpu6050_data.mpu6050 = mpu6050;
    mpu6050_data.mpu6050_raw = mpu6050_raw;

    mpu_init(&mpu6050_raw, &mpu6050, &mpu6050_data);
        
    while(1)
    {
        //buffer_print(&mpu6050_data.mpu6050.accelbuffer);
        //printf("%f\n", mpu6050_data.mpu6050.accel[0]);
    }
    return 0;
}
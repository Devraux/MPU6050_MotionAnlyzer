#include "main.h"
//#include "mylib/mylib.h"

int main()
{
    stdio_init_all();
    sleep_ms(5000);
    MPU6050 mpu6050 = {0};
    mpu_init(&mpu6050);

        
    while(1)
    {
        //mpu_read(&mpu6050);
        //printf("%f,%f,%f\n", mpu6050.mpu6050_data.accelwithoutgravity[0], mpu6050.mpu6050_data.accelwithoutgravity[1], mpu6050.mpu6050_data.accelwithoutgravity[2]);
        //buffer_print(&mpu6050.mpu6050_data.accelbuffer);
        //mpu_read(&mpu6050);
        buffer_print(&mpu6050.mpu6050_data.accelbuffer);
        //sleep_ms(100);
    }
    return 0;
}
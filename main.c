#include "main.h"
//#include "mylib/mylib.h"
#include <pico/double.h>
int main()
{
    stdio_init_all();
    sleep_ms(5000);
    MPU6050 mpu6050 = {0};
    mpu_init(&mpu6050);


    while(1)
    {
        //printf("%f,%f,%f\n", mpu6050.mpu6050_data.accel_no_gravity[0], mpu6050.mpu6050_data.accel_no_gravity[1], mpu6050.mpu6050_data.accel_no_gravity[2]);
        //printf("%f\n", mpu6050.mpu6050_data.distance);
        //buffer_print(&mpu6050.mpu6050_data.accelbuffer);
        //printf("X:%f, Y:%f, Z:%f\n",mpu6050.mpu6050_data.accel_convert[0], mpu6050.mpu6050_data.accel_convert[1], mpu6050.mpu6050_data.accel_convert[2]);
        printf("%f,%f,%f\n", mpu6050.mpu6050_data.theta_pitch, mpu6050.mpu6050_data.theta_roll, mpu6050.mpu6050_data.theta_yaw);
        //printf("%f\n", mpu6050.mpu6050_data.distance);
        sleep_ms(105);
    }
    return 0;
}
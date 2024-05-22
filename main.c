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
        //if(mpu6050.mpu6050_data.accelbuffer.Counter == 25)
        //buffer_print(&mpu6050.mpu6050_data.accelbuffer);
        //printf("%f\n", mpu6050.mpu6050_data.distance);
        //printf("%d\n", mpu6050.mpu6050_data.accel_no_offset[0]);
        //printf("%d,%d,%d\n", mpu6050.mpu6050_data.accel_no_offset[0], mpu6050.mpu6050_data.accel_no_offset[1], mpu6050.mpu6050_data.accel_no_offset[2]);
        printf("%d\n", mpu6050.mpu6050_data.accel_mod_no_gravity);
        sleep_ms(105);
    }
    return 0;
}
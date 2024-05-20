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
        printf("%f\n", 9.81*mpu6050.mpu6050_data.accelwithoutgravity[0]);
        sleep_ms(505);
    }
    return 0;
}
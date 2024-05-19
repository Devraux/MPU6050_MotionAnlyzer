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
        printf("%f\n", mpu6050.mpu6050_data.accel[0]);
        sleep_ms(100);
    }
    return 0;
}
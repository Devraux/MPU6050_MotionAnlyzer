#include "main.h"
//#include "mylib/mylib.h"

int main()
{
    stdio_init_all();
    //sleep_ms(5000);
    MPU6050 mpu6050 = {0};


    mpu_init(&mpu6050);
        
    while(1)
    {
        //buffer_print(&mpu6050.mpu6050_data.accelbuffer);
        mpu_read_raw(&mpu6050);
        printf("%d\n", mpu6050.mpu6050_raw.acceleration[1]);
        sleep_ms(1000);
    }
    return 0;
}
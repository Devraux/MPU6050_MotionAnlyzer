#include "main.h"
//#include "mylib/mylib.h"

int main()
{
    stdio_init_all();
    mpu_init();
    int16_t acceleration[3], gyro[3], temp;


    while(1)
    {
        mpu_read(acceleration, gyro, &temp);
        printf("Acc. X = %d, Y = %d, Z = %d\n", acceleration[0], acceleration[1], acceleration[2]);
        printf("Gyro. X = %d, Y = %d, Z = %d\n", gyro[0], gyro[1], gyro[2]);
        printf("Temp. = %f\n", (temp / 340.0) + 36.53);
    }
    return 0;
}
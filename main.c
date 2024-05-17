#include "main.h"
//#include "mylib/mylib.h"

int main()
{
    stdio_init_all();
    MPU6050_RAW mpu6050_raw = {0};
    MPU6050_SELFTEST mpu6050_accel_st, mpu6050_gyro_st = {0};
    MPU6050 mpu6050 = {0};
    mpu_init(&mpu6050_raw);
    sleep_ms(5000);
    
    while(1)
    {
        //mpu_read_raw(&mpu6050_raw);
        // RAW DATA FORM EMBEDDED ADC//
        //printf("Acc. X = %d, Y = %d, Z = %d\n", mpu6050_raw.acceleration[0], mpu6050_raw.acceleration[1], mpu6050_raw.acceleration[2]);
        //printf("Gyro. X = %d, Y = %d, Z = %d\n", mpu6050_raw.gyro[0], mpu6050_raw.gyro[1], mpu6050_raw.gyro[2]);
        //printf("Temp. = %f\n", mpu6050_raw.temp);

        //converted data 
       //printf("Acc. X = %f, Y = %f, Z = %f\n", mpu6050_raw.accel_convert[0],mpu6050_raw.accel_convert[1], mpu6050_raw.accel_convert[2]);
        //printf("Gyro. X = %f, Y = %f, Z = %f\n", mpu6050_raw.gyro_convert[0], mpu6050_raw.gyro_convert[1], mpu6050_raw.gyro_convert[2]);

        // visual app RAW FORMAT DATA
        //printf("%d,%d,%d\n", mpu6050_raw.acceleration[0], mpu6050_raw.acceleration[1], mpu6050_raw.acceleration[2]); //plot app formula
        
        // visual app converted FORMAT DATA
        //printf("%f,%f,%f\n", mpu6050_raw.accel_convert[0], mpu6050_raw.accel_convert[1], mpu6050_raw.accel_convert[2]); 

        //mpu_statistic(&mpu6050_raw);
        mpu_read(&mpu6050_raw, &mpu6050);
        //printf("Acc. X = %f, Y = %f, Z = %f\n", mpu6050.accel[0],mpu6050.accel[1], mpu6050.accel[2]);
        printf("%f,%f,%f\n", 9.81*mpu6050.accelwithoutgravity[0],9.81*mpu6050.accelwithoutgravity[1], 9.81*mpu6050.accelwithoutgravity[2]);
        //printf("Gyro. X = %f, Y = %f, Z = %f\n", mpu6050.gyro[0], mpu6050.gyro[1], mpu6050.gyro[2]);

        mpu_get_distance(&mpu6050_raw, &mpu6050);
        //printf("Acc. X = %f, Y = %f, Z = %f\n", mpu6050.accelwithoutgravity[0],mpu6050.accelwithoutgravity[1], mpu6050.accelwithoutgravity[2]);
        //printf("%f\n", mpu6050.distance);
        
        sleep_ms(100);
    }
    return 0;
}
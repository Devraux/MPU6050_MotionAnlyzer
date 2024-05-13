#include "main.h"
//#include "mylib/mylib.h"

int main()
{
    stdio_init_all();
    MPU6050 mpu6050;
    MPU6050_SELFTEST mpu6050_accel_st, mpu6050_gyro_st;
    mpu_init(&mpu6050);
    sleep_ms(5000);
    mpu_accel_st(&mpu6050, &mpu6050_accel_st);
    mpu_gyro_st(&mpu6050, &mpu6050_gyro_st);
    //printf("X_ACC_ERR: %f\nY_ACC_ERR: %f\nZ_ACC_ERR: %f\n", mpu6050_accel_st.X_ERROR, mpu6050_accel_st.Y_ERROR, mpu6050_accel_st.Z_ERROR);
    //printf("X_GYRO_ERR: %f\nY_GYRO_ERR: %f\nZ_GYRO_ERR: %f\n", mpu6050_gyro_st.X_ERROR, mpu6050_gyro_st.Y_ERROR, mpu6050_gyro_st.Z_ERROR);

    while(1)
    {
        mpu_read(&mpu6050);
        // RAW DATA FORM EMBEDDED ADC//
        //printf("Acc. X = %d, Y = %d, Z = %d\n", mpu6050.acceleration[0], mpu6050.acceleration[1], mpu6050.acceleration[2]);
        //printf("Gyro. X = %d, Y = %d, Z = %d\n", mpu6050.gyro[0], mpu6050.gyro[1], mpu6050.gyro[2]);
        //printf("Temp. = %f\n", mpu6050.temp);

        //converted data 
        //printf("Acc. X = %f, Y = %f, Z = %f\n", mpu6050.accel_convert[0], mpu6050.accel_convert[1], mpu6050.accel_convert[2]);
        //printf("Gyro. X = %f, Y = %f, Z = %f\n", mpu6050.gyro_convert[0], mpu6050.gyro_convert[1], mpu6050.gyro_convert[2]);

        // visual app RAW FORMAT DATA
        //printf("%d,%d,%d\n", mpu6050.acceleration[0], mpu6050.acceleration[1], mpu6050.acceleration[2]); //plot app formula
        
        // visual app converted FORMAT DATA
        printf("%f,%f,%f\n", mpu6050.accel_convert[0], mpu6050.accel_convert[1], mpu6050.accel_convert[2]); 
        sleep_ms(100);
    }
    return 0;
}
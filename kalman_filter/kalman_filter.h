#ifndef _kalman_filter_
#define _kalman_fliter_

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

typedef struct KALMAN //kalman coeficients
{
    uint16_t n;     //time stamp
    double K;       //Kalman gain 0 < k < 1
    double z_n;     // data measured in n => current value
    double r_n;      // measurement variance
    
 
}KALMAN;


/// @brief filter input data using kalman filter
/// @param input_data
/// @param kalman => filter data structure
int8_t kalman_accel(int8_t input_data, KALMAN* kalman);

/// @brief filter input data using kalman filter 
/// @param input_data
/// @return int8_t data => computed data => filtered gyroscope value 
int8_t kalman_gyro(int8_t input_data, KALMAN* kalman);

#endif
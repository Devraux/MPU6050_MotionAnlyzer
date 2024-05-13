#include "kalman_filter.h"

int8_t kalman_accel(int8_t input_data, KALMAN* kalman)
{
    switch(kalman->n)
    {
        case 1:
        kalman->x[0] = input_data;
        kalman->n++;
        break;

        case 2:

        kalman->n++;
        break;

        default:

        kalman->n++;
        if(kalman->n > (sizeof(int16_t) - 1))
            kalman->n = 0;
    } 
}

int8_t kalman_gyro(int8_t input_data, KALMAN* kalman)
{
    
}

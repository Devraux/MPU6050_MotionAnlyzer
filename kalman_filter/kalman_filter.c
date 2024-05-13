#include "kalman_filter.h"

int8_t kalman_accel(int8_t input_data, KALMAN* kalman)
{
    switch(kalman->n)
    {
        case 1: //first iteration
        kalman->n++;
        break;

        case 2: //second iteration

        kalman->n++;
        break;

        default: //next interation

        kalman->n++;
        if(kalman->n > (sizeof(int16_t) - 1))
            kalman->n = 0;
    } 
}

int8_t kalman_gyro(int8_t input_data, KALMAN* kalman)
{

}

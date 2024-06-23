#include "ringbuffer.h"

void Ring_buffer_init(RINGBUFFER* ringbuffer, uint16_t buffer_size)
{
    ringbuffer->DataX = (float*)malloc(buffer_size * sizeof(float));
    ringbuffer->DataY = (float*)malloc(buffer_size * sizeof(float));
    ringbuffer->DataZ = (float*)malloc(buffer_size * sizeof(float));
    
    ringbuffer->Buffer_Size = buffer_size;
    ringbuffer->Head = 0;
    ringbuffer->Tail = 0;
}

void Ring_buffer_push(RINGBUFFER* ringbuffer, float dataX, float dataY, float dataZ)
{
    ringbuffer->DataX[ringbuffer->Head] = dataX;
    ringbuffer->DataY[ringbuffer->Head] = dataY;
    ringbuffer->DataZ[ringbuffer->Head] = dataZ;

    ringbuffer->Head = (ringbuffer->Head + 1) % ringbuffer->Buffer_Size;
    ringbuffer->Counter++;

    if(ringbuffer->Counter > ringbuffer->Buffer_Size)
        ringbuffer->Counter = 0; // data overflow
}

void Ring_buffer_pop(RINGBUFFER* ringbuffer, float* dataX, float* dataY, float* dataZ)
{
    *dataX = ringbuffer->DataX[ringbuffer->Tail];
    *dataY = ringbuffer->DataY[ringbuffer->Tail];
    *dataZ = ringbuffer->DataZ[ringbuffer->Tail];

    ringbuffer->Tail = (ringbuffer->Tail + 1) % ringbuffer->Buffer_Size;
    ringbuffer->Counter--;

    if(ringbuffer->Counter <= 0)
        ringbuffer->Counter = 0;
}

uint16_t Ring_buffer_get_capacity(RINGBUFFER* ringbuffer)
{
    return ringbuffer->Counter;
}

void Ring_buffer_clear(RINGBUFFER* ringbuffer)
{
    ringbuffer->Counter = 0;
    ringbuffer->Head = 0;
    ringbuffer->Tail = 0;
}

void buffer_print(RINGBUFFER* ringbuffer)
{
    for(uint16_t i = ringbuffer->Tail; i < ringbuffer->Head; i++)
    {
       printf("%d: %f\n", i, ringbuffer->DataX[i]);
       printf("%d: %f\n", i, ringbuffer->DataY[i]);
       printf("%d: %f\n", i, ringbuffer->DataZ[i]);
       printf("---------------=----------------\n");
    }
    
}
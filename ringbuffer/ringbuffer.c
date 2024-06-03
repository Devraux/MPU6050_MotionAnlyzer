#include "ringbuffer.h"

void Ring_buffer_init(RINGBUFFER* ringbuffer, uint16_t buffer_size)
{
    ringbuffer->Buffer_Size = buffer_size;
    ringbuffer->Data = (float*)malloc(buffer_size * sizeof(float));
    ringbuffer->Head = 0;
    ringbuffer->Tail = 0;
}

void Ring_buffer_push(RINGBUFFER* ringbuffer, float data)
{
    ringbuffer->Data[ringbuffer->Head] = data;
    ringbuffer->Head = (ringbuffer->Head + 1) % ringbuffer->Buffer_Size;
    ringbuffer->Counter++;

    if(ringbuffer->Counter > ringbuffer->Buffer_Size)
        ringbuffer->Counter = 0; // data overflow
}

void Ring_buffer_pop(RINGBUFFER* ringbuffer, float* data)
{
    *data = ringbuffer->Data[ringbuffer->Tail];
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
       printf("%d: %f\n", i, ringbuffer->Data[i]);

    printf("All data printed");
}
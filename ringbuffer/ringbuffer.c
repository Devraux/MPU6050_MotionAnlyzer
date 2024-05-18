#include "ringbuffer.h"

void Ring_buffer_init(RINGBUFFER* ringbuffer, float* data, uint16_t buffer_size)
{
    ringbuffer->Buffer_Size = buffer_size;
    ringbuffer->Data = data;
    ringbuffer->Head = 0;
    ringbuffer->Tail = 0;
}

void Ring_buffer_push(RINGBUFFER* ringbuffer, float data)
{
    ringbuffer->Data[ringbuffer->Head] = data;
    ringbuffer->Head = (ringbuffer->Head + 1) % ringbuffer->Buffer_Size;
    ringbuffer->Counter++;
}

void Ring_buffer_pop(RINGBUFFER* ringbuffer, float* data)
{
    *data = ringbuffer->Data[ringbuffer->Tail];
    ringbuffer->Tail = (ringbuffer->Tail + 1) % ringbuffer->Buffer_Size;
    ringbuffer->Tail--;
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
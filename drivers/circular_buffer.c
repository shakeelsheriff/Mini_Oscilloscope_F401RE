#include "circular_buffer.h"

void circular_buffer_init(ring_struct *sample)
{
    sample->reader = 0;
    sample->writer = 0;
    sample->count  = 0;
}

void write_to_ring(uint16_t adc_value, ring_struct *sample)
{
    if (is_buffer_full(sample))
    {
        return;
    }
    sample->ring_buffer[sample->writer++] = adc_value;
    if (sample->writer >= BUFFERSIZE)
    {
        sample->writer = 0;
    }
    sample->count++;
}

void read_from_ring(uint16_t *adc_samples, ring_struct *sample)
{
    if (is_data_available(sample))
    {
        *adc_samples = sample->ring_buffer[sample->reader++];
        if (sample->reader >= BUFFERSIZE)
        {
            sample->reader = 0;
        }
        sample->count--;
    }
}

bool is_data_available(ring_struct *sample)
{
    return (sample->count != 0);
}

bool is_buffer_full(ring_struct *sample)
{
    return (sample->count >= BUFFERSIZE);
}

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define BUFFERSIZE  256

typedef struct {
    uint16_t ring_buffer[BUFFERSIZE];
    uint16_t writer;
    uint16_t reader;
    uint16_t count;
} ring_struct;

void circular_buffer_init(ring_struct *sample);
void write_to_ring(uint16_t adc_value, ring_struct *sample);
void read_from_ring(uint16_t *adc_samples, ring_struct *sample);
bool is_data_available(ring_struct *sample);
bool is_buffer_full(ring_struct *sample);

#endif /* CIRCULAR_BUFFER_H */

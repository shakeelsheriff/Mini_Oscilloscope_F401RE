#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "main.h"
#include<stdbool.h>
#define MAX_BUFFER_SIZE 512
#define HIGH_TRIGGER_LEVEL	1910
#define LOW_TRIGGER_LEVEL	1810
// structure to hold samples
  typedef struct{
	  uint16_t data[MAX_BUFFER_SIZE];
	  int front;
	  int rear;
  }sample_buffer;

// enumerator for main application state machine states
  typedef enum{
	  SYSTEM_INIT,
	  CONFIGURE_TIMEBASE,
	  WAIT_TRIGGER,
	  SAMPLE_ADC,
	  SEND
  }RING_BUFFER_STATES;

  //enum for edges
  typedef enum{
	  RAISING_EDGE,
	  FALLING_EDGE
  }Trigger_states;
void RingBuffer_Init(sample_buffer *sample);
void enqueue_sample(uint16_t adc_value,sample_buffer *sample);
uint16_t dequeue_sample(sample_buffer *sample);
bool is_ring_buffer_full(sample_buffer *sample);
bool is_ring_buffer_empty(sample_buffer *sample);

#endif

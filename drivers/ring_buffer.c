#include "ring_buffer.h"

void RingBuffer_Init(sample_buffer *sample){
	//configure ring buffer
	  sample->front = -1;
	  sample->rear = -1;
}
void enqueue_sample(uint16_t adc_value,sample_buffer *sample){
	if(is_ring_buffer_full(sample))
	{
		return;
	}
	if(is_ring_buffer_empty(sample)){
		sample->front = sample->rear = 0;
		sample->data[sample->rear] = adc_value;
	}
	else{
		sample->rear = (sample->rear+1) % MAX_BUFFER_SIZE;
		sample->data[sample->rear] = adc_value;
	}
}

uint16_t dequeue_sample(sample_buffer *sample){
	if(is_ring_buffer_empty(sample))
	{
	    return 0;
	}
	uint16_t value;
	value = sample->data[sample->front];
	if(sample->front == sample->rear){
		sample->front = sample->rear = -1;
	}
	else{
		sample-> front = (sample->front+1)% MAX_BUFFER_SIZE;
	}
	return value;
}

bool is_ring_buffer_full(sample_buffer *sample){
	if(((sample->rear + 1) % MAX_BUFFER_SIZE) == sample->front){
		return true;
	}
	return false;
}

bool is_ring_buffer_empty(sample_buffer *sample){
	if(sample->front == -1){
		return true;
	}
	return false;
}

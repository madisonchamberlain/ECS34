#include "circular_queue.h"
#include <stdio.h>
#include <stdlib.h>

struct CirQueue
{
	int capacity;
	int enque_loc;
	int deque_loc;
	int num_elements;
	int* elements;
};

CirQueue* cirQueueCreate(int capacity)
{
	// return NULL if capacity is not positive
	if (capacity <= 0)
	{
		return NULL;
	}
	// create and return an instance of the queue with elements initialized 
	struct CirQueue* queue;
	queue = malloc(sizeof(struct CirQueue));
	queue->capacity = capacity;
	queue->enque_loc = 0;
	queue->deque_loc = 0;
	queue->num_elements = 0;
	int* elements;
	elements = malloc(capacity*sizeof(int));
	queue->elements = elements;
	return queue;
}

int cirQueueDestroy(CirQueue* queue)
{
	// if queue is a nill pointer return 0
	if (queue == NULL)
	{
		return 0;
	}
	// otherwise free elements and the queue and return 1 for success 
	free(queue->elements);
	free(queue);
	return 1;
}

int cirQueueEnqueue(CirQueue* queue, int val)
{
	// if there is no space left to queue or there is no queue dont do anything
	if (!queue)
	{
		return 0;
	}
	if ((queue->num_elements == queue->capacity))
	{
		return 0;
	}
	else
	{
		// enque at the enque location; takes O(1) bc we know where it is
		if (queue->capacity == queue->enque_loc)
		{
			queue->enque_loc = 0;
		}
		// adjust the enque location and the number of items in the queue accordingly
		int enque_at = queue->enque_loc;
		queue->elements[enque_at] = val;
		queue->num_elements = queue->num_elements + 1;
		queue->enque_loc = queue->enque_loc + 1;
		return 1;
	}
}

int cirQueueDequeue(CirQueue* queue, int* val)
{
	//if there are no elements or if there is no queue you cant deque
	if ((queue->num_elements == 0)||queue==NULL)
	{
		return 0;
	}
	// otherwise deque what is in the first location 
	else
	{
		// get the value at the deque location (takes O(1) bc we know where it is)
		*val = queue->elements[queue->deque_loc];
		//now change the deque and number of elements accordingly
		queue->deque_loc = queue->deque_loc +1;
		queue->num_elements = queue->num_elements - 1;
		//if you just dequed the last element set deque pointer back to front of array
		if (queue->deque_loc == queue-> capacity)
		{
			queue->deque_loc = 0;
		}
		return 1;
	}
}

int cirQueueLength(const CirQueue* queue)
{
	// simply return the number of elements stored at number of elements 
	return queue->num_elements;
}

#include <stdio.h>
#include "citizen.c"

#define MAX 10

typedef enum { false, true } bool;

typedef struct CitizenQueue {
	Citizen* citizen_queue[MAX];
	int queue_size;
	int head;
	int tail;
} CitizenQueue;

CitizenQueue* makeQueue() {
	CitizenQueue* queue = malloc(sizeof(Citizen) * 10);
	Citizen* citizen = malloc(sizeof(Citizen));
	
	printf("Total size of the queue: %ld\n", sizeof(queue));
	printf("Total size of the citizen: %ld\n", sizeof(citizen));
	
	queue->head= 0;
	queue->queue_size= 0;
	queue->tail= -1;
	
	return queue;
}

Citizen * peek_queue(CitizenQueue* this) {
	printf("Current size of the queue: %s\n", this->citizen_queue[0]->id);
	return this->citizen_queue[0];
}

int size(CitizenQueue* this) {
	return this->queue_size;
}

bool empty(CitizenQueue* this) {
	return this->queue_size == 0;
}

bool full(CitizenQueue* this) {
	return this->queue_size == (MAX - 1);
}

void enqueue(CitizenQueue* this, Citizen* new_citizen) {
	if (!full(this)) {
		this->tail++;
		this->citizen_queue[this->tail];
	} else { printf("Queue is full!"); }
	this->queue_size++;
}


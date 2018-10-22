#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MALLOC(x) ((x *) malloc (sizeof(x)))

typedef struct Citizen {
	int turn;
    int priority;
	struct Citizen* next_citizen;
} Citizen;

Citizen* make_queue(Citizen* queue);
Citizen* enqueue(Citizen* queue, int priority, int turn);
Citizen* dequeue(Citizen* queue, int turn);
Citizen* next(Citizen* queue);

void show_queue(Citizen* queue);
int queue_size(Citizen* queue);
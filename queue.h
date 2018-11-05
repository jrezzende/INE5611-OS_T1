#include <stdio.h>
#include <stdlib.h>

typedef struct Citizen {
	int turn;
    int priority;
	struct Citizen* next_citizen;
} Citizen; // base queue element

Citizen* new_node; // aux node
Citizen* citizen_queue[3]; // queue array
int counter_value = 0; // attendance factor
/* int counter_value1 = 0; *Adicionei aqui - REVER NECESSIDADE DE OUTRO CONTADOR */
Citizen* make_queue(Citizen* queue); // instantiate a new queue
Citizen* make_citizen(int priority, int turn); // instantiates a citizen
Citizen* enqueue(Citizen* queue, int priority, int turn); // puts a new citizen at the end of the queue
Citizen* dequeue(Citizen* queue); // removes a citizen from the beggining of the queue

void lock(); // lock mutex
void unlock(); // unlock mutex

void show_queue(Citizen* queue); // show the current status of the queue
int queue_size(Citizen* queue); // current size of the queue

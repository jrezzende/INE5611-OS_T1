#include <stdio.h>
#include <stdlib.h>

typedef struct Citizen {
	int turn;
    int priority;
	struct Citizen* head_node;
	struct Citizen* next_citizen;
	struct Citizen* next_queue;
} Citizen; // base queue element

Citizen* new_node; // aux node
// Citizen* citizen_queue[3]; // queue array

Citizen* first_queue;
Citizen* second_queue;
Citizen* third_queue;

Citizen* append_queue(Citizen* current_queue, Citizen* next_queue);

Citizen* make_queue(int priority); // instantiate a new queue
Citizen* make_citizen(int priority, int turn); // instantiates a citizen
Citizen* enqueue(Citizen* queue, int priority, int turn); // puts a new citizen at the end of the queue
Citizen* dequeue(Citizen* queue); // removes a citizen from the beggining of the queue

int first_counter_value = 0; // first queue attendance factor
int second_counter_value = 0; // second queue attendance factor

void lock(); // lock mutex
void unlock(); // unlock mutex

void show_queue(Citizen* queue); // show the current status of the queue
int queue_size(Citizen* queue); // current size of the queue

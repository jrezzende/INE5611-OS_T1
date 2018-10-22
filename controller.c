#include "queue.c"
#include <stdio.h>
#include <unistd.h>

Citizen* citizen_queue[3];
int counter_value = 0;

void* aging()
{
	if (counter_value % 3 == 0) {
			if (queue_size(citizen_queue[1]) > 0) {
				citizen_queue[0] = enqueue(citizen_queue[0], citizen_queue[1]->priority, citizen_queue[1]->turn);
				citizen_queue[1] = next(citizen_queue[1]);
				
				if (queue_size(citizen_queue[2]) > 0) {
					citizen_queue[0] = enqueue(citizen_queue[1], citizen_queue[2]->priority, citizen_queue[2]->turn);
					citizen_queue[2] = next(citizen_queue[2]);
				}
			} else {
				if (queue_size(citizen_queue[2]) > 0) {
					citizen_queue[0] = enqueue(citizen_queue[0], citizen_queue[2]->priority, citizen_queue[2]->turn);
					citizen_queue[2] = next(citizen_queue[2]);
				}
			}
	}
}

void* counter_thread(void* args) 
{
	while (citizen_queue[0] != NULL) {
		if (counter_value % 3 == 0) { // 3 citizens from queue[0] in a row
			aging();
		}
		
		sleep(rand() % 15); // attending a citizen...
		
		printf("Current counter id: %li with Citizen: %iP%i\n\n", pthread_self(), citizen_queue[0]->priority + 1, citizen_queue[0]->turn);
		citizen_queue[0] = next(citizen_queue[0]);
		counter_value++;
		
		show_queue(citizen_queue[0]);
	}
	pthread_exit(NULL);
}

void* citizen_generator(void* args)
{
	int counter_turns[3];
	
	counter_turns[0] = 0;
	counter_turns[1] = 0;
	counter_turns[2] = 0;
	
	srand(time(NULL));
	
	while(1) {
		int queue_number = (rand() % 3);
		counter_turns[queue_number]++;
		citizen_queue[queue_number] = enqueue(citizen_queue[queue_number], queue_number, counter_turns[queue_number]);
		sleep(rand() % 3);
	}
	pthread_exit(NULL);
}
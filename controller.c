#include "queue.h"
#include <stdio.h>
#include <unistd.h>

Citizen* citizen_queue[3];
int counter_value = 0;

void* counter_thread(void* args) 
{
	while (citizen_queue[0] != NULL) {
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
		sleep(rand() % 20); 
		system("clear");
		printf("Current thread id: %li with Citizen: %iP%i\n", pthread_self(), citizen_queue[0]->priority + 1, citizen_queue[0]->turn);
		citizen_queue[0] = next(citizen_queue[0]);
		counter_value++;
		
		show_queue(citizen_queue[0]);
	}
	pthread_exit(NULL);
}

void* citizen_generator(void* args)
{
	int counter[3];
	
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	
	srand(time(NULL));
	
	while(1) {
		int queue_number = (rand() % 3);
		counter[queue_number]++;
		citizen_queue[queue_number] = enqueue(citizen_queue[queue_number], queue_number, counter[queue_number]);
		sleep(rand() % 3);
	}
	pthread_exit(NULL);
}

void main(int argc, char* argv[]) {
	citizen_queue[0] = make_queue(citizen_queue[0]);
	citizen_queue[1] = make_queue(citizen_queue[1]);
	citizen_queue[2] = make_queue(citizen_queue[2]);
	
	pthread_t generator;
	pthread_create(&generator, NULL, citizen_generator, NULL);
	int counters_amount = atoi(argv[1]);
	
	printf("Counters: %i", counters_amount);
	pthread_t threads[counters_amount];
	int thread_success;
	
	for (int i = 0; i < counters_amount; i++) {
		thread_success = pthread_create(&(threads[i]), NULL, counter_thread, NULL);
		
		if (thread_success != 0) {
			printf("Error while creating thread");
		}
	}
	
	for (int j = 0; j < counters_amount; j++)
		pthread_join(threads[j], NULL);
}
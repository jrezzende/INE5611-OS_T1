#include "controller.h"

void aging() // aging algorithm
{
	if (counter_value % 3 == 0) {
		
			if (queue_size(citizen_queue[1]) > 0) {
				citizen_queue[0] = enqueue(citizen_queue[0], citizen_queue[1]->priority, citizen_queue[1]->turn);
				citizen_queue[1] = dequeue(citizen_queue[1]);
				
				if (queue_size(citizen_queue[2]) > 0) {
					citizen_queue[1] = enqueue(citizen_queue[1], citizen_queue[2]->priority, citizen_queue[2]->turn);
					citizen_queue[2] = dequeue(citizen_queue[2]);
				}
			} else {
				if (queue_size(citizen_queue[2]) > 0) {
					citizen_queue[1] = enqueue(citizen_queue[0], citizen_queue[2]->priority, citizen_queue[2]->turn);
					citizen_queue[2] = dequeue(citizen_queue[2]);
				}
			}
	}
}

void* counter_thread(void* args) // thread guiche func 
{
	while (citizen_queue[0] != NULL) { // avoid starvation... apply aging
		aging();
		
		sleep(rand() % 15); // attending a citizen...
		
		printf("Current counter id: %li with Citizen: %iP%i\n\n", pthread_self(), citizen_queue[0]->priority, citizen_queue[0]->turn);
		citizen_queue[0] = dequeue(citizen_queue[0]);
		
		counter_value++;
		
		show_queue(citizen_queue[citizen_queue[0]->priority]);
	}
	return NULL;
}

queue_turns* make_queue_turns() // queue counter value
{
	queue_turns* queue_counter = ((queue_turns*) malloc(sizeof(queue_turns)));
	
	queue_turns->turns[0] = 0;
	queue_turns->turns[1] = 0;
	queue_turns->turns[2] = 0;
	
	return queue_turns;
}
	
void generate(counter_turns* counter) // generator
{	
	int queue_number = (rand() % 3); 
	counter->turns[queue_number] += 1;
	citizen_queue[queue_number] = enqueue(citizen_queue[queue_number], queue_number, counter->turns[queue_number]);
	sleep(rand() % 3);
}

void* citizen_generator(void* args) // citizen generator controller
{
	srand(time(NULL));
	counter_turns* counter = make_counter_turns();
	
	while(true) {
		generate(counter);
	}
	
	pthread_exit(NULL);
}

bool is_null(Citizen* citizen) // is citizen null?
{
	if (citizen == NULL)
		return true;
	return false;
}

#include "controller.h"

void apply_aging() // aging algorithm
{
	if (first_counter_value % 3 == 0) {
			
			if (queue_size(second_queue) > 0) {
				first_queue = enqueue(first_queue, second_queue->priority, second_queue->turn);
				second_queue = dequeue(second_queue);
				
				if (queue_size(third_queue) > 0) {
					second_queue = enqueue(second_queue, third_queue->priority, third_queue->turn);
					third_queue = dequeue(third_queue);
				}
			} else {
				if (queue_size(third_queue) > 0) {
					second_queue = enqueue(first_queue, third_queue->priority, third_queue->turn);
					third_queue = dequeue(third_queue);
				}
			}
	}
}

void* counter_thread(void* args) // thread guiche func 
{
	while (first_queue != NULL) { // avoid starvation... apply aging
		apply_aging();
		sleep(rand() % 15); // attending a citizen...
		
		printf("Current counter id: %li with Citizen: %iP%i\n\n", pthread_self(), first_queue->priority, first_queue->turn);

		first_queue = dequeue(first_queue);
		first_counter_value++;

		show_queue(first_queue);
	}
	return NULL;
}

queue_turns* make_queue_turns() // queue counter value
{
	queue_turns* queue_counter = ((queue_turns*) malloc(sizeof(queue_turns)));
	
	queue_counter->turns[0] = 0;
	queue_counter->turns[1] = 0;
	queue_counter->turns[2] = 0;
	
	return queue_counter;
}
	
void generate(queue_turns* counter) // generator
{	
	int queue_number = (rand() % 3); 
	counter->turns[queue_number] += 1;

	switch(queue_number) {
		case 0:
			first_queue = enqueue(first_queue, queue_number, counter->turns[queue_number]);
			break;
		case 1:
			second_queue = enqueue(second_queue, queue_number, counter->turns[queue_number]);
			break;
		case 2:
			third_queue = enqueue(third_queue, queue_number, counter->turns[queue_number]);
			break;
	}

	sleep(rand() % 5);
}

void* citizen_generator(void* args) // citizen generator controller
{
	srand(time(NULL));
	queue_turns* counter = make_queue_turns();
	
	while(true) {
		generate(counter);
	}
	
	pthread_exit(NULL);
}

bool is_null(Citizen* citizen)
{
	if (citizen == NULL)
		return true;
	return false;
}

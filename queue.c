#include "queue.h"
#include <pthread.h>

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER; // MUTEX INITIALIZER

void lock() // lock mutex
{
	pthread_mutex_lock(&MUTEX);	
}

void unlock() // unlock mutex
{
	pthread_mutex_unlock(&MUTEX);
}

///////////////////////////////////////////////////////////////

Citizen* make_queue(int priority) // instantiate a queue 
{
	Citizen* queue = ((Citizen*)malloc(sizeof(Citizen)));
	queue->priority = priority;
	queue = enqueue(queue, 100, 0);

	return queue;
}

Citizen* append_queue(Citizen* current_queue, Citizen* to_append)
{
	current_queue->next_queue = to_append;
	return current_queue;
}

Citizen* make_citizen(int priority, int turn) // instantiates a citizen
{
	Citizen* new = ((Citizen*)malloc(sizeof(Citizen)));
	
	new->next_citizen = NULL;
	new->priority = priority;
	new->turn = turn;
	
	return new;
}

Citizen* enqueue(Citizen* queue, int priority, int turn) // puts a citizen in queue
{
	lock();
	Citizen* temp = queue;
	new_node = make_citizen(priority, turn);
	
	if (new_node->priority > 2)
		return NULL;
	
	if(queue_size(queue) == 0) {
		head_node = new_node;
	} else {
		while(temp->next_citizen != NULL)
			temp= temp->next_citizen;
		temp->next_citizen = new_node; // end of the queue
	}
	unlock();
	return queue;
}

Citizen* dequeue(Citizen* queue) // removes a citizen from the beggining of the queue
{
	printf("Queue size: %d", queue_size(queue));
	lock();
	Citizen* temp;
	temp = queue;
	
	if(queue->next_citizen == NULL) {
		puts("Can't dequeue the head!");
		unlock();
		return queue;
	}

	if (queue != NULL) {
		queue = queue->next_citizen;
		free(temp);
		unlock();
		return queue;
	}
	
	unlock();
	return NULL;
}

int queue_size(Citizen* queue) // return current queue size
{
	int amount = 0;
	Citizen* current = queue;
	
	while (current != NULL) {
		current = current->next_citizen;
		amount++;
	}
	
	return amount;
}

void show_queue(Citizen* queue) // show current queue
{
	if (queue == NULL) {
		printf("The queue number %d is empty.\n", queue->priority);
		return;
	}
	
	Citizen* aux = queue;
	int size = 0;
	
	while (aux != NULL) {
		printf("Citizen: %iP%i (-_-)\n", aux->priority, aux->turn);
		aux = aux->next_citizen;
		size++;
	}
	
	printf("There are currently %d citizens waiting in queue %d.\n", size, queue->priority);
}
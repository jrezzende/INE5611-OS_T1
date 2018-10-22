#include "queue.h"

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;

Citizen* make_queue(Citizen* queue)
{
	queue = MALLOC(Citizen);
	return queue;
}

Citizen* new_node;

Citizen* enqueue(Citizen* queue, int priority, int turn)
{
	pthread_mutex_lock(&MUTEX);
	
	Citizen* temp;
	temp = queue;
	new_node = MALLOC(Citizen);
	
	new_node->next_citizen = NULL;
	new_node->priority = priority;
	new_node->turn = turn;
	
	if(queue_size(queue) > 0) {
		while(temp->next_citizen != NULL)
			temp= temp->next_citizen;
		temp->next_citizen = new_node;
	} else {
		queue = new_node;
	}
	pthread_mutex_unlock(&MUTEX);
	
	return queue;
}

Citizen* dequeue(Citizen* queue, int* turn)
{
	pthread_mutex_lock(&MUTEX);
	
	Citizen* next_in_line;
	next_in_line = queue->next_citizen;
	
	free(queue);
	(*turn)++;
	
	pthread_mutex_unlock(&MUTEX);
	
	return next_in_line;
}

Citizen* next(Citizen* queue)
{
	pthread_mutex_lock(&MUTEX);
	Citizen* temp;
	temp = queue;
	if (queue != NULL) {
		queue = queue->next_citizen;
		free(temp);
		pthread_mutex_unlock(&MUTEX);
		return queue;
	}
	pthread_mutex_unlock(&MUTEX);
	return NULL;
}

int queue_size(Citizen* queue)
{
	int amount = 0;
	Citizen* current = queue;
	
	while (current != NULL) {
		current = current->next_citizen;
		amount++;
	}
	
	return amount;
}

void show_queue(Citizen* queue)
{
	if (queue == NULL) {
		printf("The queue is empty.\n");
		return;
	}
	
	Citizen* aux = queue;
	int size = 0;
	
	while (aux != NULL) {
		printf("Citizen: %iP%i (-_-)\n", aux->priority + 1, aux->turn);
		aux = aux->next_citizen;
		size++;
	}
	
	printf("There are currently %d citizens waiting in line.\n", size);
}
#include "queue.h"

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;

Citizen* make_queue(Citizen* queue);
Citizen* enqueue(Citizen* queue, int priority, int turn);
Citizen* next_Citizen(Citizen* queue);

int show_queue(Citizen* queue);
int queue_size(Citizen* queue);

Citizen* make_queue(Citizen* queue)
{
	queue = MALLOC(Citizen);
	return queue;
}

Citizen* enqueue(Citizen* queue, int priority, int turn)
{
	pthread_mutex_lock(&MUTEX);
	
	Citizen* temp = queue;
	Citizen* new_Citizen = MALLOC(Citizen)
	
	new_Citizen->next_Citizen = NULL;
	new_Citizen->priority = priority;
	new_Citizen->turn = turn;
	
	if(queue_size(queue) > 0) {
		while(temp->next_Citizen != NULL)
			temp= temp->next_Citizen;
		temp->next_Citizen = new_Citizen;
	} else {
		queue = new_Citizen;
	}
	pthread_mutex_unlock(&MUTEX);
	
	return queue;
}

Citizen* dequeue(Citizen* queue, int* turn)
{
	pthread_mutex_lock(&MUTEX);
	
	Citizen* next_in_line;
	next_in_line = queue->next_Citizen;
	
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
		queue = queue->next_Citizen;
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
	Node* current = queue;
	
	while (current != NULL) {
		current = current->next_node;
		amount++;
	}
	
	return amount;
}

void show_queue(Citizen* queue)
{
	if (queue == NULL) {
		printf("The queue is empty.\n");
		return
	}
	
	Citizen* aux = queue;
	int queue_size = 0;
	
	while (aux != NULL) {
		printf("\n%P%i", aux->priority + 1, aux->turn);
		aux = aux->next_Citizen;
		queue_size++;
	}
	
	printf("There are currently %d citizens waiting in line.", queue_size);
}
}
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef enum { HIGHER = 0, MEDIUM = 1, LOWER = 2 } PRIORITY;

typedef struct Citizen {
    PRIORITY priority;
    char id[2];
	pthread_t thread;
} Citizen;

Citizen* makeCitizen(PRIORITY priority, char id[2])
{
    Citizen* citizen = malloc(sizeof(Citizen));

    citizen->priority= priority;
    strcpy(citizen->id, id);

    return citizen;
}

void* thread_func(void* args) {}

void start(Citizen* this)
{
	if (!this->thread)
		pthread_create(&this->thread, NULL, thread_func, NULL);
}

void change_priority(Citizen* citizen, PRIORITY priority)
{
    citizen->priority = priority;	
}
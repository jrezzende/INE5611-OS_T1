#include <stdlib.h>
typedef enum { HIGHER = 0, MEDIUM = 1, LOWER = 2 } PRIORITY;

typedef struct Citizen {
    PRIORITY priority;
    int id;
} Citizen;

Citizen* makeCitizen(PRIORITY priority, int id)
{
    Citizen* citizen = malloc(sizeof(Citizen));

    citizen->priority= priority;
    citizen->id = id;

    return citizen;
}

void change_priority(Citizen* citizen, PRIORITY priority)
{
    citizen->priority = priority;
}
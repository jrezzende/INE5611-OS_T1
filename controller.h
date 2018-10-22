#include "queue.c"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct counter_turns {
	int turns[3];
} counter_turns; // base queue element

counter_turns* make_counter_turns(); // instantiate turns counter values

void aging(); // aging to avoid starvation
void* counter_thread(void* args); // thread guiche/counter
void generate(); // citizen generator
void* citizen_generator(void* args); // citizen generator controller
bool is_null(Citizen* citizen); // return 1 if is null 0 if not
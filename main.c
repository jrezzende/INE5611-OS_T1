#include <stdio.h>
#include "citizenqueue.c"


int main()
{
    Citizen* citizen = makeCitizen(MEDIUM, "0P");
	CitizenQueue* queue = makeQueue();
	
	enqueue(queue, citizen);
	Citizen* first = peek_queue(queue);
	
	printf("Citizen id: %s\n", first->id);
	printf("Citizen credentials: %d\n", first->priority);
	printf("Current queue tail: %s\n", first->id);
	
	return 0;
}

#include <stdio.h>
#include "citizen.c"

int main()
{
    Citizen* citizen = makeCitizen(LOWER, 1);

    change_priority(citizen, MEDIUM);
	printf("%d, %d\n", citizen->priority, citizen->id);
	return 0;
}

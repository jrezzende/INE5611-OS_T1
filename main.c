#include <stdio.h>
#include "citizen.c"

int main()
{
    Citizen* citizen = makeCitizen(LOWER, "0P");

    change_priority(citizen, MEDIUM);
	start(citizen);
	printf("%d, %s\n", citizen->priority, citizen->id);
	return 0;
}

#include <stdio.h>
#include "citizen.c"

int main()
{
    Citizen* citizen = makeCitizen(LOWER, 1);

    change_priority(citizen, MEDIUM);

	return 0;
}

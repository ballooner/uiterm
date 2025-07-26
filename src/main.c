#include "uiterm-utils.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	enterRawMode();

	char c;
	while ((c = getchar()) != 'q');

	return 0;
}

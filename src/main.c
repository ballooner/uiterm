#include "uiterm-utils.h"

int main(void)
{
	enterRawMode();

	moveCursor(10, 10);

	while (1);

	return 0;
}

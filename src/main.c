#include "uiterm-utils.h"
#include "window.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	enterRawMode();

	window_t* mainWindow = createWindow(10, 5, 10, 10);
	renderWindow(mainWindow);

	char c;
	while ((c = getchar()) != 'q');

	return 0;
}

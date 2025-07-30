#include "uiterm-utils.h"
#include "window.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	enterRawMode();

	//window_t* mainWindow = createWindow(20, 20);
	//renderWindow(mainWindow);
	
	moveCursor(5, 10);

	char c;
	while ((c = getchar()) != 'q')
	{
		putchar(c);
	}

	return 0;
}

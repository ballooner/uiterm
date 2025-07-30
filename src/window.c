#include "window.h"
#include "uiterm-utils.h"
#include <stdio.h>
#include <stdlib.h>

window_t* createWindow(int height, int width)
{
	window_t* newWindow = malloc(sizeof(window_t));
	char* windowContent = malloc(height * width * sizeof(char));

	// Window setup
	newWindow->height = height;
	newWindow->width = width;
	newWindow->content = windowContent;

	// Setup empty window content
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*(windowContent + (height * i + j)) = ' ';
		}
	}

	// Temp setup
	newWindow->id = 0;
	newWindow->isActive = true;
	newWindow->posX = 1;
	newWindow->posY = 1;

	return newWindow;
}

void deleteWindow(window_t* window)
{
	free(window->content);
	free(window);
}

void renderWindow(window_t* window)
{
	for (int i = 0; i < window->height; i++)
	{
		moveCursor(window->posX, window->posY + i);
		putchar('|');
	}
}

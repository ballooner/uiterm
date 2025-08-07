#include "window.h"
#include "uiterm-utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

window_t* createWindow(int height, int width, int x, int y)
{
	window_t* newWindow = malloc(sizeof(window_t));
	char* windowContent = malloc(height * width * sizeof(char));

	// Window setup
	newWindow->height = height;
	newWindow->width = width;
	newWindow->content = windowContent;
	newWindow->posX = x;
	newWindow->posY = y;


	// Setup empty window content
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*(windowContent + (width * i + j)) = ' ';
		}
	}

	// Temp setup
	newWindow->id = 0;
	newWindow->isActive = true;

	return newWindow;
}

void deleteWindow(window_t* window)
{
	free(window->content);
	free(window);
}

void renderWindow(window_t* window)
{
	// Render top/bottom of window border
	moveCursor(window->posX - 1, window->posY - 1);
	write(STDOUT_FILENO, "┌", 4);
	moveCursor(window->posX - 1, window->posY + window->height);
	write(STDOUT_FILENO, "└", 4);
	for (int i = 0; i < window->width; i++)
	{
		moveCursor(window->posX + i, window->posY - 1);
		write(STDOUT_FILENO, "─", 4);
		moveCursor(window->posX + i, window->posY + window->height);
		write(STDOUT_FILENO, "─", 4);
	}
	moveCursor(window->posX + window->width, window->posY - 1);
	write(STDOUT_FILENO, "┐", 4);
	moveCursor(window->posX + window->width, window->posY + window->height);
	write(STDOUT_FILENO, "┘", 4);

	// Render left/right side of window border
	for (int i = 0; i < window->height; i++)
	{	
		moveCursor(window->posX - 1, window->posY + i);
		write(STDOUT_FILENO, "│", 4);
		moveCursor(window->posX + window->width, window->posY + i);
		write(STDOUT_FILENO, "│", 4);
	}

	for (int i = 0; i < window->height; i++)
	{
		moveCursor(window->posX, window->posY + i);
		for (int j = 0; j < window->width; j++)
		{
			write(STDOUT_FILENO, "X", 1);
		}
	}
}

#include "window.h"
#include <stdlib.h>

window_t* createWindow(int height, int width)
{
	window_t* newWindow = malloc(sizeof(window_t));
	char** windowContent = malloc(height * width * sizeof(char));

	// Window setup
	newWindow->height = height;
	newWindow->width = width;
	newWindow->content = windowContent;

	// Setup empty window content
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((i == 0 || i == height) || (j == 0 || j == width))
			{
				windowContent[height][width] = 
			} else
			{
				windowContent[height][width] = ' ';
			}
		}
	}

	// Temp setup
	newWindow->id = 0;
	newWindow->isActive = true;

	return newWindow;
}
void deleteWindow(window_t* window);
void renderWindow(window_t* window);

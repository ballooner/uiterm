#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>


typedef struct WindowInfo
{
	int id;
	int height;
	int width;
	int posX;
	int posY;
	bool isActive;
	char* content;
} window_t;

window_t* createWindow(int height, int width, int x, int y);
void deleteWindow(window_t* window);
void renderWindow(window_t* window);

#endif

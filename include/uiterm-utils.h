#ifndef UITERMUTILS_H
#define UITERMUTILS_H

#include <termios.h>

typedef struct TerminalSettings
{
	struct termios defaultSettings;
	struct termios currentSettings;
	int cursorX;
	int cursorY;
} terminal_settings_t;

// Clear the screen and put the terminal into raw mode.
// Saves termios settings before entering raw mode
// and returns to them on program exit.
int enterRawMode(void);
// Leaves raw mode. Called on program exit if entering
// raw mode from enterRawMode()
int leaveRawMode(void);
int clearScreen(void);
// Move cursor to position x,y where 
// x = [0, termWidth] from left-right  (i.e. left is x=0)
// y = [0, termHeight] from top-bottom (i.e. top is y=0)
int moveCursor(int x, int y);

#endif

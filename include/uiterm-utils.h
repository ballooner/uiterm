#ifndef UITERMUTILS_H
#define UITERMUTILS_H

#include <termios.h>

#define BUFFER_SIZE 128

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
// Return -1 on failure
int enterRawMode(void);
// Leaves raw mode. Called on program exit if entering
// raw mode from enterRawMode()
// Return -1 on failure
int leaveRawMode(void);
int clearScreen(void);
// Move cursor to position x,y where 
// x = [0, termWidth] from left-right  (i.e. left is x=0)
// y = [0, termHeight] from top-bottom (i.e. top is y=0)
// Return -1 on failure
int moveCursor(int x, int y);
// Draw character at position x,y
// Return -1 on failure
int drawCharacter(int x, int y, char c);
// Return the current cursor position into the variables provided
int getCursorPosition(int* x, int *y);
// Return the current terminal size in the variables provided
int getTerminalSize(int* width, int* height);

#endif

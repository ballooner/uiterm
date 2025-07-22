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

void enterRawMode(void);
void leaveRawMode(void);
void clearScreen(void);
void moveCursor(int x, int y);

#endif

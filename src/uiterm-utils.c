#include "uiterm-utils.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

terminal_settings_t terminalSettings;

int enterRawMode(void)
{
	if (tcgetattr(STDIN_FILENO, &terminalSettings.defaultSettings) == -1)
		return -1;
	struct termios newSettings = terminalSettings.defaultSettings;

	newSettings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
		| INLCR | IGNCR | ICRNL | IXON);
	newSettings.c_oflag &= ~OPOST;
	newSettings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	newSettings.c_cflag &= ~(CSIZE | PARENB);
	newSettings.c_cflag |= CS8;

	terminalSettings.currentSettings = newSettings;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalSettings.currentSettings) == -1)
		return -1;
	if (clearScreen() == -1)
		return -1;

	atexit((void (*)(void))leaveRawMode);

	return 0;
}

int leaveRawMode(void)
{
	if (clearScreen() == -1)
		return -1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalSettings.defaultSettings) == -1)
		return -1;

	return 0;
}

int clearScreen(void)
{
	if (write(STDIN_FILENO, "\x1b[1J", 4) == -1)
		return -1;

	return 0;
}

int moveCursor(int x, int y)
{
	char buffer[64];

	int bytesWritten = snprintf(buffer, 64, "\x1b[%d;%dJ", y, x);
	if (bytesWritten < 0)
		return -1;

	return bytesWritten;
}

int drawCharacter(int x, int y, char c)
{


	return 0;
}

int changeBackgroundColor(int r, int g, int b)
{


	return 0;
}

int changeCellColor(int r, int g, int b)
{


	return 0;
}

int changeTextColor(int r, int g, int b)
{


	return 0;
}

int getCursorPosition(int* x, int *y)
{


	return 0;
}

int getTerminalSize(int* width, int* height)
{


	return 0;
}

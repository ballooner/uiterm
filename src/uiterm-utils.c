#include "uiterm-utils.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

terminal_settings_t terminalSettings;

void enterRawMode(void)
{
	tcgetattr(STDIN_FILENO, &terminalSettings.defaultSettings);
	struct termios newSettings = terminalSettings.defaultSettings;

	newSettings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
		| INLCR | IGNCR | ICRNL | IXON);
	newSettings.c_oflag &= ~OPOST;
	newSettings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	newSettings.c_cflag &= ~(CSIZE | PARENB);
	newSettings.c_cflag |= CS8;

	terminalSettings.currentSettings = newSettings;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalSettings.currentSettings);
	clearScreen();

	atexit(leaveRawMode);
}

void leaveRawMode()
{
	clearScreen();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &terminalSettings.defaultSettings);
}

void clearScreen(void)
{
	write(STDIN_FILENO, "\x1b[1J", 4);
}

void moveCursor(int x, int y);

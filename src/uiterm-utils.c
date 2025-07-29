#include "uiterm-utils.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>


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
	if (write(STDOUT_FILENO, "\x1b[1J", 4) == -1)
		return -1;
	if (moveCursor(0, 0) < 0)
		return -1;

	return 0;
}

int moveCursor(int x, int y)
{
	char buffer[BUFFER_SIZE];

	int bytesWritten = snprintf(buffer, BUFFER_SIZE, "\x1b[%d;%dH", y, x);
	if (bytesWritten < 0)
		return -1;

	int returnCode = write(STDOUT_FILENO, buffer, bytesWritten);
	if (returnCode < 0)
		return -1;

	return bytesWritten;
}

int drawCharacter(int x, int y, char c)
{
	if (moveCursor(x, y) == -1)
		return -1;

	putchar(c);

	return 0;
}

int getCursorPosition(int* x, int *y)
{
	if (write(STDOUT_FILENO, "\x1b[6n", 4) < 0)
		return -1;

	char buffer[BUFFER_SIZE];

	read(STDIN_FILENO, &buffer[0], 1);

	int i = 1;
	while (i < BUFFER_SIZE && buffer[i - 1] != 'R')
	{
		read(STDIN_FILENO, &buffer[i++], 1);
	}

	if (i < BUFFER_SIZE)
		buffer[i] = '\0';

	if (buffer[0] != '\x1b' && buffer[1] != '[')
		return -1;

	sscanf(&buffer[2], "%d;%dR", y, x);

	return 0;
}

int getTerminalSize(int* width, int* height)
{
	struct winsize ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);

	*width = ws.ws_row;
	*height = ws.ws_col;

	return 0;
}

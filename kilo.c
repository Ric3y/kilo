//STEP 15 

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct termios orig_termios; //store the original terminal atributes 

//Resotre terminal attributes on program exit
void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw = orig_termios; //modify og mode 
	raw.c_lflag &= ~(ICRNL | IXON); //turn off input modes: no carriage return and new line(CTRL-M), no start/stop output control(CTRL-S and CTRL-Q)
	raw.c_lflag &= ~(OPOST); //turn off post processing for output 
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //turn off local modes: echo, canonical, extended functions (CTRL-V), signal chars (^Z and ^C) 

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
	enableRawMode();

	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if (iscntrl(c)) {
			printf("%d\r\n", c);
		}
		else {
			printf("%d ('%c')\r\n", c, c);
		}
	}
	return 0;
}


#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLACK   "\033[30m"
#define WHITE   "\033[37m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BOLDRED     "\033[1m\033[31m"
#define BRIGHTYELLOW "\u001b[33;1m"
#define GREY "\u001b[30;1m"
#define BRIGHTCYAN "\u001b[36;1m"



inline void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}
inline int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
	ungetc(ch, stdin);
	return 1;
	}

	return 0;
}

struct dimension{
	int x = 28;
	int y = 9;
};
struct coord{
	float x;
	int y;
};

#endif
#include <ncurses.h>
typedef struct pac {
	int posx, posy;
} pacman;
void initpacman(pacman *);
int getpacmanposx(pacman *p);
int getpacmanposy(pacman *p);
void setpacmanpos(pacman *, int, int);
void printpacman(pacman *);

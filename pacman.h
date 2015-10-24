#include <ncurses.h>
typedef struct pac {
	int posx, posy;
} pacman;
void initpacman(pacman *);
int getpacmanposx(pacman *p);
int getpacmanposy(pacman *p);
void setpacmanpos(pacman *, int, int);
void printpacman(pacman *);
typedef struct monster {
	int posx, posy;
	pacman *p;
} monster;
void initmonster(monster *, pacman *);
void printmonsters(monster *m, int n);
void setmonsterpos(monster *, int, int);
int getmonsterposx(monster *m);
int getmonsterposy(monster *);
int checkformonster(monster *m, int n);

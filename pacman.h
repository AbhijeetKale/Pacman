#include <ncurses.h>
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
typedef struct pac {
	int posx, posy, direction;
} pacman;
void initpacman(pacman *);
int getpacmanposx(pacman *p);
int getpacmanposy(pacman *p);
void setpacmandirection(pacman *p, int direction);
void setpacmanpos(pacman *, int, int);
void printpacman(pacman *);
int getpacmandirection(pacman *p);
typedef struct monster {
	int posx, posy;
	pacman *p;
	int direction;
} monster;
void initmonster(monster *, pacman *);
void printmonsters(monster *m);
void setmonsterpos(monster *, int, int);
int getmonsterposx(monster *m);
int getmonsterposy(monster *);
int checkformonster(monster *m, int n);
int getmonsterdirection(monster *m);
void setmonsterdirection(monster *m, int dir);
int canseepacman(monster *m);
void set_diff_monster_paths(monster *m, monster *m2);

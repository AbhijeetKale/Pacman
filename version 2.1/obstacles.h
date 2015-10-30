#include <ncurses.h>
#include "point.h"
#define VER 1
#define HOR 2
typedef struct obstacles {
	int fromx, tox, fromy, toy, type;
} obstacles;
void setobstaclepos(obstacles *, int, int, int , int, int);
void drawobstacles(obstacles *, int );
int checkforobstacles(obstacles *o, int n, char control, pacman *);
int monstercheckforobstacles(obstacles *, int, monster *);

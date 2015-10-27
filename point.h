#include <ncurses.h>
#include "pacman.h"
#define MAX_POINT 50
typedef struct point {
	int posx, posy, activate;
} point;
void printpoints(point *p, int n);
void setpointpos(point *p, int x, int y);
int getpointposx(point *p);
int getpointposy(point *p);
int checkforpoints(point *p, int n, pacman *pac);

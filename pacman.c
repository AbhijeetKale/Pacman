#include "pacman.h"
#include <stdio.h>
void initpacman(pacman *p) {
	p->posx = 0;
	p->posy = 0;
}
int getpacmanposx(pacman *p) {
	return p->posx;
}
int getpacmanposy(pacman *p) {
	return p->posy;
}
void setpacmanpos(pacman *p, int x, int y) {
	p->posx = x;
	p->posy = y;
	return;
}
void printpacman(pacman *p) {
	mvprintw(p->posx, p->posy, "a");
	mvprintw(p->posx - 1, p->posy, "a");
	mvprintw(p->posx + 1, p->posy, "a");
	mvprintw(p->posx - 1, p->posy - 1, "p");
	mvprintw(p->posx + 1, p->posy + 1, "c");
	mvprintw(p->posx, p->posy + 1, "c");
	mvprintw(p->posx, p->posy - 1, "p");
	mvprintw(p->posx - 1, p->posy + 1, "c");
	mvprintw(p->posx + 1, p->posy - 1, "p");
	refresh();
	return;
}
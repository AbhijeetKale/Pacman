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
void initmonster(monster *m, pacman *p) {
	m->p = p;
	m->posx = 0;
	m->posy = 0;
	return;
}
void setmonsterpos(monster *m, int x, int y) {
	m->posx = x;
	m->posy = y;
	return;
}
int getmonsterposx(monster *m) {
	return m->posx;
}
int getmonsterposy(monster *m) {
	return m->posy;
}
void printmonsters(monster *m, int n) {
	int count;
	for(count = 0; count < n; count++) {
		mvprintw(m->posx, m->posy, "o");
		mvprintw(m->posx - 1, m->posy, "o");
		mvprintw(m->posx + 1, m->posy, "o");
		mvprintw(m->posx, m->posy - 1, "m");
		mvprintw(m->posx, m->posy + 1, "n");
		mvprintw(m->posx - 1, m->posy - 1, "m");
		mvprintw(m->posx + 1, m->posy + 1, "n");
		mvprintw(m->posx - 1, m->posy + 1, "n");
		mvprintw(m->posx + 1, m->posy - 1, "m");
		m++;
	}
	refresh();
	return;
}
int checkformonster(monster *m, int n) {
	int count;
	for(count = 0; count < n; count++) {
		if(m->p->posy >= m->posy - 2 && m->p->posy <= m->posy + 2) {
			if(m->p->posx == m->posx + 2 || m->p->posx == m->posx - 2) {
				return 1;
			}
		}
		if(m->p->posx >= m->posx - 2 && m->p->posx <= m->posx + 2) {
			//for left
			if(m->p->posy == m->posy + 2 || m->p->posy == m->posy - 2) {
				return 1;
			}
		}
		m++;
	}
	return 0;
}

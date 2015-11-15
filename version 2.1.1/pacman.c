/*   Terminal Pacman
 *   Copyright (C) 2015  Abhijeet Kale
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
*/
#include "pacman.h"
#include <stdio.h>
void initpacman(pacman *p) {
	p->posx = 0;
	p->posy = 0;
	p->direction = UP;
}
int getpacmanposx(pacman *p) {
	return p->posx;
}
//sets the direction of the pacman
void setpacmandirection(pacman *p, int direction) {
	p->direction = direction;
	return;
}
int getpacmanposy(pacman *p) {
	return p->posy;
}
//sets the pacman postion
void setpacmanpos(pacman *p, int x, int y) {
	p->posx = x;
	p->posy = y;
	return;
}
int getpacmandirection(pacman *p) {
	return p->direction;
}
//prints the pacman
void printpacman(pacman *p) {
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	attron(COLOR_PAIR(10));
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
	attroff(COLOR_PAIR(10));
	return;
}
void initmonster(monster *m, pacman *p) {
	m->p = p;
	m->posx = 0;
	m->posy = 0;
	m->direction = LEFT;
	return;
}
//sets the monster position
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
//printsmonster
void printmonsters(monster *m) {
	init_pair(3, COLOR_BLACK, COLOR_RED);
	attron(COLOR_PAIR(3));
	mvprintw(m->posx, m->posy, "o");
	mvprintw(m->posx - 1, m->posy, "o");
	mvprintw(m->posx + 1, m->posy, "o");
	mvprintw(m->posx, m->posy - 1, "m");
	mvprintw(m->posx, m->posy + 1, "n");
	mvprintw(m->posx - 1, m->posy - 1, "m");
	mvprintw(m->posx + 1, m->posy + 1, "n");
	mvprintw(m->posx - 1, m->posy + 1, "n");
	mvprintw(m->posx + 1, m->posy - 1, "m");
	refresh();
	attroff(COLOR_PAIR(3));
	return;
}
//checks if the pacman and monster have collided
int checkformonster(monster *m, int n) {
	int count;
	for(count = 0; count < n; count++) {
		if(m->p->posy >= m->posy - 2 && m->p->posy <= m->posy + 2) {
			if(m->p->posx <= m->posx + 2 && m->p->posx >= m->posx - 2) {
				return 1;
			}
		}
		if(m->p->posx >= m->posx - 2 && m->p->posx <= m->posx + 2) {
			//for left
			if(m->p->posy <= m->posy + 2 && m->p->posy >= m->posy - 2) {
				return 1;
			}
		}
		m++;
	}
	return 0;
}
int getmonsterdirection(monster *m) {
	return m->direction;
}
void setmonsterdirection(monster *m, int dir) {
	m->direction = dir;
	return;
}
//visibilty power given to the monster for detecting pacman moves.
int canseepacman(monster *m) {
	int dir;
	if(m->p->posx >= m->posx - 1 && m->p->posx <= m->posx + 1) {
		dir = m->posy - m->p->posy;
		if(dir < 0) {
			m->direction = RIGHT;
			return RIGHT;	
		}
		else {
			m->direction = LEFT;
			return LEFT;
		}
	}
	if(m->p->posy >= m->posy - 1 && m->p->posy <= m->posy + 1) {
		dir = m->posx - m->p->posx;
		if(dir < 0) {
			m->direction = DOWN;
			return DOWN;
		}
		else {
			m->direction = UP;
			return UP;
		}
	}
	
	return m->direction;
}
//Repelling the monsters if they travel in the same direction in the same path
void set_diff_monster_paths(monster *m, monster *m2) {
	if(m->direction != m2->direction) {
		return;
	}
	switch(m->direction) {
		case UP:
			if(m->posy >= m2->posy - 1 && m->posy <= m2->posy + 1) {
				if(m->posx > m2->posx) {
					m->direction = DOWN;
				}
				else {
					m2->direction = DOWN;
				}
			}
			break;
		case DOWN:
			if(m->posy >= m2->posy - 1 && m->posy <= m2->posy + 1) {
				if(m->posx < m2->posx) {
					m->direction = UP;
				}
				else {
					m2->direction = UP;
				}
			}
			break;
		case LEFT:
			if(m->posx >= m2->posx - 1 && m->posx <= m2->posx + 1) {
				if(m->posy > m2->posy) {
					m->direction = RIGHT;
				}
				else {
					m2->direction = RIGHT;
				}
			}
			break;
		case RIGHT:
			if(m->posx == m2->posx) {
				if(m->posy < m2->posy) {
					m->direction = LEFT;
				}
				else {
					m2->direction = LEFT;
				}
			}
			break;
	}
}
//Used with printpacmans hiding the initial pacman position in order to create animated effect.
void hidepacman(pacman *m) {
	mvprintw(m->posx, m->posy, " ");
	mvprintw(m->posx - 1, m->posy, " ");
	mvprintw(m->posx + 1, m->posy, " ");
	mvprintw(m->posx, m->posy - 1, " ");
	mvprintw(m->posx, m->posy + 1, " ");
	mvprintw(m->posx - 1, m->posy - 1, " ");
	mvprintw(m->posx + 1, m->posy + 1, " ");
	mvprintw(m->posx - 1, m->posy + 1, " ");
	mvprintw(m->posx + 1, m->posy - 1, " ");
	refresh();
}
//Used with printmonster hiding the initial monster position in order to create animated effect.
void hidemonster(monster *m) {
	mvprintw(m->posx, m->posy, " ");
	mvprintw(m->posx - 1, m->posy, " ");
	mvprintw(m->posx + 1, m->posy, " ");
	mvprintw(m->posx, m->posy - 1, " ");
	mvprintw(m->posx, m->posy + 1, " ");
	mvprintw(m->posx - 1, m->posy - 1, " ");
	mvprintw(m->posx + 1, m->posy + 1, " ");
	mvprintw(m->posx - 1, m->posy + 1, " ");
	mvprintw(m->posx + 1, m->posy - 1, " ");
	refresh();
}

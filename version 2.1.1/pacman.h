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
void hidepacman(pacman *p);
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
void hidemonster(monster *p);

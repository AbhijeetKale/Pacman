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

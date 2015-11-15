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

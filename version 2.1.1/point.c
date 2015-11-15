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
#include "point.h"
//printing the points on the screen.
void printpoints(point *p, int n) {
	int count;
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	attron(COLOR_PAIR(2));
	for(count = 0; count < n; count++) {
		if(p->activate == 1) {
			mvprintw(p->posx, p->posy, "+");
		}
		else {
			attroff(COLOR_PAIR(2));
			mvprintw(p->posx, p->posy, " ");
			attron(COLOR_PAIR(2));
		}
		p++;
	}
	attroff(COLOR_PAIR(2));
	refresh();
	return;
}
int getpointposx(point *p) {
	return p->posx;
}
int getpointposy(point *p) {
	return p->posy;
}
//sets the position for the points.
void setpointpos(point *p, int x, int y) {
	p->posx = x;
	p->posy = y;
	p->activate = 1;
	return;
}
//checks for point collection by pacman and prevents from printing again if the points have been taken
int checkforpoints(point *p, int n, pacman *pac) {
	int count, k = 0;
	for(count = 0; count < n; count++) {
		if((p->activate)) {
			if (p->posx == pac->posx && p->posy == pac->posy + 1) {
				p->activate = 0;
				k = 1;
				break;
			}
			if (p->posx == pac->posx && p->posy == pac->posy - 1) {
				p->activate = 0;
				k = 1;
				break;
			}
			if (p->posx == pac->posx + 1 && p->posy == pac->posy) {
				p->activate = 0;
				k = 1;
				break;
			}
			if (p->posx == pac->posx - 1 && p->posy == pac->posy) {
				p->activate = 0;
				k = 1;
				break;
			}
			if (p->posx == pac->posx + 1 && p->posy == pac->posy + 1) {
				p->activate = 0;
				k = 1;
				break;
			}
			if (p->posx == pac->posx + 1&& p->posy == pac->posy - 1) {
				p->activate = 0;
				k = 1;
				break;
			}
			if (p->posx == pac->posx - 1&& p->posy == pac->posy + 1) {
				p->activate = 0;
				k = 1;
				break;
			}
			if (p->posx == pac->posx - 1 && p->posy == pac->posy - 1) {
				p->activate = 0;
				k = 1;
				break;
			}
		}
		p++;
	}
	return k;
}


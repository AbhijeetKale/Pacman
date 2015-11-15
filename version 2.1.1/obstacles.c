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
#include "obstacles.h"
extern int choice;
//Setting the coordinates of the obstacles
void setobstaclepos(obstacles *o, int x1, int y1, int x2, int y2, int type) {
	o->fromx = x1;
	o->fromy = y1;
	o->tox = x2;
	o->toy = y2;
	o->type = type;
	return;
}
//printing the obstacles
void drawobstacles(obstacles *o, int n) {
	int count, counter, count2;
	init_pair(1, COLOR_YELLOW, COLOR_WHITE);
	attron(COLOR_PAIR(1));
	switch(choice) {
		case 1:
			for(count2 = 0; count2 < n; count2++) {
				for(count = o->fromy; count <= o->toy; count++) {
					for(counter = o->fromx; counter <= o->tox; counter++) {
						if(o->type == VER) {
							mvprintw(counter, count - 1, "|||");
						}
						else if(o->type == HOR) {
							mvprintw(counter - 1, count, "===");
						}
					}
				}
				o++;
			}
			break;
	}
	attroff(COLOR_PAIR(1));
	return;
}
//checking obstacles in path for pacman
int checkforobstacles(obstacles *o, int n, char control, pacman *p) {
	int obs = 1;
	int count, done = 0;
	for(count = 0; count < n; count++) {
		switch(control) {
			case 'w':
				if(getpacmanposy(p) + 1 >= o->fromy - 1 && getpacmanposy(p) - 1 <= o->toy + 1) {
					if(getpacmanposx(p) - 2 <= o->tox) {
						obs = 0;
						done = 1;
					}
				}
				break;
			case 's':
				if(getpacmanposy(p) + 1 >= o->fromy - 1 && getpacmanposy(p) - 1 <= o->toy + 1) {
					if(getpacmanposx(p) + 2 <= o->fromx + 1) {
						obs = 0;
						done = 1;
					}
				}
				break;
			case 'a':
				if(getpacmanposx(p) + 1 >= o->fromx && getpacmanposx(p) - 1 <= o->tox) {
					if(getpacmanposy(p) - 2 == o->fromy + 1) {
							obs = 0;
							done = 1;
					}
				}
				break;
			case 'd':
				if(getpacmanposx(p) + 1 >= o->fromx && getpacmanposx(p) - 1 <= o->tox) {
					if(getpacmanposy(p) + 2 == o->fromy - 1) {
							obs = 0;
							done = 1;
					}
				}
				break;
		}
		if(done) {
			break;
		}
		o++;
	}
	return obs;
}
//checking the obstalces in path of the monster
int monstercheckforobstacles(obstacles *o, int n, monster *m) {
	int obs = 1, count, done;
	for(count = 0; count < n; count++) {
		switch(m->direction) {
			case UP:
				if(getmonsterposy(m) + 1 >= o->fromy - 1 && getmonsterposy(m) - 1 <= o->toy + 1) {
					if(getmonsterposx(m) - 2 <= o->tox) {
						obs = 0;
						done = 1;
					}
				}
				break;
			case DOWN:
				if(getmonsterposy(m) + 1 >= o->fromy - 1 && getmonsterposy(m) - 1 <= o->toy + 1) {
					if(getmonsterposx(m) + 2 <= o->fromx + 1) {
						obs = 0;
						done = 1;
					}
				}
				break;
			case RIGHT:
				if(getmonsterposx(m) + 1 >= o->fromx && getmonsterposx(m) - 1 <= o->tox) {
					if(getmonsterposy(m) + 2 == o->fromy - 1) {
							obs = 0;
							done = 1;
					}
				}
				break;
			case LEFT:
				if(getmonsterposx(m) + 1 >= o->fromx && getmonsterposx(m) - 1 <= o->tox) {
					if(getmonsterposy(m) - 2 == o->fromy + 1) {
							obs = 0;
							done = 1;
					}
				}
				break;
		}
		if(done == 1) {
			break;
		}
		o++;
	}
	return obs;
}

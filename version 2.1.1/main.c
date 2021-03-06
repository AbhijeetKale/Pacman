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
#include <stdlib.h>
#include "bounds.h"
#include <menu.h>
#include "obstacles.h"
#define PTS 300
#define OBS 70
#define WIN 1
#define LOOSE 0
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4
/* row and column for the dimensions of the window
* Choice is the map id which is assigned by the main arguement
* Points is max possible score than can be scored in this round
* Obsno are the number of pbstacles
*/
int row, column, choice = 1, points = 0, obsno = 0, end, score = 0;
point pts[PTS];
boundary b_ver, b_hor;
monster m, m2, m3;						// our monster
int load_game = 0;
pacman p;							// our pacman
obstacles o[OBS];
char *menu[] = {
			"Start Game",
			"Load Game",
			"Exit"
		};
/*This function draws the score bard with the score and the level*/
void drawscore(int update) {
	score += update;
	mvprintw(2, column / 2, "SCORE : %d", score);
	mvprintw(4, column / 2, "LEVEL : %d", choice);
	refresh();
	return;
}
/*Draws the boundary of the map*/
void drawBoundary() {
	int i;
	for(i = 0; i < column; i++) {
		mvprintw(row / 4 - 1, i, "-");
	}
	for(i = 0; i < column; i++) {
		mvprintw(row - (row / 4) + 1, i, "-");
	}
	for(i = row / 4 - 1; i <= row - (row / 4); i++) {
		mvprintw(i, 0, "=");
	}
	for(i = row / 4 - 1; i <= row - (row / 4); i++) {
		mvprintw(i, column - 1, "=");
	}
	setBoundary(&b_ver, row / 4, row - row / 4);
	setBoundary(&b_hor, 1, column - 1);
	return;
}
/*Sets the coordinates of the obstacles on the map*/
void placeobstacles(obstacles *ok) {
	int counter;
	switch(choice) {
		case 1:
			for(counter = 10; counter <= column - 10; counter += 6) {
				setobstaclepos(ok, row / 4 + 3, counter, row - 3 - row / 2, counter, VER);
				obsno++;
					ok++;
			}
			for(counter = 10; counter <= column - 10; counter += 6	)  {
				setobstaclepos(ok, row - row / 2 + 1, counter, row - 3 - row / 4, counter, VER);
				obsno++;
				ok++;			
			}
		break;
	}
	return;
}
//Basic function which calls all other functions which print the map.
void drawmap(obstacles *ok) {
	drawBoundary();
	printpoints(pts, points);
	drawobstacles(ok, obsno);
	refresh();
	return;
}
/*
* This function is the actual game which is played by the user
* This function controls the movement of the pacman  and the monsters, and checks for obstacles and boundaries in their path.
*/
void setmonstermovement(monster *mon, obstacles *ok) {
	//Visibilty of the pacman to the monsters
	switch(getmonsterdirection(mon)) {
			case UP:
				if(getmonsterposx(mon) - 1 > getfrom(&b_ver) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					hidemonster(mon);
					canseepacman(mon);
					setmonsterpos(mon, getmonsterposx(mon) - 1, getmonsterposy(mon));
				}
				else {
					setmonsterdirection(mon, RIGHT);
				}
				break;
			case DOWN:
				if(getmonsterposx(mon) + 1 < getto(&b_ver) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					hidemonster(mon);
					canseepacman(mon);
					setmonsterpos(mon, getmonsterposx(mon) + 1, getmonsterposy(mon));
				}
				else {
					setmonsterdirection(mon, LEFT);
				}
				break;
			case LEFT:
				if(getmonsterposy(mon) - 2 > getfrom(&b_hor) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					hidemonster(mon);
					canseepacman(mon);
					setmonsterpos(mon, getmonsterposx(mon), getmonsterposy(mon) - 1);
				}
				else {
					setmonsterdirection(mon, UP);
				}
				break;
			case RIGHT:
				if(getmonsterposy(mon) + 2 < getto(&b_hor) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					hidemonster(mon);
					canseepacman(mon);
					setmonsterpos(mon, getmonsterposx(mon), getmonsterposy(mon) + 1);
				}
				else {
					setmonsterdirection(mon, DOWN);
				}
				break;
		}
	return;
}
void continuemovingpac(obstacles *ok) {	
	//Moving the pacman in the same dir if the new dir contains obstacle
	switch(getpacmandirection(&p)) {
		case UP:
			if(getpacmanposx(&p) - 1 > getfrom(&b_ver) && checkforobstacles(ok, obsno,'w', &p) == 1) {
				hidepacman(&p);
				setpacmanpos(&p, getpacmanposx(&p) - 1, getpacmanposy(&p));
			}
			break;
		case DOWN:
			if(getpacmanposx(&p) + 1 < getto(&b_ver) && checkforobstacles(ok, obsno,'s', &p) ==1) {
				hidepacman(&p);
				setpacmanpos(&p, getpacmanposx(&p) + 1, getpacmanposy(&p));
			}
			break;
		case LEFT:
			if(getpacmanposy(&p) - 1 > getfrom(&b_hor) && checkforobstacles(ok, obsno,'a', &p) == 1) {
				hidepacman(&p);
				setpacmanpos(&p, getpacmanposx(&p), getpacmanposy(&p) - 1);
			}
			break;
		case RIGHT:
			if(getpacmanposy(&p) + 2 < getto(&b_hor) && checkforobstacles(o, obsno,'d', &p) == 1) {
				hidepacman(&p);
				setpacmanpos(&p, getpacmanposx(&p), getpacmanposy(&p) + 1);
			}
			break;
	}
}
int movepacman(obstacles *ok) {
	int a;
	FILE *fp;
	int check, dir = p.direction;
	//Controls of pacman
	nodelay(stdscr, TRUE);		//used for continuous movement of the monsters
	noecho();
	keypad(stdscr, TRUE);
	while(1) {
		a = getch();
		if(a != ERR) {
			//Setting the direction of movement on input to getch
			switch(a) {
				case KEY_UP:
					dir = UP;
					break;
				case KEY_DOWN:
					dir = DOWN;
					break;
				case KEY_LEFT:
					dir = LEFT;
					break;
				case KEY_RIGHT	:
					dir = RIGHT;
					break;
			}
		}
		if(load_game == 1) {
			load_game = 0;
			a = 'p';
		}
		if(a == 'p') {		//Pausing the game
			init_pair(5, COLOR_BLACK, COLOR_WHITE);
			attron(COLOR_PAIR(5));
			mvprintw(3, 3, "Press y/n for saving game or p to continue");
			refresh();
			attroff(COLOR_PAIR(5));
			while((a = getchar())) {
				switch(a) {
					case 'y':	//Saving the game and exiting
						fp = fopen("Pacsave.dat", "w");
						fwrite(&row, sizeof(int), 1, fp);
						fwrite(&column, sizeof(int), 1, fp);
						fwrite(&choice, sizeof(int), 1, fp);
						fwrite(&points, sizeof(int), 1, fp);
						fwrite(&obsno, sizeof(int), 1, fp);
						fwrite(&end, sizeof(int), 1, fp);
						fwrite(&score, sizeof(int), 1, fp);
						fwrite(pts, sizeof(point), PTS, fp);
						fwrite(o, sizeof(obstacles), OBS, fp);
						fwrite(&m, sizeof(monster), 1, fp);
						fwrite(&m2, sizeof(monster), 1, fp);
						fwrite(&m3, sizeof(monster), 1, fp);
						fwrite(&p, sizeof(pacman), 1, fp);
						fclose(fp);
						endwin();
						exit(0);
					case 'n':
						endwin();
						exit(0);
				}
				if(a == 'p') {	//unpause
					mvprintw(3, 3, "						");
					break;
				}
			}
		}
		setmonstermovement(&m, o);	//Setting the direction wise coordinates of the monster
		setmonstermovement(&m2, o);
		setmonstermovement(&m3, o);
		set_diff_monster_paths(&m, &m2);	//Repelling property of the monsters
		set_diff_monster_paths(&m, &m3);
		set_diff_monster_paths(&m2, &m3);
		//Deciding the direction of pacman's movement  
		switch(dir) {
			case UP:
				if(getpacmanposx(&p) - 1 > getfrom(&b_ver) && checkforobstacles(ok, obsno,'w', &p) == 1) {
					hidepacman(&p);
					setpacmandirection(&p, UP);
					setpacmanpos(&p, getpacmanposx(&p) - 1, getpacmanposy(&p));
				}
				else {
					continuemovingpac(ok);		//if obstacle is there in the path of new given dir then coninue movement in the same dir
				}
				break;
			case LEFT:
				if(getpacmanposy(&p) - 1 > getfrom(&b_hor) && checkforobstacles(ok, obsno,'a', &p) == 1) {
					hidepacman(&p);
					setpacmandirection(&p, LEFT);
					setpacmanpos(&p, getpacmanposx(&p), getpacmanposy(&p) - 1);
				}
				else {
					continuemovingpac(ok);
				}
				break;
			case DOWN:
				if(getpacmanposx(&p) + 1 < getto(&b_ver) && checkforobstacles(ok, obsno,'s', &p) ==1) {
					hidepacman(&p);
					setpacmandirection(&p, DOWN);
					setpacmanpos(&p, getpacmanposx(&p) + 1, getpacmanposy(&p));
				}
				else {
					continuemovingpac(ok);
				}
				break;
			case RIGHT:
				if(getpacmanposy(&p) + 2 < getto(&b_hor) && checkforobstacles(o, obsno,'d', &p) == 1) {
					hidepacman(&p);
					setpacmandirection(&p, RIGHT);
					setpacmanpos(&p, getpacmanposx(&p), getpacmanposy(&p) + 1);
				}
				else {
					continuemovingpac(ok);
				}
				break;
		}
		//Checking the collision with the monster
		if(checkformonster(&m, 1) == 1 || checkformonster(&m2, 1) == 1 || checkformonster(&m3, 1) == 1) {	//Checking for collision with monster
			drawscore(check);
			return LOOSE;
		}
			
		check = checkforpoints(pts, points, &p);	//Checking if the pacman has collected the points.
		drawscore(check);			//Score update
		if(check) {
			end--;
		}
		printpoints(pts, points);
		printpacman(&p);
		if(end == 0) {		//Condition for winning the game
			clear();
			drawscore(check);
			return WIN;
		}
		printmonsters(&m2);
		printmonsters(&m);
		printmonsters(&m3);
		napms(50);
	}
	nodelay(stdscr, FALSE);
	keypad(stdscr, FALSE);
	return 0;
}
void setscreenpoints() {		//Setting the position of the points on the screen
	int count, counter;
	for(counter = 7; counter < column - 6; counter += 6) {
		for(count = row /4 + 3; count < row - row / 4 ; count += 3) {
			setpointpos(pts + points, count, counter);
			points++;
		}
	}
	end = points;
	return;
}
void menuinflater() {		//Displaying the menu
	ITEM **my_items;
	int c, p = 0;
	MENU *my_menu;
	int n_menu, i;
	noecho();
	keypad(stdscr, TRUE);
	n_menu = ARRAY_SIZE(menu);
	my_items = (ITEM **)calloc(n_menu + 1, sizeof(ITEM *));
	for(i = 0; i < n_menu; ++i)
		my_items[i] = new_item(menu[i], NULL);
	my_items[n_menu] = (ITEM *)NULL;
	my_menu = new_menu((ITEM **)my_items);
	post_menu(my_menu);
	refresh();
	while((c = getch()) != KEY_F(1)) {
		switch(c) {
			case KEY_DOWN:
				if(p < 2) {
					menu_driver(my_menu, REQ_DOWN_ITEM);
					p++;
				}
				break;
			case KEY_UP:
				if(p > 0) {
					menu_driver(my_menu, REQ_UP_ITEM);
					p--;
				}
				break;
			case 10:		//On enter select the proper action
				clear();
				switch(p) {
					case 0:
						load_game = 0;
						return;
					case 1:
						clear();
						load_game = 1;
						return;
					case 2:
						endwin();
						exit(0);
				}	
				break;	
		}
	}
	free_item(my_items[0]);
	free_item(my_items[1]);
	free_menu(my_menu);
}
int startgame() {
	clear();
	FILE *fp;
	getmaxyx(stdscr, row, column);					//getting the window size in rows and columns
	initmonster(&m, &p);
	initmonster(&m2, &p);						//initalizing the monster;
	initmonster(&m3	, &p);
	initpacman(&p);							//initializing the pacman
	placeobstacles(o);						//Setting the obstacle points in the obstacle object
	if(load_game == 1) {						//loading saved file
		fp = fopen("Pacsave.dat", "r");
		if(fp == NULL) {
		printw("No saved file present.");
		getch();
		endwin();
		exit(0);
		}
		fread(&row, sizeof(int), 1, fp);
		fread(&column, sizeof(int), 1, fp);
		fread(&choice, sizeof(int), 1, fp);
		fread(&points, sizeof(int), 1, fp);
		fread(&obsno, sizeof(int), 1, fp);
		fread(&end, sizeof(int), 1, fp);
		fread(&score, sizeof(int), 1, fp);
		fread(pts, sizeof(point), PTS, fp);
		fread(o, sizeof(obstacles), OBS, fp);
		fread(&m, sizeof(monster), 1, fp);
		fread(&m2, sizeof(monster), 1, fp);
		fread(&m3, sizeof(monster), 1, fp);
		fread(&p, sizeof(pacman), 1, fp);
		fclose(fp);
	}
	else if(load_game == 0) {
		setscreenpoints();						//printig the points on the screen.
		setmonsterpos(&m, row / 2 + 4, 2);
		setmonsterpos(&m2, row / 2 - 4, 2);					//Setting the pos of the monster
		setmonsterpos(&m3, row / 2, column - 4);
		setmonsterdirection(&m, DOWN);
		setmonsterdirection(&m2, RIGHT);
		setmonsterdirection(&m3, LEFT);
		setpacmanpos(&p, row / 2 + 4, getpointposy(pts + points / 2)); 	//setting the pacman to the screen.
	}
	start_color();
	curs_set(FALSE);						//no cursor
	drawmap(o);							//drawing maps with boundaries and obstacles
	drawscore(0);							//printing the score board
	printpacman(&p);						//drawing the pacman
	printmonsters(&m);
	printmonsters(&m2);						//jprinting the monsters
	printmonsters(&m3);
	return movepacman(o);
}
int main(int argc, char *argv[]) {
	initscr();							//initialzing the screen
	restart : menuinflater();	
	attron(COLOR_PAIR(5));
	if(startgame() == WIN) {					//moving the pacman
		clear();
		mvprintw(row / 2 + 5, column / 2 - 8, "Press Enter to return to menu.");
		mvprintw(row / 2, column / 2, "YOU WIN");		//printing after the game is over.
		drawscore(0);
	}
	else {
		clear();
		mvprintw(row / 4 + 5, column / 2 - 8, "Press Enter to return to menu.");
		mvprintw(row / 2, column / 2, "YOU LOST");		//printing after the game is over.
		drawscore(0);
	}
	attroff(COLOR_PAIR(5));
	nodelay(stdscr, FALSE);
	while(1) {
		char t = getch();
		if(t == 10) {		//restarting the game and resetting all the variables used in the game
			clear();
			choice = 1;
			score = 0;
			load_game = 0;
			points = 0;
			obsno = 0;
			goto restart;
			break;
		}
	}
	endwin();
	return 0;
}

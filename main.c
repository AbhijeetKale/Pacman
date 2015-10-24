#include <ncurses.h>
#include <stdlib.h>
#include "bounds.h"
#include "obstacles.h"
#define PTS 300
#define OBS 20
#define WIN 1
#define LOOSE 0
/* row and column for the dimensions of the window
* Choice is the map id which is assigned by the main arguement
* Points is max possible score than can be scored in this round
* Obsno are the number of pbstacles
*/
int row, column, choice, points = 0, obsno = 0, end;
point pts[PTS];
boundary b_ver, b_hor;
/*This function draws the score bard with the score and the level*/
void drawscore(int update) {
	static int score = 0;
	score += update;
	mvprintw(2, column / 2, "SCORE : %d", score);
	mvprintw(4, column / 2, "LEVEL : %d", choice);
	refresh();
	return;
}
/*Draws the boundary of the map*/
void drawBoundary() {
	int i;
	switch(choice) {
		case 1:
			for(i = 0; i < column; i++) {
				mvprintw(row / 4, i, "-");
			}
			for(i = 0; i < column; i++) {
				mvprintw(row - (row / 4), i, "-");
			}
			for(i = row / 4; i < row - (row / 4); i++) {
				mvprintw(i, 0, "=");
			}
			for(i = row / 4; i < row - (row / 4); i++) {
				mvprintw(i, column - 1, "=");
			}
			break;
	}
	setBoundary(&b_ver, row / 4, row - row / 4);
	setBoundary(&b_hor, 0, column);
	return;
}
/*Sets the coordinates of the obstacles on the map*/
void placeobstacles(obstacles *o) {
	int counter;
	switch(choice) {
		case 1:
			for(counter = 12; counter < column - 8; counter += 8) {
				setobstaclepos(o, row /4 + 3, counter, row - 3 - row / 2, counter, VER);
				obsno++;
				o++;
			}
			for(counter = 12; counter < column - 8; counter += 8)  {
				setobstaclepos(o, row - row / 2 + 1, counter, row - 3 - row / 4, counter, VER);
				obsno++;
				o++;			
			}
		break;
	}
	return;
}
//Basic function which calls all other functions which print the map.
void drawmap(obstacles *o) {
	drawBoundary();
	printpoints(pts, points);
	drawobstacles(o, obsno);
	refresh();
	return;
}
/*
* This function is the actual game which is played by the user
* This function controls the movement of the pacman  and the monsters, and checks for obstacles and boundaries in their path.
*/
int movepacman(pacman *p, obstacles *o, monster *m) {
	keypad(stdscr, TRUE);
	char a;
	int check;
	//Controls of pacman
	nodelay(stdscr, TRUE);
	while(1) {
		a = getch();
		noecho();
		switch(a) {
			case 'w':
				if(getpacmanposx(p) - 1 > getfrom(&b_ver)) {
					if(checkforobstacles(o, obsno,'w', p) == 1) {
						clear();
						setpacmanpos(p, getpacmanposx(p) - 1, getpacmanposy(p));
					}
				}
				break;
			case 'a':
				if(getpacmanposy(p) - 1 > getfrom(&b_hor)) {
					if(checkforobstacles(o, obsno,'a', p) == 1) {
						clear();
						setpacmanpos(p, getpacmanposx(p), getpacmanposy(p) - 1);
					}
				}
				break;
			case 's':
				if(getpacmanposx(p) + 1 < getto(&b_ver)) {
					if(checkforobstacles(o, obsno,'s', p) ==1) {
						clear();
						setpacmanpos(p, getpacmanposx(p) + 1, getpacmanposy(p));
					}
				}
				break;
			case 'd':
				clear();
				if(getpacmanposy(p) + 2	 < getto(&b_hor)) {
					if(checkforobstacles(o, obsno,'d', p) == 1) {
						clear();
						setpacmanpos(p, getpacmanposx(p), getpacmanposy(p) + 1);
					}
				}
				break;
		}
		if(checkformonster(m, 1) == 1) {
			return LOOSE;
		}
		check = checkforpoints(pts, points, p);
		drawscore(check);
		if(check) {
			end--;
		}
		drawmap(o);
		printpacman(p);
		printmonsters(m, 1);
		if(end == 0) {
			return WIN;
		}
	}
	nodelay(stdscr, FALSE);
	keypad(stdscr, FALSE);
	return 0;
}
void setscreenpoints() {
	int count, counter;
	for(counter = 8; counter < column; counter += 8) {
		for(count = row /4 + 3; count < row - row / 4 ; count += 3) {
			setpointpos(pts + points, count, counter);
			points++;
		}
	}
	end = points;
	return;
}
int main(int argc, char *argv[]) {
	pacman p;							// our pacman
	obstacles o[OBS];
	monster m;							// our monster
	initscr();							//initialzing the screen
	choice = atoi(argv[1]); 					//setting the map	
	getmaxyx(stdscr, row, column);					//getting the window size in rows and columns
	initmonster(&m, &p);						//initalizing the monster;
	initpacman(&p);							//initializing the pacman
	setscreenpoints();						//printig the points on the screen.
	placeobstacles(o);						//Setting the obstacle points in the obstacle object
	setmonsterpos(&m, row / 2, 2);					//Setting the pos of the monster
	setpacmanpos(&p, row / 2, getpointposy(pts + points / 2)); 	//setting the pacman to the screen.
	start_color();
	curs_set(FALSE);						//no cursor
	drawmap(o);							//drawing maps with boundaries and obstacles
	drawscore(0);							//printing the score board
	printpacman(&p);						//drawing the pacman
	printmonsters(&m, 1);						//jprinting the monsters
	if(movepacman(&p, o, &m) == WIN) {					//moving the pacman
		mvprintw(row / 2, column / 2, "YOU WIN");		//printing after the game is over.
		refresh();
	}
	else {
		mvprintw(row / 2, column / 2, "YOU LOOSE");		//printing after the game is over.
		refresh();
	}
	while(1) {
		if(getch() == 'e') {
			break;
		}
	}
	endwin();
	return 0;
}

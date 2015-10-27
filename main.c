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
monster m, m2;						// our monster
pacman p;							// our pacman
obstacles o[OBS];
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
void placeobstacles(obstacles *ok) {
	int counter;
	switch(choice) {
		case 1:
			for(counter = 12; counter < column - 8; counter += 8) {
				setobstaclepos(ok, row /4 + 3, counter, row - 3 - row / 2, counter, VER);
				obsno++;
				ok++;
			}
			for(counter = 12; counter < column - 8; counter += 8)  {
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
	switch(getmonsterdirection(mon)) {
			case UP:
				if(getmonsterposx(mon) - 1 > getfrom(&b_ver) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					clear();
					canseepacman(mon);
					setmonsterpos(mon, getmonsterposx(mon) - 1, getmonsterposy(mon));
				}
				else {
					setmonsterdirection(mon, RIGHT);
				}
				break;
			case DOWN:
				if(getmonsterposx(mon) + 1 < getto(&b_ver) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					clear();
					canseepacman(mon);
					setmonsterpos(mon, getmonsterposx(mon) + 1, getmonsterposy(mon));
				}
				else {
					setmonsterdirection(mon, LEFT);
				}
				break;
			case LEFT:
				if(getmonsterposy(mon) - 2 > getfrom(&b_hor) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					clear();
					canseepacman(mon);
					setmonsterpos(mon, getmonsterposx(mon), getmonsterposy(mon) - 1);
				}
				else {
					setmonsterdirection(mon, UP);
				}
				break;
			case RIGHT:
				if(getmonsterposy(mon) + 2 < getto(&b_hor) && monstercheckforobstacles(ok, obsno, mon) == 1) {
					clear();
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
int movepacman(obstacles *ok) {
	keypad(stdscr, TRUE);
	char a;
	int check;
	//Controls of pacman
	nodelay(stdscr, TRUE);
	noecho();
	while(1) {
		a = getch();
		if(a != ERR) {
			switch(a) {
				case 'w':
					setpacmandirection(&p, UP);
					break;
				case 's':
					setpacmandirection(&p, DOWN);
					break;
				case 'a':
					setpacmandirection(&p, LEFT);
					break;
				case 'd':
					setpacmandirection(&p, RIGHT);
					break;
			}
		}
		setmonstermovement(&m, o);	//Setting the direction wise coordinates of the monster
		setmonstermovement(&m2, o);
//Deciding the direction of pacman's movement  
		switch(getpacmandirection(&p)) {
			case UP:
				if(getpacmanposx(&p) - 1 > getfrom(&b_ver) && checkforobstacles(ok, obsno,'w', &p) == 1) {
					clear();
					setpacmanpos(&p, getpacmanposx(&p) - 1, getpacmanposy(&p));
				}
				break;
			case LEFT:
				if(getpacmanposy(&p) - 1 > getfrom(&b_hor) && checkforobstacles(ok, obsno,'a', &p) == 1) {
					clear();
					setpacmanpos(&p, getpacmanposx(&p), getpacmanposy(&p) - 1);
				}
				break;
			case DOWN:
				if(getpacmanposx(&p) + 1 < getto(&b_ver) && checkforobstacles(ok, obsno,'s', &p) ==1) {
					clear();
					setpacmanpos(&p, getpacmanposx(&p) + 1, getpacmanposy(&p));
				}
				break;
			case RIGHT:
				if(getpacmanposy(&p) + 2 < getto(&b_hor) && checkforobstacles(o, obsno,'d', &p) == 1) {
					clear();
					setpacmanpos(&p, getpacmanposx(&p), getpacmanposy(&p) + 1);
				}
				break;
		}
		if(checkformonster(&m, 1) == 1 || checkformonster(&m2, 1) == 1) {	//Checking for collision with monster
			clear();
			drawscore(check);
			return LOOSE;
		}
			
		check = checkforpoints(pts, points, &p);	//Checking if the pacman has collected the points.
		drawscore(check);
		if(check) {
			end--;
		}
		drawmap(o);
		printpacman(&p);
		if(end == 0) {
			clear();
			drawscore(check);
			return WIN;
		}
		printmonsters(&m2);
		printmonsters(&m);
		napms(50);
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
	initscr();							//initialzing the screen
	choice = atoi(argv[1]); 					//setting the map	
	getmaxyx(stdscr, row, column);					//getting the window size in rows and columns
	initmonster(&m, &p);
	initmonster(&m2, &p);						//initalizing the monster;
	initpacman(&p);							//initializing the pacman
	placeobstacles(o);						//Setting the obstacle points in the obstacle object
	setscreenpoints();						//printig the points on the screen.
	setmonsterpos(&m, row / 2 + 4, 2);
	setmonsterpos(&m2, row / 2 - 4, 2);					//Setting the pos of the monster
	setmonsterdirection(&m, DOWN);
	setmonsterdirection(&m2, RIGHT);
	setpacmanpos(&p, row / 2, getpointposy(pts + points / 2)); 	//setting the pacman to the screen.
	start_color();
	curs_set(FALSE);						//no cursor
	drawmap(o);							//drawing maps with boundaries and obstacles
	drawscore(0);							//printing the score board
	printpacman(&p);						//drawing the pacman
	printmonsters(&m);
	printmonsters(&m2);						//jprinting the monsters
	if(movepacman(o) == WIN) {					//moving the pacman
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

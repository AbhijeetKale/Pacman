#include <ncurses.h>
#include <stdlib.h>
#include "bounds.h"
#include "obstacles.h"
#define PTS 300
#define OBS 20
#define PRESSED 1
#define NOT_PRESSED 0
/* row and column for the dimensions of the window
* Choice is the map id which is assigned by the main arguement
* Points is max possible score than can be scored in this round
* Obsno are the number of pbstacles
*/
int row, column, choice, points = 0, obsno = 0, end;
point pts[PTS];
boundary b_ver, b_hor;
void drawscore(int update) {
	static int score = 0;
	score += update;
	mvprintw(2, column / 2, "SCORE : %d", score);
	mvprintw(4, column / 2, "LEVEL : %d", choice);
	refresh();
	return;
}
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
void placeobstacles(obstacles *o) {
	int counter;
	switch(choice) {
		case 1:
			for(counter = 12; counter < column; counter += 8) {
				setobstaclepos(o, row /4 + 3, counter, row - 3 - row / 4, counter, VER);
				obsno++;
				o++;
			}
		break;
	}
	return;
}
void drawmap(obstacles *o) {
	drawBoundary();
	printpoints(pts, points);
	drawobstacles(o, obsno);
	refresh();
	return;
}
int movepacman(pacman *p, obstacles *o) {
	keypad(stdscr, TRUE);
	char a;
	noecho();
	int check, state;
	//Controls of pacman
	nodelay(stdscr, TRUE);
	while(1) {
		a = getch();
		state = NOT_PRESSED;
		switch(a) {
			case 'w':
				if(getpacmanposx(p) - 1 > getfrom(&b_ver)) {
					if(checkforobstacles(o, obsno,'w', p) == 1) {
						clear();
						setpacmanpos(p, getpacmanposx(p) - 1, getpacmanposy(p));
						state = PRESSED;
					}
				}
				break;
			case 'a':
				if(getpacmanposy(p) - 1 > getfrom(&b_hor)) {
					if(checkforobstacles(o, obsno,'a', p) == 1) {
						clear();
						setpacmanpos(p, getpacmanposx(p), getpacmanposy(p) - 1);
						state = PRESSED;
					}
				}
				break;
			case 's':
				if(getpacmanposx(p) + 1 < getto(&b_ver)) {
					if(checkforobstacles(o, obsno,'s', p) ==1) {
						clear();
						setpacmanpos(p, getpacmanposx(p) + 1, getpacmanposy(p));
						state = PRESSED;
					}
				}
				break;
			case 'd':
				if(getpacmanposy(p) + 2	 < getto(&b_hor)) {
					if(checkforobstacles(o, obsno,'d', p) == 1) {
						clear();
						setpacmanpos(p, getpacmanposx(p), getpacmanposy(p) + 1);
						state = PRESSED;
					}
				}
				break;
		}
		if(state) {
			check = checkforpoints(pts, points, p);
			drawscore(check);
			if(check) {
				end--;
				if(end == 0) {
					return 0;
				}
			}
			drawmap(o);
			printpacman(p);
		}
	}
	nodelay(stdscr, TRUE);
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
	pacman p;		// our pacman
	obstacles o[OBS];
	initscr();
	start_color();
	initpacman(&p);
	choice = atoi(argv[1]);  //setting the map	
	getmaxyx(stdscr, row, column);	//getting the window size in rows and columns
	curs_set(FALSE);	//no cursor
	setscreenpoints();	//printig the points on the screen.
	placeobstacles(o);
	drawmap(o);		//drawing maps with boundaries and obstacles
	drawscore(0);		//printing the score board
	setpacmanpos(&p, row / 2, getpointposy(pts + points / 2)); //setting the pacman to the screen.
	printpacman(&p);	//drawing the pacman
	if(movepacman(&p, o) == 0) {		//moving the pacman
		mvprintw(row / 2, column / 2, "YOU WIN");
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

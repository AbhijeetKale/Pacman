#include "point.h"
void printpoints(point *p, int n) {
	int count;
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	attron(COLOR_PAIR(2));
	for(count = 0; count < n; count++) {
		if(p->activate == 1) {
			mvprintw(p->posx, p->posy, "+");
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
void setpointpos(point *p, int x, int y) {
	p->posx = x;
	p->posy = y;
	p->activate = 1;
	return;
}
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


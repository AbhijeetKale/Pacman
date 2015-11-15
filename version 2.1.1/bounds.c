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
#include "bounds.h"
void initBoundary(boundary *b) {
	b->start = 0;
	b->end = 0;
}
//setting the boundary
void setBoundary(boundary *b, int from, int to) {
	b->start = from;
	b->end = to;
}
//get initial coordinates for boundary
int getfrom(boundary *b) {
	return b->start;
}
//get end coordinates for boundary
int getto(boundary *b) {
	return b->end;
}

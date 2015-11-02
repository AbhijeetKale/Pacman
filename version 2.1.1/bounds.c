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

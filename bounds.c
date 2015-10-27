#include "bounds.h"
void initBoundary(boundary *b) {
	b->start = 0;
	b->end = 0;
}
void setBoundary(boundary *b, int from, int to) {
	b->start = from;
	b->end = to;
}
int getfrom(boundary *b) {
	return b->start;
}
int getto(boundary *b) {
	return b->end;
}

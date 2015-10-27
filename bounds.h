typedef struct boundary {
	int start, end;
} boundary;
void initBoundary(boundary *);
void setBoundary(boundary *, int, int);
int getfrom(boundary *);
int getto(boundary *);

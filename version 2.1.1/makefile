
try: main.o pacman.o bounds.o point.o obstacles.o
	cc main.o pacman.o bounds.o point.o obstacles.o -l menu -l ncurses -o project
main.o: main.c pacman.h bounds.h point.h obstacles.h
	cc -Wall -c main.c
obstacles.o: obstacles.h obstacles.c
	cc -Wall -c obstacles.c
point.o: point.h point.c
	cc -Wall -c point.c
pacman.o: pacman.c pacman.h
	cc -Wall -c pacman.c
bounds.o: bounds.h
	cc -Wall -c bounds.c


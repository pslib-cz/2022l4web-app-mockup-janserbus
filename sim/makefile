make:
	gcc -Wall -c population.c 
	gcc -Wall -c input.c 
	gcc -Wall -c draw.c 
	gcc -Wall -c update.c 
	gcc -g -Wall population.o update.o draw.o input.o -o popsim `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lSDL2_ttf -lm
	rm -f *.o
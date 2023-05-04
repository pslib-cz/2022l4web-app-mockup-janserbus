output: engine.o components.o master.o
	gcc -g3 -Wall -o main master.o engine.o components.o -lSDL2 -lSDL2_ttf -lm

engine.o: gui.o engine/core.c engine/core.h engine/list.c engine/list.h engine/processes.c engine/processes.h engine/time.c engine/time.h config.h
	gcc -g3 -Wall -c engine/core.c engine/time.c engine/processes.c engine/list.c
	ld -r gui.o core.o time.o list.o processes.o -o engine.o

gui.o: engine/gui/graph.c engine/gui/graph.h config.h
	gcc -g3 -Wall -c engine/gui/graph.c
	ld -r graph.o -o gui.o

components.o: components/population.c components/population.h components/resources.c components/resources.h components.h config.h
	gcc -g3 -Wall -c components/population.c components/resources.c
	ld -r resources.o population.o -o components.o

master.o: main.c main.h loop/input.c loop/update.c loop/draw.c config.h
	gcc -g3 -Wall -c main.c loop/input.c loop/update.c loop/draw.c
	ld -r main.o input.o update.o draw.o -o master.o

clean:
	rm *.o
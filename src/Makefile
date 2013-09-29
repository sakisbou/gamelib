PROGNAME=game

ARGS=-Wall -O2
OBJ=main.o sdl.o opengl.o textures.o lander.o terrain.o earth.o
LIBS=-lSDL2 -lGL -lGLU -lIL -lm

$(PROGNAME):$(OBJ)
	gcc $(ARGS) -o $(PROGNAME) $(LIBS) $(OBJ)

main.o:main.c
	gcc $(ARGS) -c main.c

sdl.o:sdl.h sdl.c options.h
	gcc $(ARGS) -c sdl.c

opengl.o:opengl.h opengl.c options.h
	gcc $(ARGS) -c opengl.c

lander.o:lander.h lander.c
	gcc $(ARGS) -c lander.c

terrain.o:terrain.h terrain.c
	gcc $(ARGS) -c terrain.c

earth.o:earth.h earth.c
	gcc $(ARGS) -c earth.c

textures.o:textures.h textures.c
	gcc $(ARGS) -c textures.c

clean:
	rm -rf *.o *~ game

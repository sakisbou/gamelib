PROGNAME=game

ARGS=-Wall -O2
OBJ=main.o sdl.o opengl.o objects.o textures.o
LIBS=-lSDL2 -lGLU -lIL

$(PROGNAME):$(OBJ)
	gcc $(ARGS) -o $(PROGNAME) $(LIBS) $(OBJ)

main.o:main.c
	gcc $(ARGS) -c main.c

sdl.o:sdl.h sdl.c options.h
	gcc $(ARGS) -c sdl.c

opengl.o:opengl.h opengl.c options.h
	gcc $(ARGS) -c opengl.c

objects.o:objects.h objects.c
	gcc $(ARGS) -c objects.c

textures.o:textures.h textures.c
	gcc $(ARGS) -c textures.c

clean:
	rm -rf *.o game

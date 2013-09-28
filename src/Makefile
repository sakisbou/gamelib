PROGNAME=game

ARGS=-Wall -O2
OBJ=main.o sdl.o opengl.o objects.o textures.o test_object.o lander.o
LIBS=-lSDL2 -lGL -lGLU -lIL -lILU

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

test_object.o:test_object.h test_object.c
	gcc $(ARGS) -c test_object.c

lander:lander.h lander.c
	gcc $(ARGS) -c lander.c

textures.o:textures.h textures.c
	gcc $(ARGS) -c textures.c

clean:
	rm -rf *.o *~ game

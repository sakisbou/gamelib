PROGNAME=game

ARGS=-Wall -O2
MODELS=lander.o terrain.o earth.o
OBJ=main.o sdl.o opengl.o textures.o game_data.o logic.o scene.o $(MODELS)
LIBS=-lSDL2 -lGL -lGLU -lIL -lm

$(PROGNAME):$(OBJ)
	gcc $(ARGS) -o $(PROGNAME) $(LIBS) $(OBJ)

main.o:main.c
	gcc $(ARGS) -c main.c

sdl.o:sdl.h sdl.c options.h
	gcc $(ARGS) -c sdl.c

opengl.o:opengl.h opengl.c options.h
	gcc $(ARGS) -c opengl.c

lander.o:models/lander.c
	gcc $(ARGS) -c models/lander.c

terrain.o:models/terrain.c
	gcc $(ARGS) -c models/terrain.c

earth.o:models/earth.c
	gcc $(ARGS) -c models/earth.c

textures.o:textures.h textures.c
	gcc $(ARGS) -c textures.c

game_data.o:game_data.h game_data.c
	gcc $(ARGS) -c game_data.c

logic.o:logic.h logic.c
	gcc $(ARGS) -c logic.c

scene.o:scene.h scene.c
	gcc $(ARGS) -c scene.c

clean:
	rm -rf *.o *~ models/*~ blender_gl_export/*~ game

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdarg.h>

#include "sdl.h"
#include "options.h"



/*
    --- error management -------------------------------------------------------
*/

/*
    syserror
*/

void syserror_(char *file, int line)
{
  perror(PROGNAME);
  fprintf(stderr, ": %s : line %d\n", file, line);
  exit(errno);
}




/*
    SDL_error
*/

void sdl_error_(char *file, int line)
{
  fprintf(stderr, "%s: %s: line %d: %s\n", PROGNAME, file, line, SDL_GetError());
  exit(EXIT_FAILURE);
}




/*
    usererror
*/

void usererror_(char *format, ...)
{
  va_list ap;
  char formatstr[1000];

  sprintf(formatstr, "%s%s%s", PROGNAME, " : %s : line %i : ", format);

  va_start(ap, format);
  vfprintf(stderr, formatstr, ap);
  va_end(ap);

  exit(EXIT_FAILURE);
}




/*
    --- initialization and cleanup ---------------------------------------------
*/




/*
    sdl_init
*/

void sdl_init(void)
{
  int r;
  uint32_t fs = 0; if(FULLSCREEN) fs = SDL_WINDOW_FULLSCREEN;

  r = SDL_Init(
                SDL_INIT_VIDEO |
                SDL_INIT_AUDIO |
                SDL_INIT_TIMER |
                SDL_INIT_EVENTS
              );
  if(r != 0) sdl_error();

  if(SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32)!=0) sdl_error();
  if(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24)!=0) sdl_error();
  if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)!=0) sdl_error();

  main_window = SDL_CreateWindow( 
                                  PROGNAME,
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,	
                                  RESX, RESY,	
                                  SDL_WINDOW_OPENGL | fs
                                );
  if(main_window == NULL) sdl_error();

  main_gl_context = SDL_GL_CreateContext(main_window);
  if(main_gl_context == NULL) sdl_error();
}




/*
    sdl_cleanup
*/

void sdl_cleanup(void)
{
  SDL_GL_DeleteContext(main_gl_context);
  SDL_DestroyWindow(main_window); 
  SDL_Quit();
}




/*
    --- input ------------------------------------------------------------------
*/




/*
    getkey
*/

uint8_t getkey(int key)
{
  SDL_PumpEvents();
  const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
  return keyboard[key];
}




/*
    --- time -------------------------------------------------------------------
*/




static uint32_t prev_time;




/*
    init_time
*/

void init_time(void) { prev_time = SDL_GetTicks(); }




/*
    get_rel_time
*/

uint32_t get_rel_time(void)
{
  uint32_t time = SDL_GetTicks();
  uint32_t rel_time = time - prev_time;
  prev_time = time;
  return rel_time;
}





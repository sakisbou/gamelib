#ifndef __OS__
#define __OS__




#include <stdint.h>
#include <SDL2/SDL.h>



/*
    globals
*/

SDL_Window *main_window;
SDL_GLContext main_gl_context;




/*
    macros as functions
*/

#define syserror() syserror_(__FILE__, __LINE__)
#define sdl_error() sdl_error_(__FILE__, __LINE__)
#define usererror(FORMAT, args...) usererror_(FORMAT, __FILE__, __LINE__, ## args)




/*
    functions
*/

void syserror_(char *file, int line);
void sdl_error_(char *file, int line);
void usererror_(char *format, ...);

void sdl_init(void);
void sdl_cleanup(void);

uint8_t getkey(int key);

void init_time(void);
uint32_t get_rel_time(void);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "opengl.h"
#include "sdl.h"
#include "objects.h"
#include "textures.h"




/*
    init
*/

void init(void)
{
  sdl_init();
  gl_init();
  gl_textures_init();
  init_time();
}




/*
    cleanup
*/

void cleanup(void)
{
  sdl_cleanup();
}




/*
    main
*/

int main(int argc, char **argv)
{
  init();

  GLfloat angle = 0, camera_angle = 0;

  glMatrixMode(GL_PROJECTION); // used as camera
  glPushMatrix(); // projection settings must be saved

  for(;;)
  {
    glClearColor(0.3, 0.56, 0.85, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle++; if(angle > 360) angle = 0;
    camera_angle += 0.2; if(camera_angle > 360) camera_angle = 0;



    glMatrixMode(GL_PROJECTION); // used for setting up the scene
    glPopMatrix(); // restore initial setup
    glPushMatrix(); // save it again for the next run

    glTranslatef(0, 0, -12);
    glRotatef(camera_angle, 0.0, 1.0, 0.0);
    glTranslatef(0, 0, 12);
  


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(-4, -3, -12);
    glRotatef(angle, 1.0, 0.0, 0.0);
    draw_crate_01();

    glLoadIdentity();
    glTranslatef(4, -3, -12);
    glRotatef(angle, 0.0, 1.0, 0.0);
    draw_crate_02();

    glLoadIdentity();
    glTranslatef(4, 3, -12);
    glRotatef(angle, 0.0, 0.0, 1.0);
    draw_crate_03();

    glLoadIdentity();
    glTranslatef(-4, 3, -12);
    glRotatef(angle, 1.0, 0.0, 1.0);
    draw_crate_04();

    glFlush();
    SDL_GL_SwapWindow(main_window);

    if(getkey(SDL_SCANCODE_ESCAPE)) break;
  }
  
  cleanup();
  return(EXIT_SUCCESS);
}

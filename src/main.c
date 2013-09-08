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
  time_init();
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

  for(;;)
  {
    glClearColor(0.3, 0.56, 0.85, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle++; if(angle > 360) angle = 0;
    camera_angle += 0.38; if(camera_angle > 360) camera_angle = 0;


    // camera setup
    glLoadIdentity();
    glTranslatef(0, 0, -12);
    glRotatef(camera_angle, 0.0, 1.0, 0.0);
    glTranslatef(0, 0, 12);

    /*
       models can be placed in the scene using opengl
       by saving the modelview matrix before drawing the model
       and restoring it right afterwards.
    */
    glPushMatrix();
    glTranslatef(-4, -3, -12);
    glRotatef(angle, 1.0, 0.0, 0.0);
    draw_crate_01();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, -3, -12);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glScalef(1.5, 1.5, 1.5);
    draw_crate_02();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 3, -12);
    glRotatef(angle, 0.0, 0.0, 1.0);
    draw_crate_03();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 3, -12);
    glRotatef(angle, 1.0, 0.0, 1.0);
    glScalef(0.5, 0.5, 0.5);
    draw_crate_04();
    glPopMatrix();

    glFlush();
    SDL_GL_SwapWindow(main_window);

    if(getkey(SDL_SCANCODE_ESCAPE)) quit();
    if(update_events() == -1) break;
  }
  
  cleanup();
  return(EXIT_SUCCESS);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "opengl.h"
#include "sdl.h"
#include "objects.h"
#include "textures.h"

#include "test_object.h"
#include "lander.h"




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

  GLfloat angle = 0, angle_step = 0, camera_angle = 0;

//  GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 0.5 };
//  GLfloat mat_shininess[] = { 1.0 };
//  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
  GLfloat light_diffuse[] = { 0.15, 0.15, 0.15, 1.0 };
//  GLfloat light_specular[] = { 0.1, 0.1, 0.1, 0.1 };
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  GLfloat light_position[] = { 10.0, 0.0, 6.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
  light_position[1] = 10.0;
  light_position[2] = -5.0;
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);



  for(;;)
  {
//    glClearColor(0.3, 0.56, 0.85, 1.0);
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle += angle_step;
    if(angle > 20) angle_step -= .0005;
    else angle_step += .0005;

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
    glTranslatef(0, 0, -16);
    glRotatef(angle-90, 1.0, 0.0, 0.0);
    glScalef(0.2, 0.2, 0.15);
    draw_lander();
    glPopMatrix();

    glFlush();
    SDL_GL_SwapWindow(main_window);

    if(getkey(SDL_SCANCODE_ESCAPE)) quit();
    if(update_events() == -1) break;
  }
  
  cleanup();
  return(EXIT_SUCCESS);
}

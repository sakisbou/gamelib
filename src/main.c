#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "opengl.h"
#include "sdl.h"
#include "textures.h"

#include "terrain.h"
#include "lander.h"
#include "earth.h"




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

  GLfloat angle = 10, angle_step = 0, position_angle = 0, cam_x_pos=70;

  GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  GLfloat light_position[4];
  GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_diffuse_1[] = { 2.0, 2.0, 2.0, 1.0 };
//  GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 0.5 };
//  GLfloat mat_shininess[] = { 1.0 };

//  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//  GLfloat light_specular[] = { 0.5, 0.5, 0.5, 0.5 };
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse_1);


  for(;;)
  {
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle += angle_step;
    if(angle > 40) angle_step -= .002;
    else angle_step += .002;

    position_angle += 0.3; if(position_angle > 360) position_angle = 0;

    cam_x_pos = 50 * sin(position_angle * M_PI / 180);

    // camera position
    glLoadIdentity();
    glTranslatef(cam_x_pos, 0, -12);
    glRotatef(0.0, 0.0, 0.0, 0.0);
    glTranslatef(0, 0, 12);

    // light positions
    light_position[0] = 100.0;
    light_position[1] = 50.0;
    light_position[2] = 30.0;
    light_position[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    light_position[0] = 1000.0;		// x
    light_position[1] = 0.0;		// y
    light_position[2] = 100.0;		// z
    light_position[3] = 0.0;
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    /*
       models can be placed in the scene using opengl
       by saving the modelview matrix before drawing the model
       and restoring it right afterwards.
    */

    glEnable(GL_LIGHT1);
    glPushMatrix(); // save camera
    glTranslatef(-1000, 1000, -3000);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(100.0, 100.0, 100.0);
    draw_earth();
    glPopMatrix(); // restore camera
    glDisable(GL_LIGHT1);

    glEnable(GL_LIGHT0);
    glPushMatrix(); // save camera
    glTranslatef(0, -20, -90);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(150.0, 150.0, 20.0);
    draw_terrain();
    glPopMatrix(); // restore camera

    glPushMatrix(); // save camera
    glTranslatef(-cam_x_pos, 0, -50); // object's orbit center
    glRotatef(position_angle, 0.0, 1.0, 0.0); // orbit advancement
    glTranslatef(0, 0, -26); // orbit's radius
    glRotatef(angle-90, 1.0, 0.0, 0.0); // object's rotation around it's own axis
    glScalef(0.2, 0.2, 0.16); //object scaling
    draw_lander();
    glPopMatrix(); // restore camera
    glDisable(GL_LIGHT0);

    glFlush();
    SDL_GL_SwapWindow(main_window);

    if(getkey(SDL_SCANCODE_ESCAPE)) quit();
    if(update_events() == -1) break;
  }
  
  cleanup();
  return(EXIT_SUCCESS);
}

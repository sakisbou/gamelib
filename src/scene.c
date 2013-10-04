#include <GL/gl.h>

#include "sdl.h"
#include "textures.h"
#include "models.h"
#include "game_data.h"




static GLfloat light_position[4];
static GLfloat light_ambient[4];
static GLfloat light_diffuse[4];




/*
    renders the scene
*/

void render_scene(void)
{
  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_LIGHT0);

  // camera position
  glLoadIdentity();
  glTranslatef(-(lander_x_pos * 0.7), 0, -12);
  glRotatef(0.0, 0.0, 0.0, 0.0);
  glTranslatef(0, 0, 12);

  /*
     models can be placed in the scene using opengl
     by saving the modelview matrix before drawing the model
     and restoring it right afterwards.
  */

  // earth

  light_position[0] = 500.0;		// x
  light_position[1] = 0.0;		// y
  light_position[2] = 100.0;		// z
  light_position[3] = 0.0;
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  light_diffuse[0] = 2;
  light_diffuse[1] = 2;
  light_diffuse[2] = 2;
  light_diffuse[3] = 1;
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  light_ambient[0] = 0;
  light_ambient[1] = 0;
  light_ambient[2] = 0;
  light_ambient[3] = 0;
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

  glPushMatrix(); // save camera
  glTranslatef(-1000, 1000, -3000);
  glRotatef(-90, 1.0, 0, 0);
  glRotatef(earth_angle, 0, 0, 1);
  glScalef(100.0, 100.0, 100.0);
  draw_earth();
  glPopMatrix(); // restore camera

  // terrain

  light_position[0] = 100.0;
  light_position[1] = 30.0;
  light_position[2] = 30.0;
  light_position[3] = 0.0;
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  light_diffuse[0] = 1.5;
  light_diffuse[1] = 1.5;
  light_diffuse[2] = 1.5;
  light_diffuse[3] = 1;
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

  glPushMatrix(); // save camera
  glTranslatef(0, -20, -90);
  glRotatef(-90, 1.0, 0.0, 0.0);
  glScalef(150.0, 150.0, 20.0);
  draw_terrain();
  glPopMatrix(); // restore camera

  // lander

  light_position[0] = 100.0;
  light_position[1] = 50.0;
  light_position[2] = 30.0;
  light_position[3] = 0.0;
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  light_diffuse[0] = 1;
  light_diffuse[1] = 1;
  light_diffuse[2] = 1;
  light_diffuse[3] = 1;
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  light_ambient[0] = 0.5;
  light_ambient[1] = 0.5;
  light_ambient[2] = 0.5;
  light_ambient[3] = 0.5;
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

  glPushMatrix(); // save camera
  glTranslatef(lander_x_pos, lander_y_pos, lander_z_pos);
  glRotatef(-90, 1.0, 0.0, 0.0);
  glRotatef(lander_x_pos_rate * 90, 0.0, 1.0, 0.0);    
  glRotatef(lander_z_pos_rate * 90, 1.0, 0.0, 0.0);    
  glRotatef(-45 + lander_y_angle, 0.0, 0.0, 1.0);
  glScalef(0.2, 0.2, 0.16);
  draw_lander();
  glPopMatrix(); // restore camera

  glFlush();
  SDL_GL_SwapWindow(main_window);
}

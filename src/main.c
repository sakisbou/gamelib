#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "opengl.h"
#include "sdl.h"

#include "textures.h"
#include "models.h"




/*
    init
*/

void init(void)
{
  sdl_init();
  gl_init();
  gl_textures_init();
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

  uint32_t time_diff;
  float move_scale = 0.2, accel_scale = 1;

  GLfloat earth_angle = 0;

  GLfloat lander_x_pos = 0;
  GLfloat lander_y_pos = -4;
  GLfloat lander_z_pos = -50;
  GLfloat lander_x_pos_rate = 0;
  GLfloat lander_y_pos_rate = 0;
  GLfloat lander_z_pos_rate = 0;

  GLfloat light_position[4];
  GLfloat light_ambient[4];
  GLfloat light_diffuse[4];

  GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  time_reset();

  for(;;)
  {
    time_diff = get_rel_time();

    if(getkey(SDL_SCANCODE_A)) lander_x_pos_rate -= .0001 * time_diff * accel_scale;
    else if(getkey(SDL_SCANCODE_D)) lander_x_pos_rate += .0001 * time_diff * accel_scale;
    else if(lander_x_pos_rate > 0.0001) lander_x_pos_rate -= .00003 * time_diff * accel_scale;
    else if(lander_x_pos_rate < -0.0001) lander_x_pos_rate += .00003 * time_diff * accel_scale;
    lander_x_pos += lander_x_pos_rate * time_diff * move_scale;


    if(getkey(SDL_SCANCODE_W)) lander_z_pos_rate -= .0001 * time_diff * accel_scale;
    else if(getkey(SDL_SCANCODE_S)) lander_z_pos_rate += .0001 * time_diff * accel_scale;
    else if(lander_z_pos_rate > 0.0001) lander_z_pos_rate -= .00003 * time_diff * accel_scale;
    else if(lander_z_pos_rate < -0.0001) lander_z_pos_rate += .00003 * time_diff * accel_scale;
    lander_z_pos += lander_z_pos_rate * time_diff * move_scale;


    if(getkey(SDL_SCANCODE_UP)) lander_y_pos_rate += .0001 * time_diff * accel_scale;
    else if(getkey(SDL_SCANCODE_DOWN)) lander_y_pos_rate -= .0001 * time_diff * accel_scale;
    else if(lander_y_pos_rate > 0.0001) lander_y_pos_rate -= .00003 * time_diff * accel_scale;
    else if(lander_y_pos_rate < -0.0001) lander_y_pos_rate += .00003 * time_diff * accel_scale;
    lander_y_pos += lander_y_pos_rate * time_diff * move_scale;


    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHT0);

    earth_angle += 0.01;  if(earth_angle > 360) earth_angle = 0;

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
    glRotatef(-45, 0.0, 0.0, 1.0);
    glScalef(0.2, 0.2, 0.16);
    draw_lander();
    glPopMatrix(); // restore camera

    glFlush();
    SDL_GL_SwapWindow(main_window);

    if(getkey(SDL_SCANCODE_ESCAPE)) quit();
    if(update_events() == -1) break;
  }
  
  cleanup();
  return(EXIT_SUCCESS);
}

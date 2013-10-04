#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include <GL/gl.h>


float move_scale;
float accel_scale;

GLfloat earth_angle;

GLfloat lander_x_pos;
GLfloat lander_y_pos;
GLfloat lander_z_pos;
GLfloat lander_y_angle;

GLfloat lander_x_pos_rate;
GLfloat lander_z_pos_rate;
GLfloat lander_y_pos_rate;

GLfloat lander_y_angle_rate;




void game_data_init(void);




#endif

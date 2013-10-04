#include <math.h>
#include <GL/gl.h>
#include "sdl.h"
#include "game_data.h"




static uint32_t time_diff;

/*
    game logic tick
*/

void game_logic_tick(void)
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

  if(getkey(SDL_SCANCODE_LEFT)) lander_y_angle_rate += .0005 * time_diff * accel_scale;
  else if(getkey(SDL_SCANCODE_RIGHT)) lander_y_angle_rate -= .0005 * time_diff * accel_scale;
  else if(lander_y_angle_rate > 0.0001) lander_y_angle_rate -= .0001 * time_diff * accel_scale;
  else if(lander_y_angle_rate < -0.0001) lander_y_angle_rate += .0001 * time_diff * accel_scale;
  lander_y_angle += lander_y_angle_rate * time_diff * move_scale;

  earth_angle += 0.01;  if(earth_angle > 360) earth_angle = 0;

  if(getkey(SDL_SCANCODE_ESCAPE)) quit();
}


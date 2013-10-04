#include "game_data.h"

/*
    game data init
*/

void game_data_init(void)
{
  move_scale = 0.2;
  accel_scale = 1;
  lander_y_pos_rate = 0;
  lander_y_angle_rate = 0;

  earth_angle = 0;

  lander_x_pos = 0;
  lander_y_pos = -4;
  lander_z_pos = -50;
  lander_y_angle = 0;

  lander_x_pos_rate = 0;
  lander_z_pos_rate = 0;
}


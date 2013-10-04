#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "opengl.h"
#include "sdl.h"
#include "game_data.h"
#include "logic.h"
#include "scene.h"
#include "textures.h"




/*
    init
*/

void init(void)
{
  sdl_init();
  gl_init();
  gl_textures_init();
  game_data_init();
  time_reset();
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

  for(;;)
  {
    game_logic_tick();
    render_scene();

    if(update_events() == -1) break;
  }
  
  cleanup();
  return(EXIT_SUCCESS);
}

/*
    texture management
*/

#include "textures.h"
#include "opengl.h"




/*
    gl_textures_init
*/
void gl_textures_init(void)
{
  lander = create_gl_texture("textures/lander.jpg");
  terrain = create_gl_texture("textures/terrain-03.jpg");
  earth = create_gl_texture("textures/earth.jpg");
}





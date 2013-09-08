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
  crate_01 = create_gl_texture("textures/crate_01.jpg");
  crate_02 = create_gl_texture("textures/crate_02.jpg");
  crate_03 = create_gl_texture("textures/crate_03.jpg");
  crate_04 = create_gl_texture("textures/crate_04.jpg");
}





#include <GL/glu.h>
#include "textures.h"




  static GLfloat vertex[] =
  {
    -1, -1, 1,    1, -1, 1,    1, 1, 1,    -1, 1, 1,
    1, -1, 1,    1, -1, -1,    1, 1, -1,    1, 1, 1,
    -1, -1, -1,    -1, 1, -1,    1, 1, -1,    1, -1, -1,
    -1, -1, -1,    -1, -1, 1,    -1, 1, 1,    -1, 1, -1,
    -1, 1, 1,    1, 1, 1,    1, 1, -1,    -1, 1, -1,
    -1, -1, 1,    -1, -1, -1,    1, -1, -1,    1, -1, 1
  };

  static GLfloat texcoord_01[] =
  {
    0, 1,   1, 1,   1, 0,   0, 0,
    0, 1,   1, 1,   1, 0,   0, 0,
    0, 1,   1, 1,   1, 0,   0, 0,
    0, 1,   1, 1,   1, 0,   0, 0,
    0, 1,   1, 1,   1, 0,   0, 0,
    0, 1,   1, 1,   1, 0,   0, 0   
  };

  static GLfloat texcoord_02[] =
  {
    0, 0.5,   0.5, 0.5,   0.5, 1,   0, 1,
    0, 0,    0.5, 0,   0.5, 0.5,   0, 0.5,
    0.5, 0,   1, 0,   1, 0.5,   0.5, 0.5,
    0, 0,   0.5, 0,   0.5, 0.5,   0, 0.5,
    0.5, 0.5,   1, 0.5,   1, 1,   0.5, 1,
    0.5, 0.5,   1, 0.5,   1, 1,   0.5, 1   
  };

  static GLint polystart[] = {0, 4, 8, 12, 16, 20};
  static GLint polylength[] = {4, 4, 4, 4, 4, 4};


/*
    crate
*/

void draw_crate_01(void)
{
  glBindTexture(GL_TEXTURE_2D, crate_01);
  glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 3, vertex);
  glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 2, texcoord_01);
  glMultiDrawArrays(GL_TRIANGLE_FAN, polystart, polylength, 6);
}




void draw_crate_02(void)
{
  glBindTexture(GL_TEXTURE_2D, crate_02);
  glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 3, vertex);
  glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 2, texcoord_01);
  glMultiDrawArrays(GL_TRIANGLE_FAN, polystart, polylength, 6);
}




void draw_crate_03(void)
{
  glBindTexture(GL_TEXTURE_2D, crate_03);
  glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 3, vertex);
  glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 2, texcoord_02);
  glMultiDrawArrays(GL_TRIANGLE_FAN, polystart, polylength, 6);
}




void draw_crate_04(void)
{
  glBindTexture(GL_TEXTURE_2D, crate_04);
  glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * 3, vertex);
  glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * 2, texcoord_02);
  glMultiDrawArrays(GL_TRIANGLE_FAN, polystart, polylength, 6);
}






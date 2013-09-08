#include <GL/glu.h>
#include "textures.h"




/*
    vertex
*/

typedef struct
{
  float coordinate[3];     // world coordinates in the form {x,y,z)
  float texCoordinate[2];  // texture coordinates in the form {u,v}
  //float lmapCoordinate[2]; // lightmap coordinates in the form {u,v}
  //float normal[3];         // point's normal in the form {x,y,z}
} vertex_t;





/*
    polygon
*/

typedef struct
 {
  int startVertex;     // starting vertex's indice in 'vertex' array
  int numOfVertices;   // number of subsequent polygons
  int texture;         // texture's name index in 'textureName' array
//  int lightmap;        // lightmap's name index in 'lightMapName' array
 } polygon_t;




/*
    crate
*/

void draw_crate_01(void)
{
  int i, j;

  glBindTexture(GL_TEXTURE_2D, crate_01);

  GLfloat vertex[] = /* tex x, tex y, vert x, vert y, vert z (step 5) */
  {
    0, 1, -1, -1, 1,   1, 1, 1, -1, 1,   1, 0, 1, 1, 1,   0, 0, -1, 1, 1,
    0, 1, 1, -1, 1,   1, 1, 1, -1, -1,   1, 0, 1, 1, -1,   0, 0, 1, 1, 1,
    0, 1, -1, -1, -1,   1, 1, -1, 1, -1,   1, 0, 1, 1, -1,   0, 0, 1, -1, -1,
    0, 1, -1, -1, -1,   1, 1, -1, -1, 1,   1, 0, -1, 1, 1,   0, 0, -1, 1, -1,
    0, 1, -1, 1, 1,   1, 1, 1, 1, 1,   1, 0, 1, 1, -1,   0, 0, -1, 1, -1,
    0, 1, -1, -1, 1,   1, 1, -1, -1, -1,   1, 0, 1, -1, -1,   0, 0, 1, -1, 1
  };

  for(i=0; i<120; i+=20)
  {
    glBegin(GL_POLYGON);
    for(j=0; j<20; j+=5)
    {
      glTexCoord2f(vertex[i+j], vertex[i+j+1]);
      glVertex3f(vertex[i+j+2], vertex[i+j+3], vertex[i+j+4]);
    }
    glEnd();
  }
}




void draw_crate_02(void)
{
  int i, j;

  glBindTexture(GL_TEXTURE_2D, crate_02);

  GLfloat vertex[] = /* tex x, tex y, vert x, vert y, vert z (step 5) */
  {
    0, 1, -1, -1, 1,   1, 1, 1, -1, 1,   1, 0, 1, 1, 1,   0, 0, -1, 1, 1,
    0, 1, 1, -1, 1,   1, 1, 1, -1, -1,   1, 0, 1, 1, -1,   0, 0, 1, 1, 1,
    0, 1, -1, -1, -1,   1, 1, -1, 1, -1,   1, 0, 1, 1, -1,   0, 0, 1, -1, -1,
    0, 1, -1, -1, -1,   1, 1, -1, -1, 1,   1, 0, -1, 1, 1,   0, 0, -1, 1, -1,
    0, 1, -1, 1, 1,   1, 1, 1, 1, 1,   1, 0, 1, 1, -1,   0, 0, -1, 1, -1,
    0, 1, -1, -1, 1,   1, 1, -1, -1, -1,   1, 0, 1, -1, -1,   0, 0, 1, -1, 1
  };

  for(i=0; i<120; i+=20)
  {
    glBegin(GL_POLYGON);
    for(j=0; j<20; j+=5)
    {
      glTexCoord2f(vertex[i+j], vertex[i+j+1]);
      glVertex3f(vertex[i+j+2], vertex[i+j+3], vertex[i+j+4]);
    }
    glEnd();
  }
}




void draw_crate_03(void)
{
  int i, j;

  glBindTexture(GL_TEXTURE_2D, crate_03);

  GLfloat vertex[] = /* tex x, tex y, vert x, vert y, vert z (step 5) */
  {
    0, 0.5, -1, -1, 1,   0.5, 0.5, 1, -1, 1,   0.5, 1, 1, 1, 1,   0, 1, -1, 1, 1,
    0, 0, 1, -1, 1,   0.5, 0, 1, -1, -1,   0.5, 0.5, 1, 1, -1,   0, 0.5, 1, 1, 1,
    0.5, 0, -1, -1, -1,   1, 0, -1, 1, -1,   1, 0.5, 1, 1, -1,   0.5, 0.5, 1, -1, -1,
    0, 0, -1, -1, -1,   0.5, 0, -1, -1, 1,   0.5, 0.5, -1, 1, 1,   0, 0.5, -1, 1, -1,
    0.5, 0.5, -1, 1, 1,   1, 0.5, 1, 1, 1,   1, 1, 1, 1, -1,   0.5, 1, -1, 1, -1,
    0.5, 0.5, -1, -1, 1,   1, 0.5, -1, -1, -1,   1, 1, 1, -1, -1,   0.5, 1, 1, -1, 1
  };

  for(i=0; i<120; i+=20)
  {
    glBegin(GL_POLYGON);
    for(j=0; j<20; j+=5)
    {
      glTexCoord2f(vertex[i+j], vertex[i+j+1]);
      glVertex3f(vertex[i+j+2], vertex[i+j+3], vertex[i+j+4]);
    }
    glEnd();
  }
}




void draw_crate_04(void)
{
  int i, j;

  glBindTexture(GL_TEXTURE_2D, crate_04);

  GLfloat vertex[] = /* tex x, tex y, vert x, vert y, vert z (step 5) */
  {
    0, 0.5, -1, -1, 1,   0.5, 0.5, 1, -1, 1,   0.5, 1, 1, 1, 1,   0, 1, -1, 1, 1,
    0, 0, 1, -1, 1,   0.5, 0, 1, -1, -1,   0.5, 0.5, 1, 1, -1,   0, 0.5, 1, 1, 1,
    0.5, 0, -1, -1, -1,   1, 0, -1, 1, -1,   1, 0.5, 1, 1, -1,   0.5, 0.5, 1, -1, -1,
    0, 0, -1, -1, -1,   0.5, 0, -1, -1, 1,   0.5, 0.5, -1, 1, 1,   0, 0.5, -1, 1, -1,
    0.5, 0.5, -1, 1, 1,   1, 0.5, 1, 1, 1,   1, 1, 1, 1, -1,   0.5, 1, -1, 1, -1,
    0.5, 0.5, -1, -1, 1,   1, 0.5, -1, -1, -1,   1, 1, 1, -1, -1,   0.5, 1, 1, -1, 1
  };

  for(i=0; i<120; i+=20)
  {
    glBegin(GL_POLYGON);
    for(j=0; j<20; j+=5)
    {
      glTexCoord2f(vertex[i+j], vertex[i+j+1]);
      glVertex3f(vertex[i+j+2], vertex[i+j+3], vertex[i+j+4]);
    }
    glEnd();
  }
}






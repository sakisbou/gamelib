#include <IL/il.h>
#include <GL/glu.h>


#include "options.h"
#include "sdl.h"



/*
    gl init
*/

void gl_init(void)
{
  ilInit();

  float fogColor[]={0.1,0.1,0.1,1};

  // set up perpective
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOV,(GLfloat)RESX/(GLfloat)RESY,1,16384);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  // set up shade model
  glShadeModel(GL_SMOOTH);

  // set up depth buffer
  glClearDepth(1.0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

  // set up face culling
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  
  // set up vertex arrays
  glEnableClientState(GL_VERTEX_ARRAY);
//  glVertexPointer(3,GL_FLOAT,sizeof(vertex_t),vertex[0].coordinate);
//  glClientActiveTextureARB(GL_TEXTURE0_ARB); 
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//  glTexCoordPointer(2,GL_FLOAT,sizeof(vertex_t),vertex[0].texCoordinate);
//  glClientActiveTextureARB(GL_TEXTURE1_ARB); 
//  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//  glTexCoordPointer(2 ,GL_FLOAT,sizeof(vertex_t),vertex[0].lmapCoordinate);
 

  // set up texturing
  // glActiveTextureARB(GL_TEXTURE0_ARB);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  // glActiveTextureARB(GL_TEXTURE1_ARB);
  // glEnable(GL_TEXTURE_2D);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

  // set up fog
  glFogi(GL_FOG_MODE,GL_EXP2);
  glFogfv(GL_FOG_COLOR,fogColor);
  glFogf(GL_FOG_DENSITY,0.001);
  glHint(GL_FOG_HINT,GL_NICEST);
  if(FOG) glEnable(GL_FOG);

  // reset cammera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // clear and update frame buffer
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
  glFlush();
  SDL_GL_SwapWindow(main_window);
}




/*
    create_gl_texture
*/

GLuint create_gl_texture(char *image_filename)
{
  ILuint image_name;
  ILuint width, height;

  ilGenImages(1, &image_name);
  ilBindImage(image_name);
  ilLoadImage(image_filename);

  width = ilGetInteger(IL_IMAGE_WIDTH);
  height = ilGetInteger(IL_IMAGE_HEIGHT);

  ILubyte *img = ilGetData();

  GLuint texture_name;

  // get a texture name for the texture to be created
  glGenTextures(1, &texture_name);

  // opengl stuff neccessary to create the texture
  glBindTexture(GL_TEXTURE_2D,texture_name);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);

  ilDeleteImages(1, &image_name); 

  // return the texture name
  return(texture_name);
}


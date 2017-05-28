#pragma once
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gl\glut.h>
#include "arg.h"

#if defined(GL_VERSION_1_1)
#define TEXTURE_OBJECT 1
#elif defined(GL_EXT_texture_object)
#define TEXTURE_OBJECT 1
#define glBindTexture(A,B)     glBindTextureEXT(A,B)
#define glGenTextures(A,B)     glGenTexturesEXT(A,B)
#define glDeleteTextures(A,B)  glDeleteTexturesEXT(A,B)
#endif

static GLuint TexObj[31];
static GLfloat Angle = 0.0f;;
static GLboolean HaveTexObj = GL_FALSE;

//////////////////////////////////////////////

//unsigned WINAPI Thread(void *pvoid);
//void createCList(char *mode, vector<Card> &, int);
//void specialKeys(int key, int x, int y);

static void draw(void);
static void idle(void);
static void key(unsigned char k, int x, int y);
static void reshape(int width, int height);
static void init(void);
void visible(int vis);
int output(iArg *);

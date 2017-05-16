#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <GLFW/glfw3.h>

void loadBmpFile(char* fileName, GLuint* tObj);
GLuint createTileBuffer(int, int, int, int);
GLuint createPlayerTrollBuffer(int, int, int);
GLuint createShaderProgram(void);
GLuint createShaderProgram2(void);
GLuint createBgShaderProgram(void);
GLuint createPlayerShaderProgram(void);

#endif

#include <windows.h>

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include<iostream>
#define TEXSIZE 4

GLubyte bits[TEXSIZE][TEXSIZE][4];
GLfloat data[TEXSIZE][TEXSIZE][4];
GLuint texName;

void disp(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindTexture(GL_TEXTURE_2D, texName);

  glRotated(2, 1, 1, 0.25);

  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0); glVertex2f(-0.9, -0.9);
  glTexCoord2f(0, 1); glVertex2f(-0.9, 0.9);
  glTexCoord2f(1, 1); glVertex2f(0.9, 0.9);
  glTexCoord2f(1, 0); glVertex2f(0.9, -0.9);
  glEnd();
  glFlush();
}

void timer(int value) {
  glRotatef(1, 0.5, 1, 0.25);
  glutPostRedisplay();
  glutTimerFunc(50, timer, 0);
}

int main(int argc, char ** argv) {
  unsigned int i, j;

  for (i = 0; i < TEXSIZE; i++) {
    int r = (i * 0xFF) / TEXSIZE;
    for (j = 0; j < TEXSIZE; j++) {
      bits[i][j][0] = r;
      bits[i][j][1] = 0;
      bits[i][j][2] = 0;
      bits[i][j][4] = 255;

      data[i][j][0] = 1.0f;
      data[i][j][1] = 0.5f;
      data[i][j][2] = 1.0f;
      data[i][j][4] = 1.0f;
    }
  }

  glutInit(&argc, argv);
  glutInitWindowSize(400, 300);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

  glutCreateWindow("Kitty on your lap");
  glutDisplayFunc(disp);
  glutTimerFunc(100, timer, 0);

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &texName);
  glBindTexture(GL_TEXTURE_2D, texName);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA32F, TEXSIZE, TEXSIZE,
      0, GL_RGBA, GL_FLOAT, data);


  /*glTexImage2D(
   *    GL_TEXTURE_2D, 0, 3, TEXSIZE, TEXSIZE,
   *        0, GL_RGB, GL_UNSIGNED_BYTE, bits
   *          );*/

  glutMainLoop();

  glDeleteTextures(1, &texName);
  return 0;
}

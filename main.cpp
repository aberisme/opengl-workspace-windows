#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);


    glVertex2f(0.0f, 0.7f);

    glVertex2f(-0.3f, 0.3f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.5f, -0.2f);

    glVertex2f(0.5f, -0.2f);
    glVertex2f(0.1f, 0.3f);
    glVertex2f(0.3f, 0.3f);

    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
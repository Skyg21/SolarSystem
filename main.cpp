//
//  main.cpp
//  FinalProjectCG_Sky
//
//  Created by Sky Gourley on 12/13/18.
//  Copyright © 2018 Sky Gourley. All rights reserved.
#include <GLUT/GLUT.h>

#define sunRaduis 0.4
#define earthRaduis 0.06
#define moonRaduis 0.016

void drawSolarSystem(void);
void Initialization(void);
void displayFunc(void);
void reshapeFunc(int x, int y);
void idleFunc(void);
void resetScene();
void enableLights();
void reshape(GLsizei width, GLsizei height);
void keyboardClick(unsigned char key, int x, int y);     // unsigned bc dont want negative values
void mouseClick(int button,int state, int x, int y);    // x&y = where mouse is clicked on window
void mouseMotion(int x, int y);


GLfloat rotationSpeed = 0.1;
GLfloat daysInYear = 365;
GLfloat year = 0.0; //degrees
GLfloat day = 0.0;
GLfloat moonAroundEarth = 0.0;
GLfloat moonItsSelf = 0.0;
GLfloat earthOrbitRadius = 1.0;
GLfloat moonOrbitRadius = 0.1;
GLfloat moonAroundEarthRate = 4 * rotationSpeed;
GLfloat moonRotationItselfRate = 5.0 * rotationSpeed;
GLfloat dayRate = 5.0 * rotationSpeed;
GLfloat yearRate = daysInYear / 360.0 * dayRate * rotationSpeed;

int main(int argc, char* argv[])


{
    
    // Initialization for glut
    glutInit(&argc, argv);
    // set the buffer mode ( double and colors (RGB)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // set the window frame size
    glutInitWindowSize(700,700);
    glutCreateWindow("Solar system");
    Initialization();
    // reshape call back function reference setting.
    glutReshapeFunc(reshapeFunc);
    // display call back function reference setting
    glutDisplayFunc(displayFunc);
    //  idle callback function reference setting ( used in animation )
    glutIdleFunc(idleFunc);
    // enters the GLUT event processing loop
    glutMainLoop();
    return 0;
}
void drawSolarSystem(void)
{
    
    glPushMatrix();
    gluLookAt(    0.0,0.0,-4.0,   //creates a viewing matrix derived from an eye point, a reference point
              0.0,0.0,1.0,           //center of the scene, and an UP vector
              0.0,-3.0,0.0);
    glColor3f(1.0,0.8,0.3);          // Color of the sun.
    glutSolidSphere(sunRaduis,50,50); // Drawing the sun.
    glPushMatrix();
    
    glRotatef(year,0.0,1.0,0.0); //rotation for earth
    glTranslatef(earthOrbitRadius,0.0,0.0); // translation for earth.
    glRotatef(-year,0.0,1.0,0.0);
    glPushMatrix();
    glRotatef(day,0.25,1.0,0.0);
    glColor3f(0.4,0.6,0.3);
    //Drawing the earth
    glutSolidSphere(earthRaduis,10,10);
    glPopMatrix();
    
    glRotatef(moonAroundEarth,0.0,1.0,0.0); // rotation for moon.
    glTranslatef(moonOrbitRadius,0.0,0.0);  // translation for moon.
    glRotatef(-moonAroundEarth,0.0,1.0,0.0);  // around earth rotation.
    glRotatef(moonItsSelf,0.0,1.0,0.0);
    glColor3f(0.3,0.3,0.5);
    glutSolidSphere(moonRaduis,8,8);      // draw the moon
    glPopMatrix();
    
    glPopMatrix();
}

void Initialization(void)
{
    // background color
    glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(10.0);
    
    
    // GL_MODELVIEW :Applies subsequent matrix operations to the modelview matrix stack.
    /*
     The modelview matrix is for transformation of geometry from model to view space
     (therefore the camera/view transform most correctly goes in the modelview matrix).
     */
    glMatrixMode(GL_MODELVIEW);
    // replace the current matrix with the identity matrix
    glLoadIdentity();
}

void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSolarSystem();
    // flush to screen.
    glFlush();
    // swap buffers , yes we need this ( double buffering used!)
    glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x==0) return;
    
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
    displayFunc();
}

void idleFunc(void)
{
    // idle event call back in animation , here we increase the values and redisply .
    day += dayRate;
    year += yearRate;
    moonItsSelf += moonRotationItselfRate;
    moonAroundEarth += moonAroundEarthRate;
    displayFunc();
}

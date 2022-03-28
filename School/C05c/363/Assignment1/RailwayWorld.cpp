//  ========================================================================
//  COSC363: Computer Graphics (2022);  University of Canterbury.
//
//  FILE NAME: RailwayWorld.cpp
//  See Lab02.pdf for details
//  ========================================================================

#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include "RailModels.h"
#include "assignmentfuncs.h"
using namespace std;

std::vector<std::pair<float, float>> line_array = {};
float theta = 0;

// camara postions
float lookrot = 0;
float camx = 100;
float camy = 100;
float camz = 100;
float lookx = 0;
float looky = 0;
float lookz = 0;

float w1 = 3;
float w2 = 4;
float track_height = 2;

GLuint txId[2];


//---------------------------------------------------------------------
void initialize(void)
{
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

//  Define light's ambient, diffuse, specular properties
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

//  Spotlight
    //glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    //glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    //glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor (0.0, 0.0, 0.0, 0.0);  //Background colour

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60., 1.0, 10.0, 1000.0);   //Perspective projection
}

//-------------------------------------------------------------------
void display(void)
{
   float lgt_pos[] = {0.0f, 50.0f, 0.0f, 1.0f};  //light0 position (directly above the origin)
   //float spotlgt_pos[] = {-10, 14, 0, 1};
   //float spotlgt_dir[] = {-1, -1, 0};


   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt (camx,camy,camz, lookx,looky,lookz, 0.0, 1.0, 0.0);
   glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);   //light position

   //speen
   glRotatef(theta, 0, 1, 0);

   floor(txId);
   track_loop(line_array, w1, w2, track_height);
   sleepers(line_array, w1*2, w1*2/5, track_height/2);
   rail_bed(line_array, 10, w2*2, track_height/4, txId);

    //int num_wagons = 4;

    //wagons
    //for (int i = num_wagons; i > 0; i--) {
    //  glPushMatrix();
    //        glRotatef(-10.5 * i, 0, 1, 0);
    //        glTranslatef(0, 1, -120);
    //        wagon();
    //    glPopMatrix();
    //}

    //locomotive
   //glPushMatrix();
   //     glTranslatef(0, 1, -120);
    //    glLightfv(GL_LIGHT1, GL_POSITION, spotlgt_pos); //spot postion
    //    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlgt_dir); //spot direction
    //    engine();
   //glPopMatrix();


   glutSwapBuffers();   //Useful for animation
}


void train_rotate_timer(int value)
{
    theta = theta + 0.5;
    glutPostRedisplay();
    glutTimerFunc(25, train_rotate_timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'w':
            camy --;
            break;
        case 's':
            camy ++;
            break;
        case 'd':
            theta++;
            break;
        case 'a':
            theta--;
            break;
    }
    glutPostRedisplay();
}


void special(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_UP:
            lookx++;
            camx++;
            break;
        case GLUT_KEY_DOWN:
            lookx--;
            camx--;
            break;
        case GLUT_KEY_LEFT:
            lookz++;
            camz++;
            break;
        case GLUT_KEY_RIGHT:
            lookz--;
            camz--;
            break;
    }
    glutPostRedisplay();
}

//---------------------------------------------------------------------
int main(int argc, char** argv)
{
    //Load median line
    ifstream medline_file("mediumline.txt");
    parseMedianlineFile(medline_file, line_array);
    //for (std::pair<float, float>point : line_array) {
    //    cout << point.first << "," << point.second << endl;
    //}

    glGenTextures(2, txId);

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH);
   glutInitWindowSize (1024, 1024);
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("Cum Express");
   initialize ();

   glutDisplayFunc(display);
   //glutTimerFunc(25, train_rotate_timer, 0);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}

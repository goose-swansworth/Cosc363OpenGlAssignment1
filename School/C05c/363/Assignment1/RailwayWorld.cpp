//  ========================================================================
//  COSC363: Computer Graphics (2022);  University of Canterbury.
//
//  FILE NAME: RailwayWorld.cpp
//  See Lab02.pdf for details
//  ========================================================================

#include <GL/gl.h>
#include <cmath>
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "RailModels.h"
#include "assignmentfuncs.h"
#include "skybox.h"

using namespace std;

#define TO_DEGREES 180 / M_PI

GLuint txId[6]; 

std::vector<std::pair<float, float>> line_array = {};
float theta = 0;

// camara postions
float lookrot = 0;
float camx = 50;
float camy = 50;
float camz = 50;
float lookx = 0;
float looky = 0;
float lookz = 0;

float trainx = 0;
float trainy = 0;
float trainz = 0;


float rail_in = 2;
float rail_out = 2.75;
float track_height = 1;

int icurr = 0;
GLuint txID[2];

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
    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
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
   //float lgt1_pos[] = {50.f, 50.0f, 50.0f, 1.0f};
   //float spotlgt_pos[] = {-10, 14, 0, 1};
   //float spotlgt_dir[] = {-1, -1, 0};


   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt (camx,camy,camz, lookx,looky,lookz, 0.0, 1.0, 0.0);

   //speen
   glRotatef(theta, 0, 1, 0);

   floor(txId);
   track_loop(line_array, rail_in, rail_out, track_height);
   sleepers(line_array, rail_in*2, rail_in*2/5, track_height/2, 3);
   rail_bed(line_array, 10, rail_out*2, track_height/4, txId);

   glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
   skybox(txId);

   //glLightfv(GL_LIGHT1, GL_POSITION, spotlgt_pos); //spot postion
   //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlgt_dir); //spot direction

   float base_len = 12;
   std::pair<float, float> pi;
   std::pair<float, float> pi_p1;
   std::pair<float, float> ui;
   int m = 13;
   int n_points = line_array.size();
   //postion models on track
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
            pi = line_array[(icurr + i*m) % n_points];
            pi_p1 = line_array[((icurr + i*m) + 1) % n_points];
            ui = vec_in_dir(pi, pi_p1);
            normalize_2d_vec(ui);
            glTranslatef(pi.first, track_height, pi.second);
            glRotatef(atan2(ui.second, -ui.first)*TO_DEGREES, 0, 1, 0);
            switch (i) {
                case 3:
                    glRotatef(180, 0, 1, 0);
                    lookx = pi.first;
                    looky = track_height;
                    lookz = pi.second;
                    freight_engine(rail_in, rail_out, track_height, base_len, 1, 0.5);
                    break;
                case 2:
                    boxcar(rail_in, rail_out, track_height, base_len, 1, 0.5);
                    break;
                case 1:
                    log_car(rail_in, rail_out, track_height, base_len, 1, 0.5);
                    break;
                case 0:
                    tanker(rail_in, rail_out, track_height, base_len, 1, 0.5);
                    break;
            }
        glPopMatrix();
    }
    glutSwapBuffers();
}


void train_move_timer(int value)
{
    icurr++;
    icurr = icurr % line_array.size();
    glutPostRedisplay();
    glutTimerFunc(50, train_move_timer, 0);
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
        case 'i':
            icurr++;
            break;
        case ' ':
            camy++;
            break;
        case '2':
            camx = 100;
            camy = 100;
            camz = 100;
            break;
        case '1':
            camx = 50;
            camy = 50;
            camz = 50;
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

    glGenTextures(2, txId);

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize (1024, 1024);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("Cum Express");
    initialize ();

    glutDisplayFunc(display);
    glutTimerFunc(50, train_move_timer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}

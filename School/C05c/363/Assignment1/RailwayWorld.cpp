#include "RailModels.h"
#include "assignmentfuncs.h"
#include "skybox.h"
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/gl.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <utility>
#include <vector>
#include "textures.h"

#define TO_DEGREES 180 / M_PI

using namespace std;

GLuint texture_ids[12];

vector<pair<float, float>> line_array = {};

// camara postions and constants
float camx = 0;
float camy = 12;
float camz = 0;
float lookx = 0;
float looky = 8;
float lookz = 1;
float cam_step = 0.025;
float look_angle = 0;
bool follow_train = false;

// constants for models
float rail_in = 2;
float rail_out = 2.75;
float track_height = 1;
float base_len = 12;

// track index
int icurr = 0;

//---------------------------------------------------------------------
void initialize(void) {
  float grey[4] = {0.2, 0.2, 0.2, 1.0};
  float white[4] = {1.0, 1.0, 1.0, 1.0};

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
  // glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
  // glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);

  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glMaterialfv(GL_FRONT, GL_SPECULAR, white);
  glMaterialf(GL_FRONT, GL_SHININESS, 50);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glClearColor(0.0, 0.0, 0.0, 0.0); // Background colour

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75., 1.0, 10.0, 1000.0); // Perspective projection

  load_textures(texture_ids);
}


void draw_train() 
{
  std::pair<float, float> pi;
  std::pair<float, float> pi_p1;
  std::pair<float, float> ui;
  int m = 13;
  int n_points = line_array.size();
  // postion models on track
  for (int i = 0; i < 4; i++) {
    glPushMatrix();
    pi = line_array[(icurr + i * m) % n_points];
    pi_p1 = line_array[((icurr + i * m) + 1) % n_points];
    ui = vec_in_dir(pi, pi_p1);
    normalize_2d_vec(ui);
    glTranslatef(pi.first, track_height, pi.second);
    glRotatef(atan2(ui.second, -ui.first) * TO_DEGREES, 0, 1, 0);
    switch (i) {
    case 3:
      glRotatef(180, 0, 1, 0);
      if (follow_train) {
          lookx = pi.first;
          looky = track_height;
          lookz = pi.second;
      }
      freight_engine(rail_in, rail_out, track_height, base_len, 1, 0.5);
      break;
    case 2:
      boxcar(rail_in, rail_out, track_height, base_len, 1, 0.5, texture_ids);
      break;
    case 1:
      log_car(rail_in, rail_out, track_height, base_len, 1, 0.5, texture_ids);
      break;
    case 0:
      tanker(rail_in, rail_out, track_height, base_len, 1, 0.5, texture_ids);
      break;
    }
    glPopMatrix();
  }
}


//-------------------------------------------------------------------
void display(void) {
  float lgt_pos[] = {0.0f, 50.0f, 0.0f,
                     1.0f}; // light0 position (directly above the origin)
  // float lgt1_pos[] = {50.f, 50.0f, 50.0f, 1.0f};
  // float spotlgt_pos[] = {-10, 14, 0, 1};
  // float spotlgt_dir[] = {-1, -1, 0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camx, camy, camz, lookx, looky, lookz, 0.0, 1.0, 0.0);

  floor(texture_ids);
  glPushMatrix();
    glTranslatef(0, -100, 0);
    skybox(texture_ids);
  glPopMatrix();
  track_loop(line_array, rail_in, rail_out, track_height);
  sleepers(line_array, rail_in * 2, rail_in * 2 / 5, track_height / 2, 3);
  rail_bed(line_array, 10, rail_out * 2, track_height / 4, texture_ids);

  glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);

  draw_train();
  
  // positon tunnel
  glPushMatrix();
    glTranslatef(105, 0, -33.5);
    glScalef(10, 10, 10);
    tunnel(1.75, 8, 1.75, 30, texture_ids);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(108.5, -1, -33.5);
    glScalef(9, 9, 9);
    tunnel_straight(1.75, 8, 1.75, 30, texture_ids);
  glPopMatrix();
  station(base_len, 2);
  glutSwapBuffers();
}

void train_move_timer(int value) {
  icurr++;
  icurr = icurr % line_array.size();
  glutPostRedisplay();
  glutTimerFunc(50, train_move_timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
        camx = camx + cam_step*(lookx - camx);
        camz = camz + cam_step*(lookz - camz);
        break;
    case 's':
        camx = camx - cam_step*(lookx - camx);
        camz = camz - cam_step*(lookz - camz);
        break;
    case 'd':
        look_angle += 0.1;
        break;
    case 'a':
        look_angle -= 0.1;
        break;
    case 'i':
        icurr++;
        break;
    case 'f':
        follow_train = !follow_train;
        break;
    case ' ':
        camy++;
        looky++;
        break;
    case '3':
        camx = 200;
        camy = 200;
        camz = 200;
        break;
    case '2':
        camx = 100;
        camy = 100;
        camz = 100;
        break;
    case '1':
        camx = 0;
        camy = 25;
        camz = 25;
        lookx = 0;
        looky = 0;
        lookz = 0;
        break;
    case 'r': // reset
        look_angle = 0;
        camx = 0;
        camy = 8;
        camz = 0;
        lookx = 0;
        looky = 8;
        lookz = 0;
        break;
  }
  lookx = camx + 100*sin(look_angle);
  lookz = camz - 100*cos(look_angle);
  glutPostRedisplay();
}

void special(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_SHIFT_L:
      camy --;
      looky --;
      break;
  }
  glutPostRedisplay();
}


//---------------------------------------------------------------------
int main(int argc, char **argv) {
  // Load median line
  ifstream medline_file("mediumline.txt");
  parseMedianlineFile(medline_file, line_array);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(1024, 1024);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Yoy Express");
  initialize();

  glutDisplayFunc(display);
  glutTimerFunc(50, train_move_timer, 0);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMainLoop();
  return 0;
}

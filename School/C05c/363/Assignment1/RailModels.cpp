//  ========================================================================
//  COSC363: Computer Graphics (2022);  University of Canterbury.
//
//  RailModels.cpp
//  A collection of functions for generating the models for a railway scene
//  ==========================================================================

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include "GL/freeglut.h"
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "RailModels.h"
#include "assignmentfuncs.h"
using namespace std;



float white[4] = {1., 1., 1., 1.};
float black[4] = {0};
//--------------- GROUND PLANE ------------------------------------
// This is a square shaped region on the xz-plane of size 400x400 units
// centered at the origin.  This region is constructed using small quads
// of unit size, to facilitate rendering of spotlights
//-----------------------------------------------------------------



void floor(GLuint txId[])
{
    load_floor_texture(txId);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glNormal3f(0.0, 1.0, 0.0);

    // big ass quad for floor
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-400, 0, -400);

        glTexCoord2f(4, 0);
        glVertex3f(400, 0, -400);

        glTexCoord2f(4, 4);
        glVertex3f(400, 0, 400);

        glTexCoord2f(0, 4);
        glVertex3f(-400, 0, 400);
    glEnd();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glDisable(GL_TEXTURE_2D);

}


void track_loop(std::vector<std::pair<float, float>>& line_array, float w1, float w2, float height)
{
    //track quad coords
    float A1x,A1z,A2x,A2z, B1x,B1z,B2x,B2z;
    float C1x,C1z,C2x,C2z, D1x,D1z,D2x,D2z;

    glColor4f(0.0, 0.0, 0.3, 1.0);
    glBegin(GL_QUADS);
    int num_points = line_array.size();
    for (int i = 0; i <= num_points; i++) {

        //pi, pi+1, and pi+2 (points on medium line)
        std::pair<float, float> pi = line_array[i % num_points];
        std::pair<float, float> pi_p1 = line_array[(i + 1) % num_points];
        std::pair<float, float> pi_p2 = line_array[(i + 2) % num_points];

        //calcute ui (normal vector from pi to pi+1)
        std::pair<float, float> ui = {(pi_p1.first - pi.first), (pi_p1.second - pi.second)};
        normalize_2d_vec(ui);

        //calcute ui_p1 (normal vector from pi+1 to pi+2)
        std::pair<float, float> ui_p1 = {(pi_p2.first - pi_p1.first), (pi_p2.second - pi_p1.second)};
        normalize_2d_vec(ui_p1);

        //calcute vi (normal vector prep to ui)
        std::pair<float, float> vi = {ui.second, -ui.first};
        std::pair<float, float> vi_p1 = {ui_p1.second, -ui_p1.first};

        //calclate quad coords
        A1x = pi.first + vi.first*w1; A1z = pi.second + vi.second*w1;
        A2x = pi.first + vi.first*w2; A2z = pi.second + vi.second*w2;

        B1x = pi_p1.first + vi_p1.first*w1; B1z = pi_p1.second + vi_p1.second*w1;
        B2x = pi_p1.first + vi_p1.first*w2; B2z = pi_p1.second + vi_p1.second*w2;

        C1x = pi.first - vi.first*w1; C1z = pi.second - vi.second*w1;
        C2x = pi.first - vi.first*w2; C2z = pi.second - vi.second*w2;

        D1x = pi_p1.first - vi_p1.first*w1; D1z = pi_p1.second - vi_p1.second*w1;
        D2x = pi_p1.first - vi_p1.first*w2; D2z = pi_p1.second - vi_p1.second*w2;

        //outward quad
        glNormal3f(0., 1., 0.);
        glVertex3f(A1x, height, A1z);
        glVertex3f(A2x, height, A2z);
        glVertex3f(B2x, height, B2z);
        glVertex3f(B1x, height, B1z);

        //outward quad sides
        glNormal3f(1, 0, 0);
        glVertex3f(A1x, 0, A1z);
        glVertex3f(A1x, height, A1z);
        glVertex3f(B1x, height, B1z);
        glVertex3f(B1x, 0, B1z);

        glNormal3f(-1, 0, 0);
        glVertex3f(A2x, height, A2z);
        glVertex3f(A2x, 0, A2z);
        glVertex3f(B2x, 0, B2z);
        glVertex3f(B2x, height, B2z);

        //inward quad
        glNormal3f(0., 1., 0.);
        glVertex3f(C1x, height, C1z);
        glVertex3f(D1x, height, D1z);
        glVertex3f(D2x, height, D2z);
        glVertex3f(C2x, height, C2z);

        //inward quad sides
        glNormal3f(1, 0, 0);
        glVertex3f(C2x, height, C2z);
        glVertex3f(D2x, height, D2z);
        glVertex3f(D2x, 0, D2z);
        glVertex3f(C2x, 0, C2z);

        glNormal3f(-1, 0, 0);
        glVertex3f(C1x, height, C1z);
        glVertex3f(C1x, 0, C1z);
        glVertex3f(D1x, 0, D1z);
        glVertex3f(D1x, height, D1z);
    }
    glEnd();
}


static void sleeper(float pix, float piz, float vix, float viz, float uix, float uiz, float s1, float s2, float height)
{
  // Far point on sleeper in direction of ui
  float six = pix + uix*s2;
  float siz = piz + uiz*s2;

  // Sleeper coords
  float S1x,S1z,S2x,S2z,S3x,S3z,S4x,S4z;

  // Comupute sleeper coords
  S1x = pix + vix*s1; S1z = piz + viz*s1;
  S2x = pix - vix*s1; S2z = piz - viz*s1;
  S3x = six + vix*s1; S3z = siz + viz*s1;
  S4x = six - vix*s1; S4z = siz - viz*s1;

  // top of sleeper
  glNormal3f(0, 1, 0);
  glVertex3f(S1x, height, S1z);
  glVertex3f(S3x, height, S3z);
  glVertex3f(S4x, height, S4z);
  glVertex3f(S2x, height, S2z);

  // left side
  glNormal3f(1, 0, 0);
  glVertex3f(S2x, 0, S2z);
  glVertex3f(S2x, height, S2z);
  glVertex3f(S4x, height, S4z);
  glVertex3f(S4x, 0, S4z);

  // right side
  glNormal3f(-1, 0, 0);
  glVertex3f(S3x, height, S3z);
  glVertex3f(S1x, height, S1z);
  glVertex3f(S1x, 0, S1z);
  glVertex3f(S3x, 0 , S3z);

  // back side
  glNormal3f(0, 0, 1);
  glVertex3f(S2x, 0, S2z);
  glVertex3f(S1x, 0, S1z);
  glVertex3f(S1x, height, S1z);
  glVertex3f(S2x, height, S2z);

  // front side
  glNormal3f(0, 0, -1);
  glVertex3f(S4x, 0, S4z);
  glVertex3f(S4x, height, S4z);
  glVertex3f(S3x, height, S3z);
  glVertex3f(S3x, 0 , S3z);
}


void sleepers(std::vector<std::pair<float, float>>& line_array, float s1, float s2, float height, int step)
{
  glColor4f(0.59*1/2,0.29*1/2,0.00, 1);
  glBegin(GL_QUADS);
  int num_points = line_array.size();
  for (int i = 0; i < num_points; i+=step) {
    //pi, pi+1 (points on medium line)
    std::pair<float, float> pi = line_array[i % num_points];
    std::pair<float, float> pi_p1 = line_array[(i + 4) % num_points];

    //calcute ui (normal vector from pi to pi+1)
    std::pair<float, float> ui = {(pi_p1.first - pi.first), (pi_p1.second - pi.second)};
    normalize_2d_vec(ui);

    //calcute vi (normal vector prep to ui)
    std::pair<float, float> vi = {ui.second, -ui.first};
    sleeper(pi.first, pi.second, vi.first, vi.second, ui.first, ui.second, s1, s2, height);
  }
  glEnd();
  glMaterialfv(GL_FRONT, GL_SPECULAR, black);
}


void rail_bed(std::vector<std::pair<float, float>>& line_array, int n_points,  float major, float minor, GLuint txId[])
{
    int n_line_points = line_array.size();

    float vx, vy, vz;
    float wx, wy, wz;
    float tx, ty, tz;

    float theta = 0;
    float theta_step = M_PI / n_points;

    load_railbed_texture(txId);
    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < n_line_points; i++) {
        //pi, pi+1, and pi+2 (points on medium line)
        std::pair<float, float> pi = line_array[i % n_line_points];
        std::pair<float, float> pi_p1 = line_array[(i + 1) % n_line_points];
        std::pair<float, float> pi_p2 = line_array[(i + 2) % n_line_points];

        //calcute ui (normal vector from pi to pi+1)
        std::pair<float, float> ui = {(pi_p1.first - pi.first), (pi_p1.second - pi.second)};
        normalize_2d_vec(ui);

        //calcute ui+1 (normal vector from pi+1 to pi+2)
        std::pair<float, float> ui_p1 = {(pi_p2.first - pi_p1.first), (pi_p2.second - pi_p1.second)};
        normalize_2d_vec(ui_p1);

        //calcute vi, vi+1 (normal vector prep to ui and ui+1)
        std::pair<float, float> vi = {ui.second, -ui.first};
        std::pair<float, float> vi_p1 = {ui_p1.second, -ui_p1.first};


        // compute the eplipices centred at pi and pi+1
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 1, 1);
        glNormal3f(0, 1, 0);
        glBegin(GL_QUAD_STRIP);
        int j = 0;
        while (theta <= M_PI) {
            vx = pi.first + major*cos(theta)*vi.first;
            vy = minor*sin(theta);
            vz = pi.second + major*cos(theta)*vi.second;

            wx = pi_p1.first + major*cos(theta)*vi_p1.first;
            wy = minor*sin(theta);
            wz = pi_p1.second + major*cos(theta)*vi_p1.second;

            tx = pi_p1.first + major*cos(theta + theta_step)*vi_p1.first;
            ty = minor*sin(theta + theta_step);
            tz = pi_p1.second + major*cos(theta + theta_step)*vi_p1.second;

            normal(vx, vy, vz, wx, wy, wz, tx, ty, tz);

            glTexCoord2f((float)j/(n_points - 1), 0);
            glVertex3f(vx, vy, vz);

            glTexCoord2f((float)j/(n_points - 1), 1);
            glVertex3f(wx, wy, wz);

            theta += theta_step;
            j++;
        }
        glEnd();
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        theta = 0;
        j = 0;
    }
    glDisable(GL_TEXTURE_2D);
}


void freight_base(float rail_in, float rail_out, float rail_height, float base_len, float base_height, float wheel_rad)
{
  float wheel_in = rail_out - 0.5;
  float wx[12] = {base_len/2-1, base_len/2-2, base_len/2-3, -base_len/2+1, -base_len/2+2, -base_len/2+3,
                  base_len/2-1, base_len/2-2, base_len/2-3, -base_len/2+1, -base_len/2+2, -base_len/2+3};
  GLUquadric *q = gluNewQuadric();
  glNormal3f(0, 1, 0);
  //flat base
  glPushMatrix();
      glColor4f(0.1, 0.1, 0.1, 1.0);
      glTranslatef(0, rail_height + wheel_rad, 0);
      glScalef(base_len, base_height, 2*rail_out+1./2);
      glutSolidCube(1);
  glPopMatrix();
  //block under base
  glPushMatrix();
      glColor4f(0, 0, 0, 1);
      glTranslatef(0, rail_height, 0);
      glScalef(base_len-1, 1, 2*(rail_out-1));
      glutSolidCube(1);
  glPopMatrix();
  //wheels
  for (int i = 0; i < 12; i++) {
    glPushMatrix();
      glColor4f(0.1, 0.1, 0.1, 1.0);
      if (i < 6) {
        glPushMatrix();
          glTranslatef(wx[i], wheel_rad, wheel_in-wheel_rad);
          gluCylinder(q, wheel_rad, wheel_rad, wheel_rad, 30, 30);
        glPopMatrix();
        glPushMatrix();
          glTranslatef(wx[i], wheel_rad, wheel_in);
          gluDisk(q, 0, wheel_rad, 20, 2);
        glPopMatrix();
      } else {
        glTranslatef(wx[i], wheel_rad, -wheel_in);
        gluCylinder(q, wheel_rad, wheel_rad, wheel_rad, 30, 30);
        gluDisk(q, 0, wheel_rad, 20, 2);
      }
    glPopMatrix();
  }
  float connector_rad = 0.5;
  //connector front
  glPushMatrix();
      glColor3f(0.3, 0.3, 0.3);
      glTranslatef(base_len/2+connector_rad, rail_height+wheel_rad, 0);
      glRotatef(-90, 0, 1, 0);
      gluCylinder(q, connector_rad, connector_rad, connector_rad, 30, 30);
      gluDisk(q, 0, connector_rad, 20, 2);
  glPopMatrix();
  //connctor back
  glPushMatrix();
      glColor3f(0.3, 0.3, 0.3);
      glTranslatef(-base_len/2-connector_rad, rail_height+wheel_rad, 0);
      glRotatef(90, 0, 1, 0);
      gluCylinder(q, connector_rad, connector_rad, connector_rad, 30, 30);
      gluDisk(q, 0, connector_rad, 20, 2);
  glPopMatrix();
}

void freight_engine(float rail_in, float rail_out, float rail_height, float base_len, float base_height, float wheel_rad)
{
  freight_base(rail_in, rail_out, rail_height, base_len, base_height, wheel_rad);
  float engine_base_h = rail_height + 2*wheel_rad;
  float engine_h = engine_base_h + 2;
  float engine_front_w = rail_out-0.25;
  float base_w = 2*rail_out+1./2;
  float front_end =  base_len/2-0.5;
  // coords of front of engine
  float xs[10] = {base_len/2-3, base_len/2-3, base_len/2-2, base_len/2-2, front_end, front_end, base_len/2-2, base_len/2-2, base_len/2-3, base_len/2-3};
  float ys[10] = {engine_base_h, engine_h, engine_base_h, engine_h, engine_base_h, engine_h, engine_base_h, engine_h, engine_base_h, engine_h};
  float zs[10] = {-engine_front_w, -engine_front_w, -engine_front_w, -engine_front_w, 0, 0, engine_front_w, engine_front_w, engine_front_w, engine_front_w};
  // front of engine
  glPushMatrix();
  glColor3f(0.7, 0, 0);
    glBegin(GL_QUAD_STRIP);
      for (int i = 0; i < 10; i+=2) {
        if (i == 2) {
          glNormal3f(0, 0, 1);
        }
        if (i == 4 or i == 6) {
          std::pair<float, float> temp1 = {xs[i-1], zs[i-1]};
          std::pair<float, float> temp2 = {xs[i], zs[i]};
          std::pair<float, float> n = vec_in_dir(temp1, temp2);
          normalize_2d_vec(n);
          glNormal3f(n.second, 0, -n.first);
        }
        if (i == 8) {
          glNormal3f(0, 0, -1);
        }
        glVertex3f(xs[i], ys[i], zs[i]);
        glVertex3f(xs[i+1], ys[i+1], zs[i+1]);
      }
    glEnd();
    glBegin(GL_TRIANGLES);
      glNormal3f(0, 1, 0);
      glVertex3f(base_len/2-2, engine_h, engine_front_w);
      glVertex3f(front_end, engine_h, 0);
      glVertex3f(base_len/2-2, engine_h, -engine_front_w);
    glEnd();
    glBegin(GL_QUADS);
      glNormal3f(0, 1, 0);
      glVertex3f(base_len/2-3, engine_h, -engine_front_w);
      glVertex3f(base_len/2-3, engine_h, engine_front_w);
      glVertex3f(base_len/2-2, engine_h, engine_front_w);
      glVertex3f(base_len/2-2, engine_h, -engine_front_w);
    glEnd();
  glPopMatrix();
  // middle cab
  glPushMatrix();
    glBegin(GL_QUADS);
      //sides
      glNormal3f(1, 0, 0);
      glVertex3f(base_len/2-3, engine_base_h, base_w/2);
      glVertex3f(base_len/2-3, engine_h+1, base_w/2);
      glVertex3f(base_len/2-3, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-3, engine_base_h, -base_w/2);

      glNormal3f(-1, 0, 0);
      glVertex3f(base_len/2-6, engine_base_h, base_w/2);
      glVertex3f(base_len/2-6, engine_h+1, base_w/2);
      glVertex3f(base_len/2-6, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-6, engine_base_h, -base_w/2);

      glNormal3f(0, 0, -1);
      glVertex3f(base_len/2-3, engine_base_h, -base_w/2);
      glVertex3f(base_len/2-3, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-6, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-6, engine_base_h, -base_w/2);

      glNormal3f(0, 0, 1);
      glVertex3f(base_len/2-3, engine_base_h, base_w/2);
      glVertex3f(base_len/2-3, engine_h+1, base_w/2);
      glVertex3f(base_len/2-6, engine_h+1, base_w/2);
      glVertex3f(base_len/2-6, engine_base_h, base_w/2);

      //roof
      glNormal3f(0, 1, 2);
      glVertex3f(base_len/2-3, engine_h+1, base_w/2);
      glVertex3f(base_len/2-6, engine_h+1, base_w/2);
      glVertex3f(base_len/2-6, engine_h+2, base_w/2-2);
      glVertex3f(base_len/2-3, engine_h+2, base_w/2-2);

      glNormal3f(0, 1, -2);
      glVertex3f(base_len/2-3, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-6, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-6, engine_h+2, -base_w/2+2);
      glVertex3f(base_len/2-3, engine_h+2, -base_w/2+2);

      glNormal3f(0, 1, 0);
      glVertex3f(base_len/2-3, engine_h+2, base_w/2-2);
      glVertex3f(base_len/2-6, engine_h+2, base_w/2-2);
      glVertex3f(base_len/2-6, engine_h+2, -base_w/2+2);
      glVertex3f(base_len/2-3, engine_h+2, -base_w/2+2);
    glEnd();
    //window
    glNormal3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(base_len/2-3, engine_h+1, base_w/2);
      glVertex3f(base_len/2-3, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-3, engine_h+2, -base_w/2+2);
      glVertex3f(base_len/2-3, engine_h+2, base_w/2-2);
    glEnd();
    glNormal3f(-1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
      glVertex3f(base_len/2-6, engine_h+1, base_w/2);
      glVertex3f(base_len/2-6, engine_h+1, -base_w/2);
      glVertex3f(base_len/2-6, engine_h+2, -base_w/2+2);
      glVertex3f(base_len/2-6, engine_h+2, base_w/2-2);
    glEnd();
    //back block
    glColor3f(0.35, 0.35, 0.35);
    glBegin(GL_QUADS);
      glNormal3f(0, 0, 1);
      glVertex3f(base_len/2-6, engine_base_h, engine_front_w);
      glVertex3f(base_len/2-6, engine_h+2, engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_h+2, engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_base_h, engine_front_w);

      glNormal3f(0, 0, -1);
      glVertex3f(base_len/2-6, engine_base_h, -engine_front_w);
      glVertex3f(base_len/2-6, engine_h+2, -engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_h+2, -engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_base_h, -engine_front_w);

      glNormal3f(1, 0, 0);
      glVertex3f(base_len/2-6, engine_base_h, engine_front_w);
      glVertex3f(base_len/2-6, engine_h+2, engine_front_w);
      glVertex3f(base_len/2-6, engine_h+2, -engine_front_w);
      glVertex3f(base_len/2-6, engine_base_h, -engine_front_w);

      glNormal3f(-1, 0, 0);
      glVertex3f(-base_len/2+0.5, engine_base_h, engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_h+2, engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_h+2, -engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_base_h, -engine_front_w);

      glNormal3f(0, 1, 0);
      glVertex3f(base_len/2-6, engine_h+2, engine_front_w);
      glVertex3f(base_len/2-6, engine_h+2, -engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_h+2, -engine_front_w);
      glVertex3f(-base_len/2+0.5, engine_h+2, engine_front_w);
    glEnd();
  glPopMatrix();


}


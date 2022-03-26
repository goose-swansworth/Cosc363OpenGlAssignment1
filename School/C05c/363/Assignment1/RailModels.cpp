//  ========================================================================
//  COSC363: Computer Graphics (2022);  University of Canterbury.
//
//  RailModels.cpp
//  A collection of functions for generating the models for a railway scene
//  ==========================================================================

#include <cmath>
#include "GL/freeglut.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "RailModels.h"
#include "loadTGA.h"
#include "assignmentfuncs.h"
using namespace std;



float white[4] = {1., 1., 1., 1.};
float black[4] = {0};
GLuint txId;
    
//--------------- GROUND PLANE ------------------------------------
// This is a square shaped region on the xz-plane of size 400x400 units
// centered at the origin.  This region is constructed using small quads
// of unit size, to facilitate rendering of spotlights
//-----------------------------------------------------------------

void loadTexture()				
{
	glGenTextures(1, &txId);

	glBindTexture(GL_TEXTURE_2D, txId);  //Use this texture
  loadTGA("Dirt 00 seamless.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//Set texture parameters
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	
}

void floor()
{
    //loadTexture();
    //glBindTexture(GL_TEXTURE_2D, txId);
    //glEnable(GL_TEXTURE_2D);
    glColor3f(0.3, 0.3, 0.3);
    glNormal3f(0.0, 1.0, 0.0);

    //The floor is made up of several tiny squares on a 400 x 400 grid. Each square has a unit size.
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glBegin(GL_QUADS);
    for(int i = -200; i < 200; i++)
    {
        for(int j = -200;  j < 200; j++)
        {
            glVertex3f(i, 0, j);
            glVertex3f(i, 0, j+1);
            glVertex3f(i+1, 0, j+1);
            glVertex3f(i+1, 0, j);
        }
    }
    glEnd();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);

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


void sleepers(std::vector<std::pair<float, float>>& line_array, float s1, float s2, float height)
{
  glColor4f(0.59*1/2,0.29*1/2,0.00, 1);
  glBegin(GL_QUADS);
  int num_points = line_array.size();
  for (int i = 0; i < num_points; i+=4) {
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


void rail_bed(std::vector<std::pair<float, float>>& line_array, int n_points,  float major, float minor)
{
	int n_line_points = line_array.size();
	
	float vx, vy, vz;
	float wx, wy, wz;
	float tx, ty, tz;
	
	float theta = 0;
	float theta_step = M_PI / n_points ;
	
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
			
			glVertex3f(vx, vy, vz);
			glVertex3f(wx, wy, wz);
			
			theta += theta_step;
		}
		glEnd();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		theta = 0;
	}
}

//--------------- MODEL BASE --------------------------------------
// This is a common base for the locomotive and wagons
// The base is of rectangular shape (20 length x 10 width x 2 height)
// and has wheels and connectors attached.
//-----------------------------------------------------------------
void base()
{
    glColor4f(0.2, 0.2, 0.2, 1.0);   //Base color
    glPushMatrix();
      glTranslatef(0.0, 4.0, 0.0);
      glScalef(20.0, 2.0, 10.0);     //Size 20x10 units, thickness 2 units.
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();                 //Connector between wagons
      glTranslatef(11.0, 4.0, 0.0);
      glutSolidCube(2.0);
    glPopMatrix();

    //4 Wheels (radius = 2 units)
    //x, z positions of wheels:
    float wx[4] = {  -8,   8,   -8,    8 };
    float wz[4] = { 5.1, 5.1, -5.1, -5.1 };
    glColor4f(0.5, 0., 0., 1.0);    //Wheel color
    GLUquadric *q = gluNewQuadric();   //Disc

    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(wx[i], 2.0, wz[i]);
        gluDisk(q, 0.0, 2.0, 20, 2);
        glPopMatrix();
    }
}

//--------------- LOCOMOTIVE --------------------------------
// This simple model of a locomotive consists of the base,
// cabin and boiler
//-----------------------------------------------------------
void engine()
{
    base();

    //Cab
    glColor4f(0.8, 0.8, 0.0, 1.0);
    glPushMatrix();
      glTranslatef(7.0, 8.5, 0.0);
      glScalef(6.0, 7.0, 10.0);
      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(6.0, 14.0, 0.0);
      glScalef(4.0, 4.0, 8.0);
      glutSolidCube(1.0);
    glPopMatrix();

    //Boiler
    GLUquadric *q = gluNewQuadric();   //Cylinder
    glPushMatrix();
      glColor4f(0.5, 0., 0., 1.0);
      glTranslatef(4.0, 10.0, 0.0);
      glRotatef(-90.0, 0., 1., 0.);
      gluCylinder(q, 5.0, 5.0, 14.0, 20, 5);
      glTranslatef(0.0, 0.0, 14.0);
      gluDisk(q, 0.0, 5.0, 20, 3);
      glColor4f(1.0, 1.0, 0.0, 1.0);
      glTranslatef(0.0, 4.0, 0.2);
      gluDisk(q, 0.0, 1.0, 20,2);  //headlight!
    glPopMatrix();

}

//--------------- WAGON ----------------------------------
// This simple model of a rail wagon consists of the base,
// and a cube(!)
//--------------------------------------------------------
void wagon()
{
    base();

    glColor4f(0.0, 1.0, 1.0, 1.0);
    glPushMatrix();
      glTranslatef(0.0, 10.0, 0.0);
      glScalef(18.0, 10.0, 10.0);
      glutSolidCube(1.0);
    glPopMatrix();
}

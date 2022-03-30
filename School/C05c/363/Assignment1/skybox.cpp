#include <GL/gl.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "GL/freeglut.h"
#include "assignmentfuncs.h"
#include "loadTGA.h"
  //Texture ids
//--------------------------------------------------------------------------------
void load_sky_textures(GLuint txId[])				
{
	glGenTextures(6, txId); 	// Create 6 texture ids

    //up
	glBindTexture(GL_TEXTURE_2D, txId[0]);
    loadTGA("posy.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //down
    //glBindTexture(GL_TEXTURE_2D, txId[1]);
    loadTGA("negy.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //left
    //glBindTexture(GL_TEXTURE_2D, txId[2]);
    loadTGA("negx.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //right
    //glBindTexture(GL_TEXTURE_2D, txId[3]);
    loadTGA("posx.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //front
    //glBindTexture(GL_TEXTURE_2D, txId[4]);
    loadTGA("posz.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //back
    //glBindTexture(GL_TEXTURE_2D, txId[5]);
    loadTGA("negz.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

void skybox(GLuint txId[])
{   
    glGenTextures(6, txId);
    int box_size = 400;
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //up plane
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(box_size, box_size, box_size);

        glTexCoord2f(0, 1);
        glVertex3f(box_size, box_size, -box_size);

        glTexCoord2f(1, 1);
        glVertex3f(-box_size, box_size, -box_size);

        glTexCoord2f(1, 0);
        glVertex3f(-box_size, box_size, box_size);
    glEnd();

    //down plane
    glBindTexture(GL_TEXTURE_2D, txId[1]);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(box_size, -box_size, box_size);

        glTexCoord2f(0, 1);
        glVertex3f(box_size, -box_size, -box_size);

        glTexCoord2f(1, 1);
        glVertex3f(-box_size, -box_size, -box_size);

        glTexCoord2f(1, 0);
        glVertex3f(-box_size, -box_size, box_size);
    glEnd();

    //left plane
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0);
        glVertex3f(-box_size, -box_size, box_size);

        glTexCoord2f(0, 1);
        glVertex3f(-box_size, -box_size, -box_size);

        glTexCoord2f(1, 1);
        glVertex3f(-box_size, box_size, -box_size);

        glTexCoord2f(0, 1);
        glVertex3f(-box_size, box_size, box_size);
    glEnd();
    glPopMatrix();

    //right plane
    glBindTexture(GL_TEXTURE_2D, txId[3]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0);
        glVertex3f(box_size, -box_size, box_size);

        glTexCoord2f(0, 1);
        glVertex3f(box_size, -box_size, -box_size);

        glTexCoord2f(1, 1);
        glVertex3f(box_size, box_size, -box_size);

        glTexCoord2f(0, 1);
        glVertex3f(box_size, box_size, box_size);
    glEnd();
    glPopMatrix();
}
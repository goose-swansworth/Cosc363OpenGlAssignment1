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


void load_up_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[1]);
    loadTGA("posy.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void load_down_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    loadTGA("negy.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void load_left_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[3]);
    loadTGA("negx.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void load_right_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[4]);
    loadTGA("posx.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void load_back_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[5]);
    loadTGA("posz.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void load_front_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[6]);
    loadTGA("negz.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


void skybox(GLuint txId[])
{
    int box_size = 400;
    glPushMatrix();
    //up plane
    glEnable(GL_TEXTURE_2D);
    load_up_texture(txId);
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
    glDisable(GL_TEXTURE_2D);


    //left plane
    glEnable(GL_TEXTURE_2D);
    load_left_texture(txId);
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-box_size, 0, box_size);

        glTexCoord2f(1, 0);
        glVertex3f(-box_size, 0, -box_size);

        glTexCoord2f(1, 1);
        glVertex3f(-box_size, box_size, -box_size);

        glTexCoord2f(0, 1);
        glVertex3f(-box_size, box_size, box_size);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right plane
    glEnable(GL_TEXTURE_2D);
    load_right_texture(txId);
    glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(box_size, 0, box_size);

        glTexCoord2f(1, 0);
        glVertex3f(box_size, 0, -box_size);

        glTexCoord2f(1, 1);
        glVertex3f(box_size, box_size, -box_size);

        glTexCoord2f(0, 1);
        glVertex3f(box_size, box_size, box_size);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    //front plane
    glEnable(GL_TEXTURE_2D);
    load_front_texture(txId);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0); glVertex3f(-box_size, 0, box_size);
        glTexCoord2f(1, 0); glVertex3f(box_size, 0, box_size);
        glTexCoord2f(1, 1); glVertex3f(box_size, box_size, box_size);
        glTexCoord2f(0, 1); glVertex3f(-box_size, box_size, box_size);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    //back plane
    glEnable(GL_TEXTURE_2D);
    load_back_texture(txId);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(-box_size, 0, -box_size);
        glTexCoord2f(1, 0); glVertex3f(box_size, 0, -box_size);
        glTexCoord2f(1, 1); glVertex3f(box_size, box_size, -box_size);
        glTexCoord2f(0, 1); glVertex3f(-box_size, box_size, -box_size);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

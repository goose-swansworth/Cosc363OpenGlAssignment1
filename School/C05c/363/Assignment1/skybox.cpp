#include <GL/gl.h>
#include <GL/glext.h>
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



void skybox(GLuint texture_ids[])
{
    int box_size = 500;
    glPushMatrix();
    //up plane
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_ids[0]);
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
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


    //left plane
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_ids[2]);
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
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    //right plane
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_ids[3]);
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
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


    //front plane
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_ids[5]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glTexCoord2f(0, 0); glVertex3f(-box_size, 0, box_size);
        glTexCoord2f(1, 0); glVertex3f(box_size, 0, box_size);
        glTexCoord2f(1, 1); glVertex3f(box_size, box_size, box_size);
        glTexCoord2f(0, 1); glVertex3f(-box_size, box_size, box_size);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


    //back plane
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_ids[4]);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(-box_size, 0, -box_size);
        glTexCoord2f(1, 0); glVertex3f(box_size, 0, -box_size);
        glTexCoord2f(1, 1); glVertex3f(box_size, box_size, -box_size);
        glTexCoord2f(0, 1); glVertex3f(-box_size, box_size, -box_size);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

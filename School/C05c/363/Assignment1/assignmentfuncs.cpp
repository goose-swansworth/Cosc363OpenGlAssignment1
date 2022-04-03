#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include "GL/freeglut.h"
#include "assignmentfuncs.h"
#include "loadTGA.h"

using namespace std;


void parseMedianlineFile(ifstream& file, std::vector<std::pair<float, float>>& point_array) {
  string line;
  if (file.is_open())
  {
    int i = 0;
    while (getline(file, line))
    {
      string x_coord_s = line.substr(0, line.find(" "));
      string y_coord_s = line.substr(line.find(" "), line.length());
      float x_coord = stof(x_coord_s);
      float y_coord = stof(y_coord_s);
      std::pair<float, float> coord = {x_coord, y_coord};
      point_array.push_back(coord);
      i++;
    }
    file.close();
  }
  else cout << "Unable to open file";
}

void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
              float x3, float y3, float z3 )
{
      float nx, ny, nz;
      nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
      ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
      nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);

      glNormal3f(nx, ny, nz);
}

static float norm(float x, float y)
{
  return sqrt(x*x + y*y);
}

void normalize_2d_vec(std::pair<float, float>& vec)
{
  float vec_norm = norm(vec.first, vec.second);
  vec.first = vec.first / vec_norm;
  vec.second = vec.second / vec_norm;
}

std::pair<float, float> vec_in_dir(std::pair<float, float> r0, std::pair<float, float> dir_point)
{
  std::pair<float, float> dir_vec;
  dir_vec.first = dir_point.first - r0.first;
  dir_vec.second = dir_point.second - r0.second;
  return dir_vec;
}


void base_curve_normals(vector<float> vx, vector<float> vy, vector<float> &nx, vector<float> &ny)
{
    int n_points = vx.size();
    for (int i = 1; i <= n_points; i++) {
        pair<float, float> ui, ui_p1, vi_m1, vi, vi_p1, ni;
        vi_m1.first = vx[i - 1]; vi_m1.second = vy[i - 1];
        vi.first = vx[i]; vi.second = vy[i];
        vi_p1.first = vx[(i + 1) % n_points]; vi_p1.second = vy[(i + 1) % n_points];
        ui = vec_in_dir(vi_m1, vi);
        ui_p1 = vec_in_dir(vi, vi_p1);
        normalize_2d_vec(ui);
        normalize_2d_vec(ui_p1);
        ni.first = ui.second + ui_p1.second; ni.second = -ui.first + -ui.first;
        normalize_2d_vec(ni);
        nx.push_back(ni.first);
        ny.push_back(ni.second);
    }
}


void load_floor_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    loadTGA("Dirt 00 seamless.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

}

void load_railbed_texture(GLuint txId[])
{
    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("railbedrocks.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}

void load_boxcar_texture(GLuint txId[]) {
  glBindTexture(GL_TEXTURE_2D, txId[7]);  //Use this texture
    loadTGA("boxcarred.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
}

void load_brick_texture(GLuint txId[]) {
  glBindTexture(GL_TEXTURE_2D, txId[8]);  //Use this texture
    loadTGA("brickRough1.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}


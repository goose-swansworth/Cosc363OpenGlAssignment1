#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "GL/freeglut.h"
#include "assignmentfuncs.h"
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

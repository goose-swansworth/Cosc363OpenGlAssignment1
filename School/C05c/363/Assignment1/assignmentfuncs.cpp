#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
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
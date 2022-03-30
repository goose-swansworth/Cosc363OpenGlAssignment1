#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "GL/freeglut.h"

void parseMedianlineFile(std::ifstream&, std::vector<std::pair<float, float>>&);

void normalize_2d_vec(std::pair<float, float>& vec);

std::pair<float, float> vec_in_dir(std::pair<float, float> r0, std::pair<float, float> dir_point);

void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
              float x3, float y3, float z3 );


void load_floor_texture(GLuint txId[]);

void load_railbed_texture(GLuint txId[]);

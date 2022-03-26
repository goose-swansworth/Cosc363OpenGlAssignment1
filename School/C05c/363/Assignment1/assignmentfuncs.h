#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

void parseMedianlineFile(std::ifstream&, std::vector<std::pair<float, float>>&);

void normalize_2d_vec(std::pair<float, float>& vec);

std::pair<float, float> vec_in_dir(std::pair<float, float> r0, std::pair<float, float> dir_point);
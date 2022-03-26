#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "medianlineloader.h"
using namespace std;

Array2<float> line_array;

int main(void)
{
    ifstream medline_file("Oval.txt");
    string header;
    getline(medline_file, header);
    cout << header << endl;
    int num_points = stoi(header);
    for (int i = 0; i <= num_points; i++) {
        std::vector<float> temp_point = {0, 0};
        line_array.push_back(temp_point);
    }
   parseMedianlineFile(medline_file, line_array);
}

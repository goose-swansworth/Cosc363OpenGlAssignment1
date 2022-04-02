//  ========================================================================
//  COSC363: Computer Graphics (2022);  University of Canterbury.
//
//  RailModels.h
//  Header file for a collection of models for a railway scene
//  ========================================================================

#include "assignmentfuncs.h"
#include "GL/freeglut.h"

void floor(GLuint txId[]);

void tracks(float, float) ;

void track_loop(std::vector<std::pair<float, float>>& line_array, float w1, float w2, float height);

void sleepers(std::vector<std::pair<float, float>>& line_array, float s1, float s2, float height, int step);

void rail_bed(std::vector<std::pair<float, float>>& line_array, int n_points,  float major, float minor, GLuint txId[]);

void freight_base(float rail_in, float rail_out, float rail_height, float base_len, float base_height, float wheel_rad);

void freight_engine(float rail_in, float rail_out, float rail_height, float base_len, float base_height, float wheel_rad);

void boxcar(float rail_in, float rail_out, float rail_height, float base_len, float base_height, float wheel_rad, GLuint txID[]);

void tanker(float rail_in, float rail_out, float rail_height, float base_len, float base_height, float wheel_rad);

void log_car(float rail_in, float rail_out, float rail_height, float base_len, float base_height, float wheel_rad);

void tunnel(float h, float w, float in_rad);

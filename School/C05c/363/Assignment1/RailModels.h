//  ========================================================================
//  COSC363: Computer Graphics (2022);  University of Canterbury.
//
//  RailModels.h
//  Header file for a collection of models for a railway scene
//  ========================================================================

#include "assignmentfuncs.h"

void floor();

void tracks(float, float) ; 

void track_loop(std::vector<std::pair<float, float>>& line_array, float w1, float w2, float height);

void sleepers(std::vector<std::pair<float, float>>& line_array, float s1, float s2, float height);

void engine();

void wagon();

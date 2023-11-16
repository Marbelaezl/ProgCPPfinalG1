#pragma once

#include <cmath>
#include <vector>
#include <random>
#include <fstream>

void genposition(std::vector<std::vector<double>> &position, std::vector<double> angles);
void randanggen(std::vector<double> &theta, int seed);
void print(std::vector<std::vector<double>> positions, std::ofstream &out);
double dist2d(const std::vector<std::vector<double>> &positions);

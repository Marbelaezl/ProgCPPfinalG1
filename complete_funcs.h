#pragma once

#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>

void genposition(std::vector<std::vector<double>> &position, std::vector<double> angletheta, std::vector<double> anglephi);

void randanggen(std::vector<double> &anglevec, int seed);
void randanggenaux(std::vector<double> &anglevec, int seed);

void print(std::vector<std::vector<double>> positions, std::ofstream &out);

double dist3d(const std::vector<std::vector<double>> &positions);

void generatevectors(std::vector<double> &angletheta, std::vector<double> &anglephi, int seedtheta, int seedphi, int caso);


double mean_dist (const std::vector<std::vector<double>>&positions, int a);

std::vector<std::vector<double>> unstable (const std::vector<std::vector<double>>&positions);

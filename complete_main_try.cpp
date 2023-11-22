#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include "complete.h"

int main(int argc, char**argv){

    int caso = std::stoi(argv[1]);
    int N = std::stoi(argv[2]);
    std::string nombre = argv[3];
    int seedtheta = std::stoi(argv[4]);
    int seedphi = std::stoi(argv[5]);

    std::vector<double> theta(N);
    std::vector<double> phi(N);

    generatevectors(theta, phi, seedtheta, seedphi, caso);

    std::vector<std::vector<double>> pos(N+1);
    std::ofstream fout (nombre);

    genposition(pos,theta, phi);
    print(pos,fout);

    fout.close();


    std::ofstream longitud("longitud.txt");
    for (int i=0; i < 800; i++){
      generatevectors(theta, phi, i, i, caso);
      genposition(pos, theta, phi);
      longitud << i << "\t" << dist3d(pos) <<"\n";
    }
    longitud.close();


    return 0;

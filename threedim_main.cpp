#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include "threedim.h"

int main(int argc, char**argv){

    int seedtheta = std::stoi(argv[3]);
    int seedphi = std::stoi(argv[4]);
    std::string nombre = argv[2];
    int N = std::stoi(argv[1]);

    std::vector<double> theta(N);
    std::vector<double> phi(N);
    randanggen(theta, seedtheta);
    randanggen(phi, seedphi);

    std::vector<std::vector<double>> pos(N+1);
    std::ofstream fout (nombre);

    genposition(pos,theta, phi);
    print(pos,fout);

    fout.close();

    std::ofstream longitud("longitud.txt");
    for (int i=0; i < 800; i++){
      randanggen(theta, i);
      randanggen(phi, 2*i+1);
      genposition(pos, theta, phi);
      longitud << i << "\t" << dist2d(pos) <<"\n";
    }
    longitud.close()


    return 0;

}

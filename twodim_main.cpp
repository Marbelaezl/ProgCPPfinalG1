#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include "twodim.h"

void newposition(std::vector<double> &position, double angle );
void randanggen(std::vector<double> &theta, int seed);

int main(int argc, char**argv){

    int seed = std::stoi(argv[3]);
    std::string nombre = argv[2];
    int N = std::stoi(argv[1]);

    std::vector<double> theta(N);
    randanggen(theta, seed);

    std::vector<double> pos = {0.0,0.0}; //Posicion del primer monomero

    std::ofstream fout (nombre); //Nombre de un archivo para guardar los valores de cada posición 

    fout << pos[0] << "\t" << pos[1] << "\n";

    for (auto val: theta){
        newposition(pos, val);
        fout << pos[0] << "\t" << pos[1] << "\n";
    }

    fout.close();

    return 0;

}

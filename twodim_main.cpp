#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include "twodim.h"



int main(int argc, char**argv){

    int seed = std::stoi(argv[3]);
    std::string nombre = argv[2];
    int N = std::stoi(argv[1]);

    std::vector<double> theta(N);
    randanggen(theta, seed);

    std::vector<std::vector<double>> pos(N+1) ; //Posicion del primer monomero

    std::ofstream fout (nombre); //Nombre de un archivo para guardar los valores de cada posición 

    genposition(pos, theta);
    print(pos, fout);

    

    fout.close();
    //datos de la longitud promedio
    std::ofstream longitud("longitud.txt");
    for (int i=0; i < 800; i++){
      randanggen(theta, i);
      genposition(pos, theta);
      longitud << i << "\t" << dist2d(pos) <<"\n";
    }
    return 0;

}

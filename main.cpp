#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include "complete_funcs.h"

int main(int argc, char**argv){

  int caso;
  int N;
  std::string nombre;
  int seedtheta,seedphi;

  //Verification of command-line arguments.
    try{
      caso = std::stoi(argv[1]);
      N = std::stoi(argv[2]);
      switch (argc){
      case (3):
	{nombre = "data.txt"; seedtheta=1; seedphi=1; break;}
      case (4):
	{nombre = argv[3]; seedtheta=1;seedphi=1; break;}
      case (5):
	{nombre = argv[3]; seedtheta=std::stoi(argv[4]);seedphi=seedtheta; break;}
      case (6):
	{nombre = argv[3]; seedtheta=std::stoi(argv[4]);seedphi=std::stoi(argv[5]); break;}
      default:
	throw 1;
	
    }
    }
    catch(...){
      std::cerr<< "Usage: " << argv[0] << "Case N (fname seed1 seed2) \nRequired:\nCase: 1 for 2d polymer, 2 for 3d polymer, 3 for restricted 3d polymer \nN: number of monomers\nOptional:\nfname: Name of the file for the results to be printed at, including extension. Default: data.txt\nseed1: seed for random distribution of theta. Default: 1 \nseed2: seed for random distribution of phi. Default: seed1\n";
    return 1;
    }

    std::vector<double> theta(N);
    std::vector<double> phi(N);

    generatevectors(theta, phi, seedtheta, seedphi, caso);

    std::vector<std::vector<double>> pos(N+1);
    std::ofstream fout (nombre);

    genposition(pos,theta, phi);
    print(pos,fout);

    fout.close();

    //Generate data for length histogram
    std::ofstream longitud("longitud.txt");
    for (int i=0; i < 800; i++){
      generatevectors(theta, phi, i, i, caso);
      genposition(pos, theta, phi);
      longitud << i << "\t" << dist3d(pos) <<"\n";
    }
    longitud.close();


    return 0;
}

#include "threedim.h"

void genposition(std::vector<std::vector<double>> &position, std::vector<double> angletheta, std::vector<double> anglephi){
  std::vector currentpos={0.0,0.0,0.0};
  position[0] = currentpos;
  for (int i=0; i < angletheta.size();i++){
    currentpos[0] += std::cos(angletheta[i])*std::sin(anglephi[i]);
    currentpos[1] += std::sin(angletheta[i])*std::sin(anglephi[i]);
    currentpos[2] += std::cos(anglephi[i]);
    position[i+1] = currentpos;
  }
}

void randanggen(std::vector<double> &anglevec, int seed){
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0,2*M_PI);

    for (int i = 0; i < anglevec.size(); i++){
        double thetan = dis(gen);
        anglevec[i] = thetan;
    }
}

void print(std::vector<std::vector<double>> positions, std::ofstream &out){
  for(auto x: positions){
    out << x[0] << "\t" << x[1] << "\t" << x[2] << "\n";
  }
}

double dist3d(const std::vector<std::vector<double>> &positions){
  int N = positions.size() -1; // Último índice accesible
  return std::sqrt(std::pow((positions[0][0]-positions[N][0]),2) + std::pow((positions[0][1]-positions[N][1]),2) + std::pow((positions[0][2]-positions[N][2]),2));
}

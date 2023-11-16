#include "twodim.h"

void genposition(std::vector<std::vector<double>> &position, std::vector<double> angles){
  std::vector currentpos={0.0,0.0};
  position[0] = currentpos;
  for (int i=0; i < angles.size();i++){
    currentpos[0] += std::cos(angles[i]);
    currentpos[1] +=std::sin(angles[i]);
    position[i+1] = currentpos;
  }
}

void randanggen(std::vector<double> &theta, int seed){
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0,2*M_PI);

    for (int i = 0; i < theta.size(); i++){
        double thetan = dis(gen);
        theta[i] = thetan;
    }
}

void print(std::vector<std::vector<double>> positions, std::ofstream &out){
  for(auto x: positions){
    out << x[0] << "\t" << x[1] << "\n";
  }
}

double dist2d(const std::vector<std::vector<double>> &positions){
  int N = positions.size() -1; // Último índice accesible
  return std::sqrt(std::pow((positions[0][0]-positions[N][0]),2) + std::pow((positions[0][1]-positions[N][1]),2));
}

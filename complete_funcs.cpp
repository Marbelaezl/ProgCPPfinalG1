#include "complete_funcs.h"

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

void randanggenaux(std::vector<double> &anglevec, int seed){
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<> dis(0,2*M_PI);
    for (int i = 0; i < anglevec.size(); i++){
        double thetan = dis(generator);
        anglevec[i] = thetan;
    }
}

void generatevectors(std::vector<double> &angletheta, std::vector<double> &anglephi, int seedtheta, int seedphi, int caso){
    double angle = (109.5/180.0)*M_PI;
    if (caso == 1){
        std::fill(anglephi.begin(),anglephi.end(),(M_PI/2.0));
        randanggen(angletheta, seedtheta);
    } else if(caso == 2){
        randanggen(angletheta, seedtheta);
        randanggenaux(anglephi, seedphi);
    } else if(caso == 3){
        std::generate(angletheta.begin(), angletheta.end(), [multiplo = 1, angle]() mutable { return angle * (multiplo++); });
        randanggen(anglephi, seedphi);
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

double mean_dist (const std::vector<std::vector<double>>&positions, int a){
  int N = positions.size() -1; // Último índice accesible
  int M = positions[0].size() -1; //Tamaño de los vectores dentro de positions
  double mean_dist = 0.0;
  int b = 0;
  for (int ii = 0; ii <= N-a; ii++){
    double square = 0.0;
    for (int i = 0; i <= M; i++){
      square += std::pow ((positions[ii][i] - positions [a+ii][i]), 2);
    }
  square = std::sqrt(square);
  b += 1;
  mean_dist += square;
  }
  return mean_dist/b;
}
std::vector<std::vector<double>> unstable (const std::vector<std::vector<double>>&positions){
  int N = positions.size() - 1; // Último índice accesible
  int M = positions[0].size() - 1; //Tamaño de los vectores dentro de positions
  std::vector<std::vector<double>> c;
  for (int i = 0; i <= N; i++){
    for (int ii = i+2; ii <= N; ii++){
      double square = 0.0;
      for (int x = 0; x <= M; x++){
        square += std::pow ((positions[i][x] - positions [ii][x]), 2);
      }
      if (std::sqrt(square) < 1){
        c.push_back (positions[i]);
        c.push_back (positions[ii]);
      }
    }
  }
  return c;
}

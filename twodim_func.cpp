#include "twodim.h"

void newposition(std::vector<double> &position, double angle ){
    position[0] = position[0]+std::cos(angle);
    position[1] = position[1]+std::sin(angle);
}

void randanggen(std::vector<double> &theta, int seed){
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0,2*M_PI);

    for (int i = 0; i < theta.size(); i++){
        double thetan = dis(gen);
        theta[i] = thetan;
    }
}

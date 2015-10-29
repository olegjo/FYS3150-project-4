#include "isingmodel.h"
#include <iostream>
#include <armadillo>
#include "../lib.h"
#include <cmath>

using namespace std;
using namespace arma;


double energy(mat S, int pos_x, int pos_y)
{
    double E = 0;
    E += S(pos_y, pos_x)*S(pos_y+1, pos_x);
    E += S(pos_y, pos_x)*S(pos_y-1, pos_x);
    E += S(pos_y, pos_x)*S(pos_y, pos_x+1);
    E += S(pos_y, pos_x)*S(pos_y, pos_x-1);
    return -E;
}

int periodic(int index, int size)
{
    if (index == size - 1) {
        return 0;
    }
    if (index == 0) {
        return size -1;
    }
    else {
        return index;
    }
}

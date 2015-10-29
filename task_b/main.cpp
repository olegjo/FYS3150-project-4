#include <iostream>
#include "../lib.h"
#include <armadillo>
#include <cmath>
#include "../isingmodel.h"

using namespace std;
using namespace arma;

int main()
{

    double L = 3;
    long idum = -1;

    // initialize lattice
    mat S = zeros<mat>(L+2,L+2);
    for (int i = 1; i < L+1; i++) {
        for (int j = 1; j < L+1; j++) {
            S(i, j) = round(ran0(&idum))*2-1; // creating random 1's or -1's
        }
    }
    // Periodic boundary conditions
    for (int i = 1; i < L+1; i++) {
        S(i, 0) = S(i, L);
        S(0, i) = S(L, i);
        S(i, L+1) = S(i, 1);
        S(L+1, i) = S(1, i);
    }

    // Choose two random numbers in [1, L]. This is where I position myself in the lattice
    int pos_x = floor(ran0(&idum)*L + 1);
    int pos_y = floor(ran0(&idum)*L + 1);
    cout << pos_x << " " << pos_y << endl;
    // calculate the energy of this position
    double E = energy(S, pos_x, pos_y);
    cout << E << endl;
    cout << S << endl;
    // now change one of five spins - current, left, right, over, below
    int change = floor(ran0(&idum)*6);
    if (change == 0) {
        S(pos_y, pos_x) *= -1;
    }
    if (change == 1) {
        S(pos_y, pos_x+1) *= -1;
    }
    if (change == 2) {
        S(pos_y+1, pos_x) *= -1;
    }
    if (change == 3) {
        S(pos_y, pos_x-1) *= -1;
    }
    if (change == 4) {
        S(pos_y-1, pos_x) *= -1;
    }
    cout << energy(S, pos_x, pos_y) << endl;
    cout << S << endl;

    // calculate energy of this new state
    //

    return 0;
}


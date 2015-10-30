#include "isingmodel.h"
#include <iostream>
#include "../lib.h"
#include <cmath>

using namespace std;

int periodic(int index, int size, int add)
{
    return (index + size + add) % size;
}

int randint(int a, int b, long &idum)
{
    return floor(ran0(&idum)*(b+1-a) + a);
}

void Metropolis(int **S, double &E, double &M, double *w, int L, long &idum)
{
    // loop over all the elements in the lattice
    for (int y=0; y < L; y++) {
        for (int x=0; x < L; x++) {
            // Choose two random numbers in [0, L-1]. This is where I position myself in the lattice
            int ix = (int) (ran1(&idum)*(double)L);
            int iy = (int) (ran1(&idum)*(double)L);
            // calculate the change in energy of this state
            int deltaE = 2*S[iy][ix]*
                    (S[iy][periodic(ix, L, 1)] +
                    S[iy][periodic(ix, L, -1)] +
                    S[periodic(iy, L, 1)][ix] +
                    S[periodic(iy, L, -1)][ix]);
            // if deltaE <= 0 accept the new configuration, if not, check if a random number <= exp(deltaE/T) and accept
            if (ran1(&idum) <= w[deltaE+8] ) {
                S[iy][ix] *= -1;
                E += (double) deltaE;
                M += (double) 2*S[iy][ix];
            }
        }
    }
}



void Initialize_uniform(double **S, double &E, double &M, int L)
{
    E = M = 0.0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            S[i][j] = 1;
            M += (double) S[i][j];
        }
    }
    for (int y = 0; y < L; y++) {
        for (int x = 0; x < L; x++) {
            E -= (double) S[y][x]*
                    (S[periodic(y,L,-1)][x] +
                    S[y][periodic(x, L, -1)]);
        }
    }
}

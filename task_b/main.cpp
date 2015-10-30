#include <iostream>
#include "../lib.h"
#include <cmath>
#include "../isingmodel.h"
#include <iomanip>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    double T = atof(argv[1]); // Temperature
    double E, M;

    int L = atoi(argv[2]);
    int MCcycles = atoi(argv[3]);
    long idum = -1; // starting point for the RNG

    double average[5];

    // pre-calculating the possible changes in energy
    double w[17];
    for (int deltaE = -8; deltaE <= 8; deltaE++) {
        w[deltaE+8] = 0;
    }
    for (int deltaE = -8; deltaE <= 8; deltaE+=4) {
        w[deltaE+8] = exp(-deltaE/T);
    }
    for (int i = 0; i < 5; i++) average[i] = 0.0;

    // initialize lattice, and energy and magnetization for ground state
    int **S;
    for (int i=0; i<L; i++) {
        S = new int *[L];
    }
    for (int i=0; i<L; i++) {
        S[i] = new int [L];
    }
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

    for (int cycles=1; cycles<=MCcycles; cycles++) {
        Metropolis(S, E, M, w, L, idum);
        // update expectation values
        average[0] += E;    average[1] += E*E;
        average[2] += M;    average[3] += M*M;  average[4] += fabs(M);
    }




    double norm = 1/((double) (MCcycles));  // divided by total number of cycles
    double Eaverage = average[0]*norm;
    double E2average = average[1]*norm;
    double Maverage = average[2]*norm;
    double M2average = average[3]*norm;
    double Mabsaverage = average[4]*norm;
    // all expectation values are per spin, divide by 1/L/L
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;

    char *outfilename = argv[4];
    ofstream outfile(outfilename);

    outfile << setprecision(8) << MCcycles;
    outfile << setw(15) << setprecision(8) << T;
    outfile << setw(15) << setprecision(8) << Eaverage/L/L;
    outfile << setw(15) << setprecision(8) << Evariance/T/T; // divide by T**2 because specific heat
    outfile << setw(15) << setprecision(8) << Maverage/L/L;
    outfile << setw(15) << setprecision(8) << Mvariance/T;    // divide by T because suceptibility
    outfile << setw(15) << setprecision(8) << Mabsaverage/L/L << endl;
    outfile.close();


    //cout << Eaverage/L/L << endl;

    delete[] S;
    return 0;
}





















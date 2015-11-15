#include <iostream>
#include "../lib.h"
#include <cmath>
#include "../isingmodel.h"
#include <iomanip>
#include <fstream>
#include <time.h>

using namespace std;

int main()
{
    double T = 1; // Temperature
    int L = 20;
    int MCcycles = 1000;
    string initial_state = "Random";

    long idum = -259349; // starting point for the RNG
    double E, M;

    // pre-calculating the possible changes in energy
    double w[17];
    double average[5];

    for (int deltaE = -8; deltaE <= 8; deltaE++) {
        w[deltaE+8] = 0;
    }
    for (int deltaE = -8; deltaE <= 8; deltaE+=4) {
        w[deltaE+8] = exp(-deltaE/T);
    }

    // initialize lattice
    int **S;
    for (int i=0; i<L; i++) {
        S = new int *[L];
    }
    for (int i=0; i<L; i++) {
        S[i] = new int [L];
    }
    // initializing the lattice with random or uniform spin configuration
    initialize(S, E, M, L, idum, initial_state);

    for (int i = 0; i < 5; i++) average[i] = 0.0;

    E = calc_total_energy(S, L);
    int accepted = 0; // number of accepted energy states
    for (int cycles=1; cycles<=MCcycles; cycles++) {
        Metropolis(S, E, M, w, L, idum, accepted);

        string outfilename = "cycle_"+to_string(cycles)+".txt";
        ofstream outfile;
        outfile.open(outfilename, ios::out);
        outfile << "# Initial state: " << initial_state << endl;
        outfile << "# Temperature: " << T << endl;
        outfile << "# Lattice size L = " << L << endl;
        for (int i = 0; i<L; i++) {
            for (int j = 0; j<L; j++) {
                outfile << setw(3) << setprecision(1) << S[i][j];
            }
            outfile << endl;
        }
        outfile.close();
    }

    delete[] S;
    return 0;
}











































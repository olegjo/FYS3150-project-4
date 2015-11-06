#include <iostream>
#include "../lib.h"
#include <cmath>
#include "../isingmodel.h"
#include <iomanip>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 6) {
        cout << "Bad usage. Command line arguments:" << endl;
        cout << "T, L, critical variance, MCcylces, outfilename, initial state (Random or Uniform)" << endl << endl;
        cout << "Critical variance is the variance that below which, the system is considered" << endl;
        cout << "           stable and we start recording the total energy of the system." << endl;
        cout << "           sigma_E = 0.5 and sigma_E = 8.5 are found to be useful for T=1 and T=2." << endl;
    }

    double T = atof(argv[1]); // Temperature
    int L = atoi(argv[2]);
    float sigma_E_crit = atof(argv[3]);
    int MCcycles = atoi(argv[4]);
    string outfilename = argv[5];
    string initial_state = argv[6];

    long idum = -1; // starting point for the RNG
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


    ofstream outfile;
    outfile.open(outfilename, ios::out);
    outfile << "# Initial state: " << initial_state << endl;
    outfile << "# Temperature: " << T << endl;
    outfile << "# MCcycles  -  <E>  -  E" << endl;


    for (int i = 0; i < 5; i++) average[i] = 0.0;
    // initializing the lattice with random or uniform spin configuration
    E = M = 0.0;
    if (initial_state == "Random") {
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < L; j++) {
                S[i][j] = round(ran1(&idum))*2 - 1;
                M += (double) S[i][j];
            }
        }
    }
    if (initial_state == "Uniform") {
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < L; j++) {
                S[i][j] = 1;
                M += (double) S[i][j];
            }
        }
    }

    E = calc_total_energy(S, L);

    int accepted = 0; // number of accepted energy states
    for (int cycles=1; cycles<=MCcycles; cycles++) {
        Metropolis(S, E, M, w, L, idum, accepted);
        // update expectation values
        average[0] += E;    average[1] += E*E;
        average[2] += M;    average[3] += M*M;  average[4] += fabs(M);

        double Evariance = (average[1]/cycles - average[0]*average[0]/cycles/cycles)/L/L;
        outfile << setw(15) << setprecision(8) << cycles;
        outfile << setw(15) << setprecision(8) << Evariance;
        if (Evariance <= sigma_E_crit) outfile << setw(15) << setprecision(8) << calc_total_energy(S, L) << endl;
        if (Evariance > sigma_E_crit) outfile << setw(15) << setprecision(8) << "NA" << endl;
    }
    outfile.close();

    delete[] S;
    return 0;
}























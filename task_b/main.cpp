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
    clock_t start_all, finish_all, start_this, finish_this;
    start_all = clock();
    if (argc < 7) {
        cout << "Bad usage. Command line arguments:" << endl;
        cout << "T, L, MCcylces_min, MCcycles_max, N, outfilename, initial state (Random or Uniform)" << endl;
    }

    double T = atof(argv[1]); // Temperature
    int L = atoi(argv[2]);
    int MCcycles_min = atoi(argv[3]);
    int MCcycles_max = atoi(argv[4]);
    int N = atoi(argv[5]);
    string outfilename = argv[6];
    string initial_state = argv[7];

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
    outfile << "# MCcycles  -  T  -  Eaverage/part.  -  C_V  -  M/part  -  Xsi  -  abs(M)_average/part  -  N_accepted" << endl;


    double increment = (MCcycles_max - MCcycles_min)/((double) N);
    for (double MCcycles = MCcycles_min; MCcycles <= MCcycles_max; MCcycles += increment) {
        start_this = clock();
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

        for (int y = 0; y < L; y++) {
            for (int x = 0; x < L; x++) {
                E -= (double) S[y][x]*
                        (S[periodic(y,L,-1)][x] +
                        S[y][periodic(x, L, -1)]);
            }
        }


        int accepted = 0; // number of accepted energy states
        for (int cycles=1; cycles<=MCcycles; cycles++) {
            Metropolis(S, E, M, w, L, idum, accepted);
            // update expectation values
            average[0] += E;    average[1] += E*E;
            average[2] += M;    average[3] += M*M;  average[4] += fabs(M);
        }
        finish_this = clock();


        double norm = 1/((double) (MCcycles));  // divided by total number of cycles
        double Eaverage = average[0]*norm;
        double E2average = average[1]*norm;
        double Maverage = average[2]*norm;
        double M2average = average[3]*norm;
        double Mabsaverage = average[4]*norm;
        // all expectation values are per spin, divide by L*L
        double Evariance = (E2average- Eaverage*Eaverage)/L/L;
        double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;


        outfile << setw(15) << setprecision(8) << MCcycles;
        outfile << setw(15) << setprecision(8) << T;
        outfile << setw(15) << setprecision(8) << Eaverage/L/L;
        outfile << setw(15) << setprecision(8) << Evariance/T/T; // divide by T**2 because specific heat
        outfile << setw(15) << setprecision(8) << Maverage/L/L;
        outfile << setw(15) << setprecision(8) << Mvariance/T;    // divide by T because suceptibility
        outfile << setw(15) << setprecision(8) << Mabsaverage/L/L;
        outfile << setw(15) << setprecision(8) << accepted << endl;
        cout << MCcycles << "/" << MCcycles_max << "      " << ((finish_this - start_this*1.0)/CLOCKS_PER_SEC) << endl;
    }
    outfile.close();
    finish_all = clock();
    cout << "Total time: " << ((finish_all - start_all*1.0)/CLOCKS_PER_SEC) << endl;

    delete[] S;
    return 0;
}






















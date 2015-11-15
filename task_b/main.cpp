#include <iostream>
#include "../lib.h"
#include <cmath>
#include "../isingmodel.h"
#include <iomanip>
#include <fstream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[])
{
    double start_all, finish_all, start_this, finish_this;

    // initialize MPI
    int numprocs, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    start_all = MPI_Wtime();

    if (argc < 7) {
        if (my_rank == 0) {
            cout << "Bad usage. Command line arguments:" << endl;
            cout << "T_start, T_stop, N_T, L, MCcylces, outfilename, initial state (Random or Uniform)" << endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    double T_start = atof(argv[1]); // Temperature
    double T_stop = atof(argv[2]);
    int N_T = atof(argv[3]);
    int MCcycles = atoi(argv[4]);
    string outfilename = argv[5];
    string initial_state = argv[6];

    long idum = -1-my_rank; // starting point for the RNG
    double E, M;
    int L = 2;
    // initialize lattice
    int **S;
    for (int i=0; i<L; i++) {
        S = new int *[L];
    }
    for (int i=0; i<L; i++) {
        S[i] = new int [L];
    }

    // initialize the outfile
    ofstream outfile;
    outfile.open(outfilename, ios::out);
    outfile << "# Initial state: " << initial_state << endl;
    outfile << "# Lattice size: L = " << L << endl;
    outfile << "# MCcycles  -  T  -  <E>/particle  -  C_V  -  M/part  -  Xsi  -  <|M|>/particle  -  N_accepted" << endl;

    double increment_T = (T_stop - T_start)/((double) N_T);
    if (increment_T == 0) increment_T = 1;
    for (double T = T_start; T <= T_stop; T+=increment_T) {
        start_this = MPI_Wtime();
        // pre-calculating the possible changes in energy
        double w[17];
        int num_averages = 5;
        double average[num_averages];
        double total_average[num_averages];

        for (int deltaE = -8; deltaE <= 8; deltaE++) {
            w[deltaE+8] = 0;
        }
        for (int deltaE = -8; deltaE <= 8; deltaE+=4) {
            w[deltaE+8] = exp(-deltaE/T);
        }


        // Bradcasting to all nodes the common variables
        MPI_Bcast(&L, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&T, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(&MCcycles, 1, MPI_INT, 0, MPI_COMM_WORLD);



        int interval = MCcycles/numprocs;
        int myloop_begin = my_rank*interval + 1;
        int myloop_end = (my_rank + 1)*interval;
        if ( (my_rank == numprocs-1) && ( myloop_end < MCcycles) ) myloop_end = MCcycles;

        for (int i = 0; i < 5; i++) {
            average[i] = 0.0;
            total_average[i] = 0.0;
        }
        // initializing the lattice with random or uniform spin configuration
        initialize(S, E, M, L, idum, initial_state);

        int accepted = 0; // number of accepted energy states
        int accepted_total = 0;
        for (int cycles = myloop_begin; cycles <= myloop_end; cycles++) {
            Metropolis(S, E, M, w, L, idum, accepted);
            // update expectation values
            average[0] += E;    average[1] += E*E;
            average[2] += M;    average[3] += M*M;  average[4] += fabs(M);
        }

        // find total average
        for (int i = 0; i < num_averages; i++) {
            MPI_Reduce(&average[i], &total_average[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        }
        MPI_Reduce(&accepted, &accepted_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        finish_this = MPI_Wtime();
        if (my_rank == 0) {
            double norm = 1/((double) (MCcycles));  // divided by total number of cycles
            double Eaverage = total_average[0]*norm;
            double E2average = total_average[1]*norm;
            double Maverage = total_average[2]*norm;
            double M2average = total_average[3]*norm;
            double Mabsaverage = total_average[4]*norm;
            // all expectation values are per spin, divide by L*L
            double Evariance = (E2average - Eaverage*Eaverage)/L/L;
            double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;


            outfile << setw(15) << setprecision(8) << MCcycles;
            outfile << setw(15) << setprecision(8) << T;
            outfile << setw(15) << setprecision(8) << Eaverage/L/L;
            outfile << setw(15) << setprecision(8) << Evariance/T/T; // divide by T**2 because specific heat
            outfile << setw(15) << setprecision(8) << Maverage/L/L;
            outfile << setw(15) << setprecision(8) << Mvariance/T;    // divide by T because suceptibility
            outfile << setw(15) << setprecision(8) << Mabsaverage/L/L;
            outfile << setw(15) << setprecision(8) << accepted_total << endl;
            cout << T << "/" << T_stop << "      " << finish_this - start_this << " seconds " << endl;
        }
    }
    outfile.close();
    finish_all = MPI_Wtime();
    if (my_rank == 0) {
        cout << "Total time: " << finish_all-start_all << " seconds on " << numprocs << " processors" << endl;
    }

    delete[] S;
    MPI_Finalize();
    return 0;
}






















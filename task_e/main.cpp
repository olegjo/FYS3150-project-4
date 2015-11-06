#include <iostream>
#include "../lib.h"
#include <cmath>
#include "../isingmodel.h"
#include <iomanip>
#include <fstream>
#include <time.h>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[])
{


    // initialize MPI
    int numprocs, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (argc < 8) {
        if(my_rank == 0) {
            cout << "Bad usage. Command line arguments:" << endl;
            cout << "T_initial, T_final, T_step, L, N_MCcycles, outfilename, initial state (Random or Uniform)" << endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    double T_initial = atof(argv[1]); // initial temperature
    double T_final   = atof(argv[2]); // final temperature
    double T_step    = atof(argv[3]); // temperature step
    int L = atoi(argv[4]);
    int MCcycles = atoi(argv[5]);
    string outfilename = argv[6];
    string initial_state = argv[7];

    // Initialize the outputfile
    ofstream outfile;
    if (my_rank == 0) {
        outfile.open(outfilename, ios::out);
        outfile << "# Initial state: " << initial_state << endl;
        outfile << "# MCcycles  -  <E>  -  E" << endl;
    }

    double E, M, w[17], average[5], total_average[5];
    // initialize lattice. First allocating memory.
    int **S;
    for (int i=0; i<L; i++) {
        S = new int *[L];
    }
    for (int i=0; i<L; i++) {
        S[i] = new int [L];
    }


    /*
    Determine number of intervall which are used by all processes
    myloop_begin gives the starting point on process my_rank
    myloop_end gives the end point for summation on process my_rank
    */

    int no_of_intervals = MCcycles/numprocs;
    int myloop_begin = my_rank*no_of_intervals + 1;
    int myloop_end = (my_rank + 1)*no_of_intervals;
    if ( (my_rank == numprocs-1) && ( myloop_end < MCcycles) ) myloop_end = MCcycles;

    // Now let all nodes know about the common variables
    // They are: L, T_initial, T_final, T_step
    MPI_Bcast(&L, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&T_initial, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&T_final, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&T_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    long idum = -1-my_rank; // starting point for the RNG

    for (double T = T_initial; T < T_final; T+=T_step) {

        // initializing the lattice with random or uniform spin configuration
        initialize(S, E, M, L, idum, initial_state);

        // pre-calculating the possible changes in energy

        for (int deltaE = -8; deltaE <= 8; deltaE++) {
            w[deltaE+8] = 0;
        }
        for (int deltaE = -8; deltaE <= 8; deltaE+=4) {
            w[deltaE+8] = exp(-deltaE/T);
        }

        for (int i = 0; i < 5; i++) average[i] = 0.0;
        for (int i = 0; i < 5; i++) total_average[i] = 0.0;

        int accepted = 0; // number of accepted energy states
        for (int cycles = myloop_begin; cycles <= myloop_end; cycles++) {
            Metropolis(S, E, M, w, L, idum, accepted);
            // update expectation values
            average[0] += E;    average[1] += E*E;
            average[2] += M;    average[3] += M*M;  average[4] += fabs(M);
        }

        // find total average
        for (int i = 0; i < 5; i++) {
            MPI_Reduce(&average[i], &total_average[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        }

        outfile << setw(8) << setprecision(15) << T;
        outfile << setw(8) << setprecision(15) << L << endl;
    }



    delete[] S;
    outfile.close();
    MPI_Finalize();
    return 0;
}






















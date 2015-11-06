

int periodic(int index, int size, int add);

int randint(int a, int b, long& idum);
// returns a random integer in the interval [a, b]


void Metropolis(int** S, double &E, double &M, double *w, int L, long &idum, int &accepted);

void Initialize_uniform(double **S, double &E, double &M, int L);

double calc_total_energy(int **S, int L);

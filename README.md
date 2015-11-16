# FYS3150 project 4
This is the fourth numerical project in the computational physics course FYS3150 at University of Oslo 2015.
In it the two dimensional Ising model is solved using the metrolopis algorithm.

## Dependencies:
C++11 with mpi

Python 2.7 with numpy and matplotlib

## Overview
The source code can be found in the directories task_x where x=d, b, e. The easiest way to reproduce the data
is to run the python scripts in Results/task_y/run_y.py, y=b, c, d, e.

Each run_y.py has a variable 
```python
runAgain = False
```
Set this to ```True``` to rerun the calculations. All results files, are, however stored so that a 
rerun is not necessary. 

An animation of the lattice is also made and can be viewed by running the python file in `extra/extra.py`

### task b
Comarison between the numerical results and the analytical result for a 2 by 2 lattice.

### task c
A 20 by 20 lattice is used to invesitgate the stability of the method.

### task d
Probability of the energy of the system at different temperatures

### task e
Using lattice sizes L by L with L=20, 40, 60, 80 and 100 to approximate the critical temperature of the Ising model

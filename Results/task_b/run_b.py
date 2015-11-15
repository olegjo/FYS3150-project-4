import os
import numpy as np
import sys
sys.path.insert(0, '../')
from lesfil import lesfil
import matplotlib.pyplot as plt

runAgain = False

def mathrm(s):
	s = s.split()
	ret = ''
	for word in s:
		ret += '$\mathrm{%s}$ ' % word
	return ret



# path is the path to executable
path = '../../build-FYS3150-project-4-OpenMPI-Release/task_b/'

T_start = 1
T_stop = 1
N_T = 1
Initial_state = 'Random'

relerr = []

## The analytical solution
Z = np.cosh(8.0/T_start) + 12
Eaverage = (-8*np.sinh(8.0/T_start))/Z
E2average = (64*np.cosh(8.0/T_start))/Z
Maverage = 0
M2average = (32.*np.exp(8.0/T_start) + 8.)/Z
C_V = (E2average - Eaverage**2)/T_start/T_start/4.
chi = 1.0/T_start*(M2average - Maverage*Maverage)/4.
absMaverage = (8.*np.exp(8./T_start) + 4)/Z/4.
chi = 1.0/T_start*(M2average - absMaverage*absMaverage)/4.





for cycle in np.linspace(0, 100000, 1001):
	MCcylces = int(cycle)
	filename = 'task_b_T1_%f_T2_%f_NT_%i_MC_%i_%s.txt' % (T_start, T_stop, N_T, MCcylces, Initial_state)
	args = '%f %f %i  %i %s %s' % (T_start, T_stop, N_T, MCcylces, filename, Initial_state)
	run = 'mpirun -n 4 %stask_b %s' % (path, args)
	if runAgain:
		os.system(run)
	Eaverage_numerical = lesfil(filename)[2][0]
	relerr.append(abs(Eaverage/4. - Eaverage_numerical)/abs(Eaverage/4.)*100)

print ''
print '\# MC Cycles 	&	$\langle E \\rangle$	&	$C_V$	&	$\langle |M| \\rangle$ 	&	$\chi$ \\\\ \hline'
print '%s 	&	%.5f			&	%.5f	&	%.5f	&	%.5f \\\\' % ('Analytical', Eaverage/4., C_V, absMaverage, chi)
for MCcycles in [100, 1000, 10000, 100000, 1000000]:
	filename = 'task_b_T1_%f_T2_%f_NT_%i_MC_%i_%s.txt' % (T_start, T_stop, N_T, MCcycles, Initial_state)
	fil = lesfil(filename)
	C_V_numerical = float(fil[3][0])
	absMaverage_numerical = float(fil[6][0])
	chi_numerical = float(fil[5][0])
	Eaverage_numerical = float(fil[2][0])
	print '%i 		&	%.5f		&	%.5f		&	%.5f	&	%.5f	\\\\' % (fil[0][0], Eaverage_numerical, C_V_numerical, absMaverage_numerical, chi_numerical)
plt.plot(np.linspace(0, 100000, 1001), relerr)
plt.ylim([-1, 1])
plt.xlabel(mathrm('Monte Carlo Cycles'))
plt.ylabel(mathrm('Relative error [\%]'))
plt.savefig('task_b_T1_L2_relerrs.pdf')
#plt.show()
# print ''
# print '<E>/particle (numerical)  =', Eaverage_numerical
# print '<E>/particle (analytical) =', Eaverage/4.
# print 'Relative error (%)        =', abs(Eaverage/4. - Eaverage_numerical)/abs(Eaverage/4.)*100, '\n'


print '''
We need only 1000 monte carlo cycles to get a relative error of 0.29%.
At 10 000 cycles the relative error is 0.14%, and at 100 000 it is 0.017%.\n'''






















import os
import sys
sys.path.insert(0, '../')
from plotfil import plotfil
import matplotlib.pyplot as plt
from lesfil import lesfil
import numpy as np

doItAgain = False


def Filename(L, Tstart, Tstop, Tstep, MCcycles, initial_state):
	return 'task_e_Tstart_L_%i_%f_Tstop_%f_Tstep_%f_MC_%i_%s.txt' % (L, Tstart, Tstop, Tstep, MCcycles, initial_state)

def doit():
	filename = Filename(L, T_start, T_stop, T_step, MCcycles, initial_state)
	args = '%f %f %f %i %i %s %s' % (T_start, T_stop, T_step, L, MCcycles, filename, initial_state)
	run = 'mpirun -n 4 %stask_e %s' % (path, args)
	os.system(run)

def mathrm(s):
	s = s.split()
	ret = ''
	for word in s:
		ret += '$\mathrm{%s}$ ' % word
	return ret

path = '../../build-FYS3150-project-4-OpenMPI-Release/task_e/'

T_start = 2.0
T_stop = 2.4
T_step = 0.01 # 0.02
MCcycles = 1000000
initial_state = 'Random'

for L in [20, 40, 60, 80, 100]:
	if doItAgain:
		doit()

for L in [20, 40, 60, 80, 100]:
	filename = Filename(L, T_start, T_stop, T_step, MCcycles, initial_state)
	data = lesfil(filename)
	plt.figure(0)
	plt.subplot(211)
	plotfil(filename, 0, 1, label='$L=%i$' % L)

	plt.subplot(212)
	plotfil(filename, 0, 2, label='$L=%i$' % L)

	plt.figure(2)
	plt.subplot(211)
	plotfil(filename, 0, 3, label='$L=%i$' % L)

	plt.subplot(212)
	plotfil(filename, 0, 4, label='$L=%i$' % L)

plt.figure(0)
plt.subplot(211)
plt.plot((2.269, 2.269), (-1.8, -1.1), 'k')
#plt.xlabel(mathrm('Temperature')+'$T$')
plt.ylabel('$\langle E \\rangle$ '+mathrm('per particle'))
plt.legend(loc='best')
#plt.savefig('task_e_Eaverage_VS_time_1000000.pdf')

plt.subplot(212)
plt.plot((2.269, 2.269), (0.1, 1), 'k')

plt.xlabel(mathrm('Temperature')+'$kT/J$')
plt.ylabel('$\langle |M| \\rangle$ '+mathrm('per particle'))
plt.legend(loc='best')
plt.savefig('task_e_absMaverage_VS_time_1000000.pdf')

plt.figure(2)
plt.subplot(211)
plt.plot((2.269, 2.269), (0.5, 2.5), 'k')

#plt.xlabel(mathrm('Temperature')+'$T$')
plt.ylabel('$C_V$ '+mathrm('per particle'))
plt.legend(loc='best')
#plt.savefig('task_e_C_V_VS_time_1000000.pdf')

plt.subplot(212)
plt.plot((2.269, 2.269), (0, 180), 'k')

plt.xlabel(mathrm('Temperature')+'$kT/J$')
plt.ylabel('$\chi$ '+mathrm('per particle'))
plt.legend(loc='best')
plt.savefig('task_e_chi_VS_time_1000000.pdf')

plt.show()










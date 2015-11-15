import os
import sys
sys.path.insert(0, '../')
from plotfil import plotfil
import matplotlib.pyplot as plt

runAgain = False


def Filename(T, MCcycles, initial_state):
	return 'task_c_T_%f_MC_%i_%s.txt' % (T, MCcycles, initial_state)

def doit():
	filename = Filename(T, MCcycles, initial_state)
	args = '%f %i %i %s %s' % (T, L, MCcycles, filename, initial_state)
	run = '%stask_d %s' % (path, args)
	if runAgain:
		os.system(run)

def mathrm(s):
	s = s.split()
	ret = ''
	for word in s:
		ret += '$\mathrm{%s}$ ' % word
	return ret
path = '../../build-FYS3150-project-4-OpenMPI-Release/task_d/'

L = 20
MCcycles = 5000


### Run first with Uniform starting position
initial_state = 'Uniform'
## Temperature T = 1
T = 1
doit()

## Temperature T=2.4
T = 2.4
doit()


### Now with random starting position
initial_state = 'Random'
## Temperature T = 1
T = 1
doit()

## Temperature T=2.4
T = 2.4
doit()



### Now plot things:
## Uniform start
filename1 = Filename(1, MCcycles, 'Uniform')
filename2 = Filename(2.4, MCcycles, 'Uniform')
# <E>
plt.subplot(211)
plt.title(mathrm('Uniform'))
plotfil(filename1, 0, 1, label='$T=1$')	# T=1
plotfil(filename2, 0, 1, label='$T=2.4$')	# T=2.4
plt.ylim([-2.1, -1.1])
plt.legend(loc='best')
plt.ylabel('$\langle E \\rangle$ ')

# <|M|>
plt.subplot(212)
plotfil(filename1, 0, 2, label='$T=1$')	# T=1
plotfil(filename2, 0, 2, label='$T=2.4$')	# T=2.4
plt.ylim([0.4, 1.1])
plt.legend(loc='best')
plt.xlabel(mathrm('Number of monte carlo cycles'))
plt.ylabel('$\langle |M| \\rangle$')
plt.savefig('task_c_averages_uniform.pdf')

# accepted configurations
plt.figure()
plt.subplot(211)
plotfil(filename1, 0, 4, label='$T=1.0$')
plt.ylabel(mathrm('Number of accepted/MCcycles'))
plt.legend()
plt.subplot(212)
plotfil(filename2, 0, 4, label='$T=2.4$')
plt.xlabel(mathrm('Number of Monte Carlo cycles'))
plt.ylabel(mathrm('Number of accepted/MCcycles'))
plt.legend()
plt.savefig('task_c_accepted_Uniform.pdf')



## Random start

filename1 = Filename(1, MCcycles, 'Random')
filename2 = Filename(2.4, MCcycles, 'Random')
print filename1
# <E>
plt.figure()
plt.subplot(211)
plt.title(mathrm('Random'))
plotfil(filename1, 0, 1, label='$T=1$')	# T=1
plotfil(filename2, 0, 1, label='$T=2.4$')	# T=2.4
plt.ylim([-2.1, -1.1])
plt.legend(loc='best')
plt.ylabel('$\langle E \\rangle$ ')

# <|M|>
plt.subplot(212)
plotfil(filename1, 0, 2, label='$T=1$')	# T=1
plotfil(filename2, 0, 2, label='$T=2.4$')	# T=2.4
plt.legend(loc='best')
plt.xlabel(mathrm('Number of Monte Carlo cylces'))
plt.ylabel('$\langle |M| \\rangle$')
# plt.savefig('task_c_averages_random.pdf')
# accepted configurations
plt.figure()
plt.subplot(211)
plotfil(filename1, 0, 4, label='$T=1.0$')
plt.ylabel(mathrm('Number of accepted/MCcycles'))
plt.legend()
plt.subplot(212)
plotfil(filename2, 0, 4, label='$T=2.4$')
plt.xlabel(mathrm('Number of monte carlo cycles'))
plt.ylabel(mathrm('Number of accepted/MCcycles'))
plt.legend()
# plt.savefig('task_c_accepted_Random.pdf')


plt.figure()
plt.subplot(211)
plotfil(Filename(1, MCcycles, 'Random'), 0, 4, label=mathrm('Random'))
plt.legend()
plt.ylim([-5, 100])
plt.ylabel(mathrm('Number of accepted/MCcycles'))

plt.subplot(212)
plotfil(Filename(1, MCcycles, 'Uniform'), 0, 4, label=mathrm('Uniform'))
plt.legend()
plt.ylim([-0.1, 0.8])
plt.xlabel(mathrm('Number of Monte Carlo cycles'))
plt.ylabel(mathrm('Number of accepted/MCcycles'))
plt.show()
# plt.savefig('task_c_accepted_T1.pdf')


############### accepted configurations ###################
T_start = 1
T_stop = 3.5
T_step = 0.01
MCcycles = 500000
filename = 'task_c_T_%f_%f_MC_%i_%s.txt' % (T_start, T_stop, MCcycles, initial_state)

path = '../../build-FYS3150-project-4-OpenMPI-Release/task_e/'

args = '%f %f %f %i %i %s %s' % (T_start, T_stop, T_step, 20, MCcycles, filename, initial_state)
run = 'mpirun -n 4 %stask_e %s' % (path, args)
if runAgain:
	os.system(run)
plt.figure()
plotfil(filename, 0, 5)
plt.xlabel(mathrm('Temperature ')+'$kT/J$')
plt.ylabel(mathrm('Number of accepted configurations per MCcycle'))
# plt.savefig('task_c_accepted_VS_time_'+str(MCcycles)+'.pdf')
































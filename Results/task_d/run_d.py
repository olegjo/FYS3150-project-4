import os
import sys
import matplotlib.pyplot as plt
sys.path.insert(0, '../')
from lesfil import lesfil
import numpy as np

runAgain = True

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
MCcycles = 100000


### Run first with Uniform starting position
initial_state = 'Uniform'
## Temperature T = 1
# variance = 0.02
T = 1
doit()

## Temperature T=2.4
# variance = 8.61
T = 2.4
doit()


### Now with random starting position
initial_state = 'Random'
## Temperature T = 1
# Variance = 1.44
T = 1
doit()

## Temperature T=2.4
# variance = 7.80
T = 2.4
doit()




bins = [-800+4*i for i in range(401)]
### Now plot things:
## Uniform start
filename1 = Filename(1, MCcycles, 'Uniform')
filename2 = Filename(2.4, MCcycles, 'Uniform')

# T = 1
data1 = lesfil(filename1)
plt.figure(1)
plt.subplot(211)
plt.hist(data1[3][500:], bins=bins, normed=True, label='$T=1$')
plt.xlim([-800, -770])
plt.ylabel('$P(E)$')
plt.legend()

# T = 2.4
data2 = lesfil(filename2)
plt.figure(1)
plt.subplot(212)
plt.hist(data2[3][500:], bins=bins, normed=True, label='$T=2.4$')
plt.xlim([-700, -300])
plt.legend()
plt.ylabel('$P(E)$')
plt.xlabel(mathrm('Total energy')+' $E$')

plt.savefig('task_d_histogram_Uniform.pdf')


## Random start
filename1 = Filename(1, MCcycles, 'Random')
filename2 = Filename(2.4, MCcycles, 'Random')

# T = 1
data1 = lesfil(filename1)
plt.figure('Random')
plt.hist(np.array(data1[3][2000:]), bins=bins, normed=True, label='$T=1$, %s' % mathrm('Random'))
plt.xlim([-800, -770])
plt.legend()

# T = 2.4
data2 = lesfil(filename2)
plt.figure(4)
plt.hist(data2[3][1000:], bins=bins, normed=True, label='$T=2.4$, %s' % mathrm('Random'))
plt.xlim([-700, -300])
plt.legend()



T = 2.2
doit()

filename3 = Filename(2.2, MCcycles, 'Random')
plt.figure()
data3 = lesfil(filename3)
plt.hist(data3[3], bins=bins, normed=True, label='$T=2.2$')
plt.legend()

T = 2.3
doit()
filename3 = Filename(2.2, MCcycles, 'Random')
plt.figure()
data3 = lesfil(filename3)
plt.hist(data3[3], bins=bins, normed=True, label='$T=2.3$')
plt.legend()

T = 2.35
doit()
filename3 = Filename(2.2, MCcycles, 'Random')
plt.figure()
data3 = lesfil(filename3)
plt.hist(data3[3], bins=bins, normed=True, label='$T=2.35$')
plt.legend()

plt.show()


'''
Variance = 0.0230059
Variance = 8.25811
Variance = 0.0976123
Variance = 8.02067
'''
print 8.02067*20
print 0.0976123*20






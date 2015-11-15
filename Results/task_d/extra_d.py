import numpy as np
import matplotlib
matplotlib.use('TKAgg')
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import sys
sys.path.insert(0, '../')
from lesfil import lesfil
import os

runAgain = False


def Filename(T, MCcycles, initial_state):
	return 'task_c_T_%f_MC_%i_%s.txt' % (T, MCcycles, initial_state)


def doit():
	filename = Filename(T, MCcycles, initial_state)
	args = '%f %i %i %s %s' % (T, L, MCcycles, filename, initial_state)
	run = '%stask_d %s' % (path, args)
	if runAgain:
		os.system(run)


path = '../../build-FYS3150-project-4-OpenMPI-Release/task_d/'

L = 20
MCcycles = 100000
initial_state = 'Random'

for T in np.linspace(2, 2.4, 100):
	doit()

data = lesfil(Filename(2, MCcycles, initial_state))
bins = [-800+4*i for i in range(401)]


plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111)

hist, bins, patches = ax.hist(data[3][10000:], bins=bins, normed=True, label='$T=2.4$')
plt.draw()
for T in np.linspace(2, 2.4, 100):
	filename = Filename(T, MCcycles, initial_state)
	data = lesfil(filename)
	n, bins = np.histogram(data[3][10000:], bins, normed=True)
	for rect, h in zip(patches, n):
		rect.set_height(h)
	plt.draw()
plt.ioff()
plt.show()












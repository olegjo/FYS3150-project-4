import numpy as np
import matplotlib
matplotlib.use('TKAgg')
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
import sys
sys.path.insert(0, '../')
from lesfil import lesfil

cycles = range(1, 1001)

pics = np.zeros((len(cycles), 20, 20))
for cycle in cycles:
	filename = 'cycle_'+str(cycle)+'.txt'
	f = open(filename)
	A = np.zeros((20, 20))
	j = 0
	for line in f:
		numbers = line.split()
		if not numbers[0] == '#':
			for i in range(len(numbers)):
				A[j][i] = numbers[i]
			j += 1
	pics[cycle-1] = A

filename = 'task_c_T_1.000000_MC_5000_Random.txt'
data = lesfil(filename)


plt.ion()

fig = plt.figure()
ax = fig.add_subplot(211)
ax2 = fig.add_subplot(212)
ax.text(22, 8, '.', style='italic',
        bbox={'facecolor':'maroon', 'alpha':1, 'pad':10})
ax.text(23, 8.2, ' $\uparrow$', fontsize=20)
ax.text(22, 12, '.', style='italic',
        bbox={'facecolor':'blue', 'alpha':1, 'pad':10})
ax.text(23, 12.2, ' $\downarrow$', fontsize=20)
# plt.text(21,8,'$\uparrow$', color='r', fontsize=20)
# plt.text(21,10,'$\downarrow$', color='b', fontsize=20)

line = ax.matshow(pics[0])
line2, = ax2.plot(data[0], data[1])
ax2.set_xlim([0, 1000])
ax2.set_ylim([-1.9, -1.5])


line3, = ax2.plot((1, 1), (ax2.get_ylim()[0], ax2.get_ylim()[1]))
ax2.set_xlabel('$\mathrm{Monte}$ $\mathrm{Carlo}$ $\mathrm{cycles}$')
ax2.set_ylabel('$\langle E \\rangle$')
plt.draw()
for i in cycles[450:700]:
	line.set_data(pics[i-1])
	line3.set_xdata((i, i))
	ax.set_xlabel('Cycle = %i' % i)
	plt.draw()
plt.ioff()
plt.show()


# plt.subplot(211)
# plt.plot(data[0], data[1], 'k')
# plt.xlim([-10, 1000])
# plt.ylim([-1.9, -1.5])
# plt.plot((3,3), (plt.ylim()[0], plt.ylim()[1]), label='$\mathrm{Cycle}=3$')
# plt.plot((500,500), (plt.ylim()[0], plt.ylim()[1]), label='$\mathrm{Cycle}=500$')
# plt.plot((600,600), (plt.ylim()[0], plt.ylim()[1]), label='$\mathrm{Cycle}=600$')
# plt.legend()
# plt.xlabel('$\mathrm{Monte}$ $\mathrm{Carlo}$ $\mathrm{cycles}$')
# plt.ylabel('$\langle E \\rangle$')
# plt.savefig('extra_marked.pdf')
# plt.show()









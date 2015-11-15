# coding: latin-1
import numpy as np
import matplotlib.pyplot as plt
import os
import time
import sys

Eaverage  = []
C_V       = []
Maverage  = []
Xsi       = []
Mabsaverage = []
accepted  = []
MCcycles = []

outfilename = sys.argv[1]
f = open(outfilename)
for line in f:
	if not line.split()[0] == '#':
		numbers = np.array(line.split(), np.float64)
		MCcycles.append(numbers[0])
		Eaverage.append(numbers[2])
		C_V.append(numbers[3])
		Maverage.append(numbers[4])
		Xsi.append(numbers[5])
		Mabsaverage.append(numbers[6])
		accepted.append(numbers[7])


plt.plot(np.log10(MCcycles), np.array(Eaverage))
# plt.plot(MCcycles, Eaverage)
plt.xlabel('$\log_{10}(\mathrm{MC \ cycles})$')
plt.ylabel('$\langle E \\rangle$ (per particle)')
plt.ticklabel_format(style='plain', axis='y', scilimits=(0,0))
plt.savefig(outfilename[:-4]+'.pdf')
#os.system('open %s' % (outfilename[:-4]+'.pdf'))
plt.show()
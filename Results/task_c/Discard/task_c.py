# coding: latin-1
import numpy as np
import matplotlib.pyplot as plt
import os
import time

T = 2.4
L = 20
calculate_again = True
#random = '_randomINIT'
random = ''


MCcycles = 10**np.linspace(3, 7, 100)
Eaverage  = []
C_V       = []
Maverage  = []
Xsi       = []
Mabsaverage = []
accepted  = []

timestring = time.strftime('_%d-%m--%H-%M')
outfilename = 'Results_T'+str(T)+'_L'+str(L)+random+timestring+'.txt'

write_preamble = True
if calculate_again:
	done25 = False; done50 = False; done75 = False
	outfile = open(outfilename, 'a')
	for n in MCcycles:
		n = int(n)
		executable = '../../build-FYS3150-project-4-Desktop_Qt_5_5_1_clang_64bit-Release/task_b/task_b'
		filename = 'temp.txt'
		args = ' %s %s %s %s' % (str(T), str(L), str(n), filename)
		os.system(executable+args)
		f = open(filename)
		for line in f:
			if write_preamble:
				if line.split()[0] == '#':
					outfile.write(line)
				if line.split()[0] != '#':
					write_preamble = False
			if not line.split()[0] == '#':
				outfile.write(line)
				print line
		f.close()
		prosentferdig = float(n)/max(MCcycles)*100
		if not done25 and prosentferdig > 25:
			done25 = True
			os.system('say 25 prosent ferdig')
		if not done50 and prosentferdig > 50:
			done50 = True
			os.system('say 50 prosent ferdig')
		if not done75 and prosentferdig > 75:
			done75 = True
			os.system('say 75 prosent ferdig')
	outfile.close()
	os.system('rm temp.txt')
	os.system('say jeg er ferdig nå')


f = open(outfilename)
MCcycles = []
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
plt.xlabel('$\log_{10}(\mathrm{MC \ cycles})$')
plt.ylabel('$\langle E \\rangle$ (per particle)')
plt.ticklabel_format(style='plain', axis='y', scilimits=(0,0))
plt.show()


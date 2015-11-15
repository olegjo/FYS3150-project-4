import matplotlib.pyplot as plt
import numpy as np
from lesfil import lesfil
import sys

def plotfil(filename, x, y, label=None):
	data = lesfil(filename)
	plt.plot(data[x], data[y], label=label)

if __name__ == '__main__':
	filename = sys.argv[1]
	x = int(sys.argv[2])
	y = int(sys.argv[3])
	plotfil(filename, x, y)
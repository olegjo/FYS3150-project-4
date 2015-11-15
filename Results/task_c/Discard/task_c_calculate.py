# coding: latin-1
import numpy as np
import matplotlib.pyplot as plt
import os
import time

T = '1'
L = '20'
MCcycles_min = '1000'
MCcycles_max = '100000'
N_MCcycles = '300'
initial_state = 'Random'
# initial_state = 'Uniform'

timestring = time.strftime('_%d-%m--%H-%M')
os.system('mkdir Results'+timestring)
outfilename = 'Results%s/Results_T%s_L%s%s.txt' % (timestring, T, L, timestring)
args = ' %s %s %s %s %s %s %s' % (T, L, MCcycles_min, MCcycles_max, N_MCcycles, outfilename, initial_state)
executable = '../../build-FYS3150-project-4-Desktop_Qt_5_5_1_clang_64bit-Release/task_b/task_b'
os.system(executable+args)
os.system('python task_c_plot.py %s' % (outfilename))


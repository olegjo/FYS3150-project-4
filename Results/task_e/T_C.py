import numpy as np

L = [20, 40, 60, 80, 100]
T_C_C_V = [2.3, 2.29, 2.29, 2.28, 2.27]
T_C_xi = [2.37, 2.32, 2.31, 2.29, 2.29]

a = []
for i in range(5):
	for j in range(i+1, 5):
		a_new = L[j]*L[i]/(L[j]-L[i])*(T_C_C_V[i] - T_C_C_V[j])
		a.append(a_new)

aaverage = np.average(a)
T_C = []
for i in range(5):
	T_C.append(T_C_C_V[i] - aaverage/L[i])

print np.average(T_C)


a = []
for i in range(5):
	for j in range(i+1, 5):
		a_new = L[j]*L[i]/(L[j]-L[i])*(T_C_xi[i] - T_C_xi[j])
		a.append(a_new)

aaverage = np.average(a)
T_C = []
for i in range(5):
	T_C.append(T_C_xi[i] - aaverage/L[i])

print np.average(T_C)
print 2.269 
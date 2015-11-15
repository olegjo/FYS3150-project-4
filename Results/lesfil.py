
def lesfil(filename):
	data = []

	f = open(filename)
	for line in f:
		numbers = line.split()
		if not numbers[0] == '#':
			for i in range(len(numbers)):
				data.append([])
			break
	f.close()
	f = open(filename)
	for line in f:
		numbers = line.split()
		if not numbers[0] == '#':
			for i in range(len(numbers)):
				data[i].append(float(numbers[i]))

	f.close()
	return data


if __name__ == '__main__':
	import sys
	data = lesfil(sys.argv[1])
	for i in sys.argv[2:]:
		print data[int(i)]


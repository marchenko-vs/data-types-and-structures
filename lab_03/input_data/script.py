import random

with open("input_m.txt", "w") as f:
	for i in range(100):
		for j in range(100):
			number = random.randint(-100, 100)
			f.write(str(number) + ' ')
		f.write('\n')

with open("input_v.txt", "w") as f:
	for i in range(100):
		number = random.randint(-100, 100)
		f.write(str(number) + ' ')

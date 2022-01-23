
# import numpy as np
# import matplotlib.pyplot as plt

# file1 = open('my_sine.txt', 'r')
# Lines = file1.readlines()

# Angle = []
# AngleCvt = []
# Ua = []
# Ub = []
# Uc = []

# for i in range(500):
#     Angle.append(np.pi*3/2 + np.pi*2 * i / 500)

# for line in Lines:
#     sine_list = line.replace('\n','').split(' ')
#     Ua.append(float(sine_list[0]))
#     Ub.append(float(sine_list[1]))
#     Uc.append(float(sine_list[2]))

# plt.plot(Angle)
# plt.plot(Ua)
# plt.plot(Ub)
# plt.plot(Uc)
# plt.show()


import numpy as np
import matplotlib.pyplot as plt

file1 = open('loop.txt', 'r')
Lines = file1.readlines()

Angle = []
AngleCvt = []
Ua = []
Ub = []
Uc = []

for line in Lines:
    sine_list = line.replace('\n','').split('\t')
    Ua.append(float(sine_list[0]))
    Ub.append(float(sine_list[1]))
    Uc.append(float(sine_list[2]))

plt.plot(Ua)
plt.plot(Ub)
plt.plot(Uc)
plt.show()
import numpy as np
import matplotlib.pyplot as plt

wt = np.linspace(0,4*np.pi,100)

Ua = 5*np.sin(wt)+5
Ub = 5*np.sin(wt+np.pi*2/3)+5
Uc = 5*np.sin(wt+np.pi*4/3)+5

plt.plot(Ua,'--',c='b')
plt.plot(Ub,'--',c='b')
plt.plot(Uc,'--',c='b')

for i in range(100):
    plt.scatter(i, Ua[i])
    plt.scatter(i, Ub[i])
    plt.scatter(i, Uc[i])
    plt.plot([i,i],[Ua[i],Uc[i]])
    plt.plot([i,i],[Ua[i],Ub[i]])
    plt.pause(0.01)

plt.show()
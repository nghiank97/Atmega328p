import numpy as np
import matplotlib.pyplot as plt

wt = np.linspace(0,4*np.pi,100)

Ua = 24*np.sin(wt)
Ub = 24*np.sin(wt-np.pi*2/3)
Uc = 24*np.sin(wt+np.pi*2/3)

# Kc = (2/3)*np.array([
#     [1, -1/2, -1/2],
#     [0, np.sqrt(3)/2, -np.sqrt(3)/2],
#     [1/2, 1/2, 1/2]]).T

Kc = (2/3)*np.array([
    [1, -1/2, -1/2],
    [0, np.sqrt(3)/2, -np.sqrt(3)/2]])

Ualpha = []
Ubeta = []

for i in range(100):
    U = np.array([Ua[i], Ub[i], Uc[i]])
    Ubuff = np.dot(Kc,U)
    Ualpha.append(Ubuff[0])
    Ubeta.append(Ubuff[1])

Ud = []
Up = []

# Kp = np.array([
#     [np.cos(angle), np.sin(angle)],
#     [-np.sin(angle), np.cos(angle)]])

for i in range(100):
    U = np.array([Ualpha[i], Ubeta[i]])

    angle = wt[i]
    # print(angle)
    Kp = np.array([
        [np.cos(angle), np.sin(angle)],
        [-np.sin(angle), np.cos(angle)]])

    Ubuff = np.dot(Kp,U)
    Ud.append(Ubuff[0])
    Up.append(Ubuff[1])

fig, axs = plt.subplots(3, sharex=True, sharey=True)
fig.suptitle('Sharing both axes')
axs[0].plot(Ua,c='y',label='Ua')
axs[0].plot(Ub,c='r',label='Ub')
axs[0].plot(Uc,c='b',label='Uc')
axs[0].legend()

axs[1].plot(Ualpha,'-',c='r',label='Ualpha')
axs[1].plot(Ubeta,'-',c='g',label='Ubeta')
axs[1].legend()

axs[2].plot(Ud,'-',c='r',label='Ud')
axs[2].plot(Up,'-',c='g',label='Up')
axs[2].legend()


plt.show()
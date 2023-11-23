import matplotlib.pyplot as plt
import numpy as np

data1=np.genfromtxt("100.txt",delimiter="\t")
data2=np.genfromtxt("100-2.txt",delimiter="\t")

fig,ax=plt.subplots(1,2)
ax[0].plot(data1[:,0],data1[:,1],marker="o",color="green")
ax[1].plot(data2[:,0],data2[:,1],marker="s",color="red")
ax[0].set_xlabel("x, relative units")
ax[0].set_ylabel("y, relative units")
ax[1].set_xlabel("x, relative units")
ax[0].set_title("seed = 1")
ax[1].set_title("seed=2")
plt.show()

dist=np.genfromtxt("longitudes.txt")
fig_len,ax_len=plt.subplots()
fig_stable,ax_stable=plt.subplots()

ax_len.set_xlabel("length")
ax_len.set_ylabel("counts")
ax_len.set_title("Distancia promedio para N = 500 monómeros")

ax_stable.set_xlabel("unstable positions")
ax_stable.set_ylabel("counts")
ax_stable.set_title("Posiciones inestables para N = 500 monómeros")
print(dist)
for i in range(0,3):
    avglen= np.mean(dist[:,2*i +1])
    avgstable=np.mean(dist[:,2*i+2])
    ax_len.hist(dist[:,2*i+1], bins=20,label ="case " + str(i+2) +": "  + str(avglen.round(3)))
    ax_stable.hist(dist[:,2*i+1], bins=20,label ="case " + str(i+2) +": "  + str(int(avgstable)))
                
    


ax_len.legend()
ax_stable.legend()

plt.show()


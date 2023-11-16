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

dist=np.genfromtxt("longitud.txt",delimiter="\t")
fig,ax=plt.subplots()

ax.set_xlabel("length")
ax.set_ylabel("counts")
ax.hist(dist[:,1], bins=20)
avg= np.mean(dist[:,1])
ax.plot([avg,avg],[0,100],linestyle="--",color="black", label ="mean: " + str(avg))
ax.legend()
plt.show()

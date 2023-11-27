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

dist=np.genfromtxt("longitud.txt")
fig_len,ax_len=plt.subplots()
fig_stable,ax_stable=plt.subplots()

ax_len.set_xlabel("length")
ax_len.set_ylabel("counts")
ax_len.set_title("Distancia promedio para N = 500 monómeros")

ax_stable.set_xlabel("unstable positions")
ax_stable.set_ylabel("counts")
ax_stable.set_title("Pares inestables para N = 500 monómeros")

colors=["red","black","green"]
for i in range(0,3):
    avglen= np.mean(dist[:,2*i +1])
    avgstable=np.mean(dist[:,2*i+2])
    ax_len.hist(dist[:,2*i+1], bins=20,label ="case " + str(i+1) +": "  + str(avglen.round(3)),alpha=0.6,color=colors[i])
    ax_stable.hist(dist[:,2*i+2], bins=20,label ="case " + str(i+1) +": "  + str(int(avgstable)),alpha=0.6,color=colors[i])
                
    


ax_len.legend()
ax_stable.legend()

plt.show()
fig,ax=plt.subplots()
longitudes=np.genfromtxt("1-data.txt")
ax.set_xlabel("n")
ax.set_ylabel("average length")
ax.scatter(longitudes[:,0],longitudes[:,1],color="red")
ax.plot(longitudes[:,0],(2*longitudes[:,0]/np.pi)**(1/2),linestyle="--",color="black")
plt.show()

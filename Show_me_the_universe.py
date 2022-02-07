import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

cycles = int(input("Cycle number: "))

Time_Axis = np.loadtxt("Game_Saver.txt").reshape(cycles, 50, 50)

fig, ax = plt.subplots()

im = ax.matshow(Time_Axis[0], cmap="Greys")

ax.axis("off")

def animate(i):

    im.set_array(Time_Axis[i])

    return im,


ani = animation.FuncAnimation(fig, animate, frames=cycles, interval=50)

plt.show()


#The file MCByzantine contains the number of rounds in which the Byzantines generals reach an accord
#This program makes a graph of the times the number of round r is = to 1, 2, ..., 10 rounds and saves it as a file

import matplotlib.pyplot as plt
import numpy as np

# Load the data
data = np.loadtxt("MCByzantine.txt")

# Plot a hystogram
plt.hist(data, bins=10, color="blue", edgecolor="black")


# Add labels
plt.xlabel("Number of rounds")
plt.ylabel("Number of times")

# Show the plot
plt.show()

# Save the plot
plt.savefig("MCByzantine3.png")


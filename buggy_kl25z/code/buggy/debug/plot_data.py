import matplotlib.pyplot as plt
import numpy as np

def createGraphForCamera():
    # Initialize an empty plot
    fig, ax = plt.subplots()
    line, = ax.plot([], [])  # Empty line

    # Set axis limits
    ax.set_xlim(0, 10)
    ax.set_ylim(0, 1)

    # Set labels and title
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_title('Dynamic Plot')

def plotCamera(data):
    x_axe = np.arange(128)

    plt.figure()
    plt.plot(x_axe, data)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.grid(True)
    # Add labels and title
    plt.title('Data from Camera')

    # Display the plot
    plt.show()

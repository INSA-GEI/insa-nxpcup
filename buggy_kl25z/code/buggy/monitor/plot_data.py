import multiprocessing as mp
import time
from matplotlib.animation import FuncAnimation
import random
import matplotlib.pyplot as plt
import os

def test_serial(data_queue, exit_event):
    print('Start test serial...')
    while not exit_event.is_set():
        if not data_queue.empty():
            buffer = data_queue.get()
            print(buffer)
            print(len(buffer))
            time.sleep(0.1)

def update_plot(frame, line, data_queue):
    buffer = [0] * 128  # Default buffer if the queue is empty
    if not data_queue.empty():
        buffer = data_queue.get()  # Get data from the queue
    # Convert the buffer to a list of 16-bit integers
    print(buffer)
    line.set_ydata(buffer)  # Update the y-values of the plot

def plot_data(data_queue, exit_event):
    # Create a figure and axis for the plot
    fig, ax = plt.subplots()

    # Initialize the plot with all values set to 0
    x = range(128)
    line, = ax.plot(x, [0] * 128)

    # Set the plot title and labels
    ax.set_title("Real-time Camera Data Plot")
    ax.set_xlabel("Coordinate Index")
    ax.set_ylabel("Brightness Value")
    ax.set_xlim(0, 127)
    ax.set_ylim(0, 1023)
    # Create the animation

    animation = FuncAnimation(fig, update_plot, fargs=(line, data_queue), interval=100)

    # Show the plot
    plt.ion()
    plt.show()

    # Keep checking the exit_event and close the plot when it's set
    while not exit_event.is_set():
        plt.pause(0.1)  # Pause for a short period of time (in seconds)
    plt.close(fig)  # Close the plot

def generate_random_arrays(array_length):
    random_array_16bits = []
    for i in range(array_length):
        random_array_16bits.append(random.randint(0, 1023))
    random_array = []
    for value in random_array_16bits:
        msb = value >> 8  # Get the most significant byte
        lsb = value & 0xFF  # Get the least significant byte
        random_array.append(msb)
        random_array.append(lsb)
    return random_array

if __name__ == '__main__':
    # Create a queue to communicate between processes
    queue = mp.Queue()
    exit_event = mp.Event()
    # Create the process
    process = mp.Process(target=plot_data, args=(queue, exit_event))
    process.start()

    # Generate some sample data and put it into the queue
    sample_data = [800 for i in range(128)]

    
    data_raw = []
    for i in sample_data:       
        msb = i >> 8  # Get the most significant byte
        lsb = i & 0xFF  # Get the least significant byte
        data_raw.append(msb)
        data_raw.append(lsb)    
    # Keep updating the plot with new data
    try :
        while True:
            #queue.put(generate_random_arrays(128))  # Put the new data into the queue
            queue.put(data_raw)
            # Add some delay between updates
            time.sleep(0.1)  # Delay for 0.1 seconds
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        exit_event.set()
        process.join()
        if process.is_alive():
            print("Warning: process did not terminate correctly")
        else:
            print("Process terminated correctly")
    
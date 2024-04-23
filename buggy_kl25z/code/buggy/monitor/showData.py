import time
import os
import multiprocessing as mp
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
from inputUser import inputUser

### CONSTANTS
CAMERA_DATA_SIZE = 256
CAMERA_RESOLUTION = 128
CAMERA_VALUE_MAX = 1023

######################################################################################################
# Function to plot the camera other data (RoadMiddle, RoadMiddleOld, BlackLineLeft, BlackLineRight, Nbr_edges)
######################################################################################################
def printOthersCameraData(dataCameraOthers, data_camera_others_lock, exit_event):
    try:
        while not exit_event.is_set():
            os.system('cls' if os.name == 'nt' else 'clear')
            print('\033[H')
            data_camera_others_lock.acquire()
            print("RoadMiddle: ", dataCameraOthers[0])
            print("RoadMiddleOld: ", dataCameraOthers[1])
            print("BlackLineLeft: ", dataCameraOthers[2])
            print("BlackLineRight: ", dataCameraOthers[3])
            print("Nbr_edges: ", dataCameraOthers[4])
            data_camera_others_lock.release()
            time.sleep(1)
        # Exit
        print("Exiting printOthersCameraData")
    except KeyboardInterrupt:
        exit_event.set()
        print("Exiting printOthersCameraData")
        return

######################################################################################################
# Function to plot the camera data
######################################################################################################

def plotCameraData(dataCamera, dataCamera_lock, exit_event):
    fig, ax = plt.subplots()
    # Initialize the plot with all values set to 0
    # x = range(128)
    dataCamera_lock.acquire()
    line, = ax.plot(dataCamera)
    dataCamera_lock.release()
    try:
        # Function to update the plot
        def update_plot(frames, dataCamera, dataCamera_lock, exit_event):
            dataCamera_lock.acquire()
            line.set_ydata(list(dataCamera))  # Update the y-values of the plot
            dataCamera_lock.release()
            if exit_event.is_set():
                plt.close('all')
            return line,
        
        # Set the plot title and labels
        ax.set_title("Real-time Camera Data Plot")
        ax.set_xlabel("Coordinate Index")
        ax.set_ylabel("Brightness Value")
        ax.set_xlim(0, 127)
        ax.set_ylim(0, 1000)
        # Create the animation

        animation = FuncAnimation(fig, update_plot, fargs=(dataCamera, dataCamera_lock, exit_event), interval=25, blit = True, cache_frame_data=False)

        # Show the plot
        plt.grid()
        plt.show()
        # Exit when window is closed
        print("Exiting watch")
        exit_event.set()
    except KeyboardInterrupt:
        plt.close()
        print("Exiting watch")
        exit_event.set()  
    

def test_print(inputQueue):
    try:
        while not inputQueue.empty():
            os.system('cls' if os.name == 'nt' else 'clear')  # Clear the terminal
            print('\033[H' + str(inputQueue.get()), end='\r')
            time.sleep(1)
    except KeyboardInterrupt:
        print("Exiting")
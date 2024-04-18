import serial
import struct
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

### Global parameters
watchOption = 0

def watch(inputQueue, exit_event):
    data = []
    try:
        ser = serial.Serial(COM_PORT, baudrate=BAUD_RATE)
        ser.flush()
        print("Serial port opened")
        while not exit_event.is_set():
            if ser.in_waiting:
                data = ser.read(CAMERA_DATA_SIZE)
                if len(data) == CAMERA_DATA_SIZE:
                    data = struct.unpack('h' * (len(data) // 2), data)
                    #if data[1] > 0 or data[1] < 1023:
                    os.system('cls' if os.name == 'nt' else 'clear')  # Clear the terminal
                    print('\033[H' + str(data), end='\r')
            if not inputQueue.empty():
                command = inputQueue.get()
                print(command)
                ser.flush()
                ser.write(command)
                print("Command sent")
        # Exit
        ser.close()
        print("Serial port closed")
        print("Exiting watch")
    except serial.SerialException:
        print("Error: Could not open serial port")
        exit_event.set()
        return
    except KeyboardInterrupt:
        print("Closing serial port")
        ser.close()
        exit_event.set()
        print("Exiting watch")
        return

######################################################################################################
# TEST CODE
######################################################################################################

def plot(data, output_data_lock, exit_event):
    fig, ax = plt.subplots()
    # Initialize the plot with all values set to 0
    # x = range(128)
    output_data_lock.acquire()
    line, = ax.plot(data)
    output_data_lock.release()
    try:
        # Function to update the plot
        def update_plot(frames, data, output_data_lock, exit_event):
            output_data_lock.acquire()
            line.set_ydata(list(data))  # Update the y-values of the plot
            output_data_lock.release()
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

        animation = FuncAnimation(fig, update_plot, fargs=(data, output_data_lock, exit_event), interval=25, blit = True, cache_frame_data=False)

        # Show the plot
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

if __name__ == "__main__":
    #test_print()
    inputQueue = mp.Queue()
    exit_event = mp.Event()
    #p_main = mp.Process(target=watch, args=(inputQueue, ))

    p_input = mp.Process(target=inputUser, args=(inputQueue, exit_event,))
    p_input.start()

    p_output = mp.Process(target=watch, args=(inputQueue, exit_event,))
    p_output.start()
    try:
        # Wait for both processes to finish
        p_input.join()
        p_output.join()
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        exit_event.set()
        p_input.join()
        p_output.join()
        if p_input.is_alive() & p_output.is_alive():
            print("Warning: process did not terminate correctly")
        else:
            print("Process terminated correctly")
import serial
import struct
import time
import os
import multiprocessing as mp
from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
from inputUser import inputUser

### CONSTANTS
COM_PORT = 'COM11'
BAUD_RATE = 115200
CAMERA_DATA_SIZE = 256
CAMERA_RESOLUTION = 128
CAMERA_VALUE_MAX = 1023

### Global parameters
watchOption = 0

def watch(inputQueue):
    data = []
    try:
        ser = serial.Serial(COM_PORT, baudrate=BAUD_RATE)
        ser.flush()
        print("Serial port opened")
        while True:
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
    except serial.SerialException:
        print("Error: Could not open serial port")
        return
    except KeyboardInterrupt:
        print("Closing serial port")
        ser.close()
        return

######################################################################################################
# TEST CODE
######################################################################################################
def update_plot(line, ser, data):
    if ser.in_waiting:
        data = ser.read(CAMERA_DATA_SIZE)
        if len(data) == CAMERA_DATA_SIZE:
                    data = struct.unpack('h' * (len(data) // 2), data)
    line.set_ydata(data)  # Update the y-values of the plot

def plot(inputQueue):
    data = [0] * 128
    try:
        ser = serial.Serial(COM_PORT, baudrate=BAUD_RATE)
        ser.flush()
        print("Serial port opened")
        
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

        animation = FuncAnimation(fig, update_plot, fargs=(line, ser, data), interval=50)

        # Show the plot
        plt.ion()
        plt.show()

        while True:
            if not inputQueue.empty():
                command = inputQueue.get()
                print(command)
                ser.flush()
                ser.write(command)
                print("Command sent")

    except serial.SerialException:
        print("Error: Could not open serial port")
        return
    except KeyboardInterrupt:
        print("Closing serial port")
        ser.close()
        return

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
    #p_main = mp.Process(target=watch, args=(inputQueue, ))

    p_input = mp.Process(target=inputUser, args=(inputQueue, ))
    p_input.start()

    p_output = mp.Process(target=plot, args=(inputQueue, ))
    p_output.start()
    try:
        # Wait for both processes to finish
        p_input.join()
        p_output.join()
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        p_input.join()
        p_output.join()
        if p_input.is_alive() & p_output.is_alive():
            print("Warning: process did not terminate correctly")
        else:
            print("Process terminated correctly")
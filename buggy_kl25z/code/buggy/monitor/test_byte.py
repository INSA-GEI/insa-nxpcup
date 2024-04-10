from matplotlib.animation import FuncAnimation
import matplotlib.pyplot as plt
import serial
import struct

### CONSTANTS
COM_PORT = 'COM11'
BAUD_RATE = 115200
CAMERA_DATA_SIZE = 256
CAMERA_RESOLUTION = 128
CAMERA_VALUE_MAX = 1023
### GLOBAL VARIABLES
ser = serial.Serial(COM_PORT, baudrate=BAUD_RATE)
ser.timeout = 0
data = [0] * CAMERA_RESOLUTION
# Create a figure and axis for the plot
fig, ax = plt.subplots()

def get_data():
    global ser
    global data
    if ser.in_waiting:      
        new_data = ser.read(CAMERA_DATA_SIZE)
        if len(new_data) == 256:
            new_data = struct.unpack('h' * (len(new_data) // 2), new_data)
            data = new_data
            #print(new_data)
            #print(len(new_data))
    yield data 

def update_plot(data, line):
    line.set_ydata(data)  # Update the y-values of the plot

def plot_data():
    global fig
    global ax
    global data
    global ser
    # Initialize the plot with all values set to 0
    x = range(CAMERA_RESOLUTION)
    line, = ax.plot(x, [0] * CAMERA_RESOLUTION)

    # Set the plot title and labels
    ax.set_title("Real-time Camera Data Plot")
    ax.set_xlabel("Coordinate Index")
    ax.set_ylabel("Brightness Value")
    ax.set_xlim(0, CAMERA_RESOLUTION-1)
    ax.set_ylim(0, CAMERA_VALUE_MAX)

    # Create the animation
    animation = FuncAnimation(fig, update_plot, frames=get_data, fargs=(line,), interval=20)

    # Show the plot
    plt.show()

#ser = serial.Serial(COM_PORT, baudrate=BAUD_RATE)
print("Serial port opened")
ser.flush()
print("Serial port opened")
try :
    plot_data()
except KeyboardInterrupt:
    # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
    # This signals the subprocesses to exit their loops and finish execution.
    ser.close()
    print("Serial port closed")
    plt.close(fig)
    print("Plot closed")
    print("Process terminated correctly")
    
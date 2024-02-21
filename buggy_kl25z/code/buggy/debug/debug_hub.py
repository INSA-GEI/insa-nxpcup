import serial
from read_data import *
from plot_data import *
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

# Define the COM port and baud rate
COM_PORT = 'COM11'
BAUD_RATE = 115200

# Open the serial port
ser = serial.Serial(COM_PORT, BAUD_RATE)

try:
    # Continuous loop to receive and process data
    while True:     
        if (checkReceivedData(ser)):
            getData(ser)
        
# Handle keyboard interrupt (Ctrl+C) to gracefully exit
except KeyboardInterrupt:
    print("Exiting...")
    # Close the serial port
    ser.close()
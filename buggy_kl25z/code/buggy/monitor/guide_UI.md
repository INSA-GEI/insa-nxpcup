# How to use the user interface
### Autor: Triet NGUYEN (tr_nguye@insa-toulouse.fr)

The user interface allows users to connect with the buggy through a Bluetooth connection. Users can then receive debug data from the buggy, including data's camera, speed and servo angle. Also, users can change the parameters of the buggy remotely.

## Table of Contents
- [How to use the user interface](#how-to-use-the-user-interface)
    - [Requirements](#requirements)
    - [Connect to the Buggy](#connect-to-the-buggy)
    - [Start the interface](#start-the-interface)
    - [Choose the data to watch](#choose-the-data-to-watch)
    - [Changing parameters](#changing-parameters)
    - [Exit](#exit)

## Requirements
The Bluetooth module (Bluetooth Bee) has to be installed on the buggy.

## How to use the user interface
### Requirements
The Bluetooth module (Bluetooth Bee) has to be installed on the buggy.


### Connecting to the Buggy
1. Turn on the buggy (and the Bluetooth Bee), the LED1 must be blinking
2. Go to the Bluetooth configuration of your PC, search for NXPCup device and connect to it (pass: 1234)
3. The status of the Bluetooth device should be "paired"

### Starting the interface
1. With the buggy turned on, open the file hub.py with VS code
2. Run the code, an input window and a plot window should appear. The data is also available on the terminal
3. The LED2 on the Bluetooth Bee should be on and not blinking
4. If the connection cannot be established, the plot windows will close and an error will appear on the terminal

### Choosing the data to watch
1. From the input window, choose an object that you want to watch
2. If the object is a camera, choose between data and data-diff to watch
3. Submit your choice

### Changing parameters
1. From the input window, choose a parameter to change
2. Change the value (attention to its format)
3. Submit the change

### Exit
Close the input window to close the interface
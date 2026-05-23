from serial import Serial, SerialException
import struct

# Constants
COM_PORT = 'COM11'
BAUD_RATE = 115200
TIME_OUT = 1
CAMERA_DATA_SIZE = 256
DATA_OTHERS_SIZE = 16

def runSerial(inputQueue, dataCamera, dataCamera_lock, dataOthers, dataOthers_lock, exit_event):
    try:
        ser = Serial(COM_PORT, baudrate=BAUD_RATE, timeout=TIME_OUT)
        ser.flush()
        print("Serial port opened")
        while not exit_event.is_set():
            if not inputQueue.empty():
                command = inputQueue.get()
                if command != 0 :
                    print(command)
                    ser.write(command)
                    print("Command sent")
            if ser.in_waiting:
                dataCamera_received = ser.read(CAMERA_DATA_SIZE)
                if len(dataCamera_received) == CAMERA_DATA_SIZE:
                    # Unpack the data, from [LSB MSB] to 2 octets intergers
                    dataCamera_received = struct.unpack('h' * (CAMERA_DATA_SIZE // 2), dataCamera_received)
                    dataCamera_lock.acquire()
                    #print(len(dataCamera_received))
                    for i in range(len(dataCamera_received)):
                        dataCamera[i] = dataCamera_received[i]
                    dataCamera_lock.release()

                dataOthers_received = ser.read(DATA_OTHERS_SIZE)
                if len(dataOthers_received) == DATA_OTHERS_SIZE:
                    # Unpack the data, from [LSB MSB] to 2 octets intergers
                    dataOthers_received = struct.unpack('h' * (DATA_OTHERS_SIZE // 2), dataOthers_received)
                    dataOthers_lock.acquire()
                    for i in range(len(dataOthers_received)):
                        dataOthers[i] = dataOthers_received[i]
                    dataOthers_lock.release()
                
        ser.close()
        print("Serial port closed")   
    except SerialException:
        exit_event.set()
        print("Error: Could not open serial port")
        print("Exiting runSerial")
        return
    except KeyboardInterrupt:
        ser.close()
        print("Exiting runSerial")
        return
    
def testReceiveSerial(exit_event):
    try:
        ser = Serial(COM_PORT, baudrate=BAUD_RATE, timeout=TIME_OUT)
        ser.flush()
        print("Serial port opened")
        while not exit_event.is_set():
            if ser.in_waiting:
                dataCamera_received = ser.read(CAMERA_DATA_SIZE)
                if len(dataCamera_received) == CAMERA_DATA_SIZE:
                    # Unpack the data, from [LSB MSB] to 2 octets intergers
                    dataCamera_received = struct.unpack('h' * (CAMERA_DATA_SIZE // 2), dataCamera_received)
                    print(len(dataCamera_received))

                dataOthers_received = ser.read(DATA_OTHERS_SIZE)
                if len(dataOthers_received) == DATA_OTHERS_SIZE:
                    # Unpack the data, from [LSB MSB] to 2 octets intergers
                    dataOthers_received = struct.unpack('h' * (DATA_OTHERS_SIZE // 2), dataOthers_received)
                    print(len(dataOthers_received))
                
        ser.close()
        print("Serial port closed")   
    except SerialException:
        exit_event.set()
        print("Error: Could not open serial port")
        print("Exiting runSerial")
        return
    except KeyboardInterrupt:
        ser.close()
        print("Exiting runSerial")
        return
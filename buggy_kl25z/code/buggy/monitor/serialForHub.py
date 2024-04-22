from serial import Serial, SerialException
import struct

# Constants
COM_PORT = 'COM11'
BAUD_RATE = 115200
TIME_OUT = 1
CAMERA_DATA_SIZE = 256
CAMERA_OTHERS_SIZE = 10

def runSerial(inputQueue, dataCamera, dataCamera_lock, dataCameraOthers, dataCameraOthers_lock, exit_event):
    nb_bytes_to_receive = 8 # !!! Fix to 0  # Number of bytes to receive depend on which data we are watching
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
                        dataCamera[i] = dataCamera_received[len(dataCamera_received)-1-i]
                    dataCamera_lock.release()

                dataCameraOthers_received = ser.read(CAMERA_OTHERS_SIZE)
                if len(dataCameraOthers_received) == CAMERA_OTHERS_SIZE:
                    # Unpack the data, from [LSB MSB] to 2 octets intergers
                    dataCameraOthers_received = struct.unpack('h' * (CAMERA_OTHERS_SIZE // 2), dataCameraOthers_received)
                    dataCameraOthers_lock.acquire()
                    for i in range(len(dataCameraOthers_received)):
                        dataCameraOthers[i] = dataCameraOthers_received[i]
                    dataCameraOthers_lock.release()
                
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
from serial import Serial, SerialException
import struct

# Constants
COM_PORT = 'COM11'
BAUD_RATE = 115200
TIME_OUT = 1
CAMERA_DATA_SIZE = 256
CAMERA_OTHERS_SIZE = 8

def runSerial(inputQueue, outputBuffer, output_lock, exit_event):
    nb_bytes_to_receive = 256 # !!! Fix to 0  # Number of bytes to receive depend on which data we are watching
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
                data_received = ser.read(nb_bytes_to_receive)
                if len(data_received) == nb_bytes_to_receive:
                    # Unpack the data, from [LSB MSB] to 2 octets intergers
                    data_received = struct.unpack('h' * (len(data_received) // 2), data_received)
                    output_lock.acquire()
                    for i in range(len(data_received)):
                        outputBuffer[i] = data_received[len(data_received)-1-i]
                    output_lock.release()
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
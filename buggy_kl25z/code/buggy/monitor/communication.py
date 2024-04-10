import serial
import multiprocessing as mp
import struct
# Define the COM port and baud rate
COM_PORT = 'COM11'
BAUD_RATE = 115200

CAMERA_DATA_SIZE = 256

def communicate_uart_data(receive_queue, send_queue, exit_event):
    rx_buffer_size = 2048
    #rx_buffer = array.array('i', [0]*rx_buffer_size)  # 'i' denotes integer    received_bytes = 0
    rx_buffer = bytearray(rx_buffer_size)
    received_bytes = 0

    tx_buffer_size = 4
    #tx_buffer = array.array('i', [0]*tx_buffer_size)  # 'i' denotes integer    
    tx_bufer = bytearray(tx_buffer_size)

    try:
        ser = serial.Serial(COM_PORT, baudrate=BAUD_RATE)
        ser.flush()
        print("Serial port opened")
        while not exit_event.is_set():
            # Receive data from the serial port
            
            if ser.in_waiting > 0:
                data = ser.read(CAMERA_DATA_SIZE)
                #rx_buffer[received_bytes:received_bytes+CAMERA_DATA_SIZE] = struct.unpack('h' * (len(data) // 2), data)
                #rx_buffer[received_bytes:received_bytes+256] = [int.from_bytes(d, byteorder='big') for d in data]
                #rx_buffer[received_bytes:received_bytes+256] = ser.read(CAMERA_DATA_SIZE)
                data = struct.unpack('h' * (len(data) // 2), data)
                received_bytes += CAMERA_DATA_SIZE

                # Call a function for every 256 bytes received
                if received_bytes % CAMERA_DATA_SIZE == 0:
                    #if (rx_buffer[received_bytes-256] < 0x4):
                        #receive_queue.put(rx_buffer[received_bytes-CAMERA_DATA_SIZE:received_bytes])
                    receive_queue.put(data)
                    #else : 
                    #    dump = ser.read(1)                    
                #receive_queue.put(convert_to_int(rx_buffer[received_bytes-256:received_bytes]))
                # Check if the rx_buffer is full
                if received_bytes >= rx_buffer_size:
                    received_bytes = 0  # Overwrite from the first index
            
            # Send data to the serial port
            if not send_queue.empty():
                tx_buffer = send_queue.get()
                ser.write(tx_buffer)
        ser.close()
    except Exception as e:
        print(e) 
        ser.close()           
    

def test_serial(data_queue, exit_event):
    while not exit_event.is_set():
        data_raw = data_queue.get()
        data = []
        '''
        for i in range(0, len(data_raw), 2):
            lsb = data_raw[i]
            msb = data_raw[i+1]
            value = (msb << 8) | lsb
            data.append(value)
        print(data)
        '''
        print(data_raw)
    
if __name__ == '__main__':
    # Create a queue to communicate between processes
    data_queue = mp.Queue()
    command_queue = mp.Queue()
    exit_event = mp.Event()

    # Create the process
    p_uart = mp.Process(target=communicate_uart_data, args=(data_queue, command_queue, exit_event))
    p_test = mp.Process(target=test_serial, args=(data_queue, exit_event))
    p_uart.start()
    p_test.start()

    try :
        while True:
            pass
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        exit_event.set()
        p_test.join()
        p_uart.join()
        if p_test.is_alive() & p_uart.is_alive():
            print("Warning: process did not terminate correctly")
        else:
            print("Process terminated correctly")
    
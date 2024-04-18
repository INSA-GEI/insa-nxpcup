from multiprocessing import Process, Queue, Event, Lock, Array, Manager
from inputUser import inputUser
from printToTerminal import watch, plot
from serialForHub import runSerial
from time import sleep
import os

def test_receive_serial(outputBuffer, output_data_lock, exit_event):
    print("Start Test")
    try:
        while not exit_event.is_set():
            
            output_data_lock.acquire()
            os.system('cls' if os.name == 'nt' else 'clear')  # Clear the terminal
            print('\033[H' + str(outputBuffer), end='\r')
            output_data_lock.release()         
            sleep(1)           
    except KeyboardInterrupt:
        print("Exiting test")

def outputMethodSelect(outputBuffer, output_data_lock, outputMethod, exit_event):
    print("")

if __name__ == "__main__":
   
    data = Array('i', [100] * 128)  # Create a shared array
    
    try :
        exit_event = Event()
        output_data_lock = Lock()
        inputQueue = Queue()
        outputMethod = Queue()

        p_serial = Process(target=runSerial, args=(inputQueue, data, output_data_lock, exit_event,))
        p_serial.start()

        p_input = Process(target=inputUser, args=(inputQueue, outputMethod, exit_event,))
        p_input.start()

        p_output = Process(target=plot, args=(data, output_data_lock, exit_event,))
        p_output.start()
        """


        p_output = Process(target=plot, args=(exit_event, ser, ser_lock,))
        p_output.start()
    
        # Wait for both processes to finish
        
        p_output.join()
        """
        # Wait for the processes to finish
        p_serial.join()
        p_input.join()
        p_output.join()
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        exit_event.set()
        """
        p_input.join()
        p_output.join()
        if p_input.is_alive() & p_output.is_alive():
            print("Warning: processes did not terminate correctly")
        else:
            print("Process terminated correctly")
            print("HUB closed")
        """
        p_serial.join()
        p_output.join()
        if p_serial.is_alive() & p_input.is_alive() & p_output.is_alive():
            print("Warning: processes did not terminate correctly")
        else:
            print("Process terminated correctly")
            print("HUB closed")
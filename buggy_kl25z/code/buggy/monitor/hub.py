from multiprocessing import Process, Queue, Event, Lock, Array
from inputUser import inputUser
from showData import printOthersCameraData, plotCameraData
from serialForHub import runSerial
from time import sleep
import os

def test_receive_serial(dataCamera, data_camera_lock, dataCameraOthers, data_camera_others_lock, exit_event):
    print("Start Test")
    try:
        while not exit_event.is_set():
            os.system('cls' if os.name == 'nt' else 'clear')  # Clear the terminal
            data_camera_lock.acquire()
            
            #print('\033[H' + str(list(dataCamera)), end='\n')
            print(str(list(dataCamera)))
            data_camera_lock.release() 

            data_camera_others_lock.acquire()
            #print('\033[H' + str(list(dataCameraOthers)), end='\r')
            print(str(list(dataCameraOthers)))
            data_camera_others_lock.release()       
            sleep(1)           
    except KeyboardInterrupt:
        print("Exiting test")

if __name__ == "__main__":
   
    dataCamera = Array('i', [100] * 128)  # Create a shared array for the camera data
    dataCameraOthers = Array('i', [100] * 5)  # Create a shared array for the camera others data (RoadMiddle, RoadMiddleOld, BlackLineLeft, BlackLineRight, Nbr_edges)

    try :
        exit_event = Event()
        data_camera_lock = Lock()
        data_camera_others_lock = Lock()
        inputQueue = Queue()


        p_serial = Process(target=runSerial, args=(inputQueue, dataCamera, data_camera_lock, dataCameraOthers, data_camera_others_lock, exit_event,))
        p_serial.start()

        p_input = Process(target=inputUser, args=(inputQueue, exit_event,))
        p_input.start()

        p_plot = Process(target=plotCameraData, args=(dataCamera, data_camera_lock, exit_event,))
        p_plot.start()

        p_print = Process(target=printOthersCameraData, args=(dataCameraOthers, data_camera_others_lock, exit_event,))
        p_print.start()

        #p_test = Process(target=test_receive_serial, args=(dataCamera, data_camera_lock, dataCameraOthers, data_camera_others_lock, exit_event,))
        #p_test.start()
        
        # Wait for the processes to finish
        p_serial.join()
        p_input.join()
        p_plot.join()
        #p_print.join()
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        exit_event.set()
        p_serial.join()
        p_input.join()
        p_plot.join()
        #p_print.join()
        if p_serial.is_alive() & p_input.is_alive() & p_plot.is_alive() :
            print("Warning: processes did not terminate correctly")
        else:
            print("Process terminated correctly")
            print("HUB closed")
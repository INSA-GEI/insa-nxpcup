from multiprocessing import Process, Queue, Event, Lock, Array
from inputUser import inputUser
from showData import printOthersData, plotCameraData
from serialForHub import runSerial, testReceiveSerial
from time import sleep
import os

def test_print(dataCamera, data_camera_lock, dataOthers, data_others_lock, exit_event):
    print("Start Test")
    try:
        while not exit_event.is_set():
            os.system('cls' if os.name == 'nt' else 'clear')  # Clear the terminal
            data_camera_lock.acquire()
            
            #print('\033[H' + str(list(dataCamera)), end='\n')
            print(str(list(dataCamera)))
            data_camera_lock.release() 

            data_others_lock.acquire()
            #print('\033[H' + str(list(dataCameraOthers)), end='\r')
            print(str(list(dataOthers)))
            data_others_lock.release()       
            sleep(1)           
    except KeyboardInterrupt:
        print("Exiting test")

if __name__ == "__main__":
   
    dataCamera = Array('i', [100] * 128)  # Create a shared array for the camera data
    dataOthers = Array('i', [100] * 8)  # Create a shared array for others data (RoadMiddle, RoadMiddleOld, BlackLineLeft, BlackLineRight, Nbr_edges, SpeedLeft, SpeedRight, ServoAngle)

    for i in range(len(dataCamera)):
        dataCamera[i] = 50 + i%3
    dataCamera[20] = 400
    dataCamera[21] = 405
    dataCamera[22] = 406
    dataCamera[80] = 430
    dataCamera[81] = 435
    dataCamera[82] = 418
    dataCamera[105] = 100
    
    for i in range(len(dataOthers)):
        dataOthers[i] = i

    try :
        exit_event = Event()
        data_camera_lock = Lock()
        data_others_lock = Lock()
        inputQueue = Queue()

        # p_serial = Process(target=runSerial, args=(inputQueue, dataCamera, data_camera_lock, dataOthers, data_others_lock, exit_event,))
        # p_serial.start()

        p_input = Process(target=inputUser, args=(inputQueue, exit_event,))
        p_input.start()

        p_plot = Process(target=plotCameraData, args=(dataCamera, data_camera_lock, exit_event,))
        p_plot.start()

        p_print = Process(target=printOthersData, args=(dataOthers, data_others_lock, exit_event,))
        p_print.start()
        
        #p_test = Process(target=test_print, args=(dataCamera, data_camera_lock, dataOthers, data_others_lock, exit_event,))
        #p_test.start()
        
        # p_test_serial = Process(target=testReceiveSerial, args=(exit_event,))
        # p_test_serial.start()

        # Wait for the processes to finish
        
        # p_serial.join()
        p_input.join()
        p_plot.join()
        #p_print.join()
        
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        exit_event.set()
        
        # p_serial.join()
        p_input.join()
        p_plot.join()
        #p_print.join()
        if p_input.is_alive() & p_plot.is_alive() :
            print("Warning: processes did not terminate correctly")
        else:
            print("Process terminated correctly")
            print("HUB closed")
        
        ############################ Test ################################
        
        # p_test_serial.join()
        # if p_test_serial.is_alive():
        #     print("Warning: processes did not terminate correctly")
        # else:
        #     print("Process terminated correctly")
        #     print("HUB closed")
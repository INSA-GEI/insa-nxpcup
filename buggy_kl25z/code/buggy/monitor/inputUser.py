import tkinter as tk
from tkinter import ttk
import multiprocessing as mp

### Constants
# PARAMETERS
CMD_ID_ENGINE = 0x01
CMD_ID_CAMERA_MODE = 0x02
CMD_ID_CAMERA_KP = 0x03
CMD_ID_CAMERA_KI = 0x04
CMD_ID_CAMERA_KD = 0x05
CMD_ID_DIFFERENTIAL_KP = 0x06
CMD_ID_DIFFERENTIAL_KI = 0x07
CMD_ID_DIFFERENTIAL_KDP = 0x08
CMD_ID_SPEED_START = 0x09
CMD_ID_SPEED_LIMIT = 0x0A
CMD_ID_SPEED_TURN = 0x0B
# WATCH
CMD_ID_CAMERA_FAR_DATA = 0x0C
CMD_ID_CAMERA_FAR_DATA_DIFF = 0x0D
CMD_ID_CAMERA_FAR_OTHERS = 0x0E
CMD_ID_CAMERA_FAR_NUM_BORDERS = 0x0F
CMD_ID_CAMERA_NEAR_DATA = 0x10
CMD_ID_CAMERA_NEAR_DATA_DIFF = 0x11
CMD_ID_CAMERA_NEAR_OTHERS = 0x12
CMD_ID_CAMERA_NEAR_NUM_BORDERS = 0x13
CMD_ID_CAMERA_COMBINED_CENTER = 0x14        # Not used
CMD_ID_SPEED = 0x15
CMD_ID_SERVO_ANGLE = 0x16
CMD_ID_STOP_WATCH = 0x17

def inputUser(inputQueue, exit_event):
    def buildCMD(cmd_id, data = [0,0]) -> list:
        cmd = [cmd_id]
        cmd.append(data[0])
        cmd.append(data[1])
        cmd.append(cmd[0] ^ cmd[1] ^ cmd[2])
        return cmd
    ### Functions for watching data ##############################################
    # Init defaut watch choice
    choice_maked = {
        "Objet": "Camera Far",
        "Watch": "Data"
    }

    def update_choice(*args):   
        choice_maked["Objet"] = camera_choice_var.get()
        choice_maked["Watch"] = watch_choice_var.get()
    
    def summitWatch():
        cmd = 0
        if choice_maked["Objet"] == "Camera Near":
            if choice_maked["Watch"] == "Data":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_DATA)
                #print(buildCMD(CMD_ID_CAMERA_NEAR_DATA, ACTIVATE))
            elif choice_maked["Watch"] == "Data Diff":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_DATA_DIFF)
            elif choice_maked["Watch"] == "NumberEdge":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_NUM_BORDERS)
            elif choice_maked["Watch"] == "Others":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_OTHERS)
        if choice_maked["Objet"] == "Camera Far":
            if choice_maked["Watch"] == "Data":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_DATA)
            elif choice_maked["Watch"] == "Data Diff":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_DATA_DIFF)
            elif choice_maked["Watch"] == "NumberEdge":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_NUM_BORDERS)
            elif choice_maked["Watch"] == "Others":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_OTHERS)
        if choice_maked["Objet"] == "Speed":
            cmd = buildCMD(CMD_ID_SPEED)
        if choice_maked["Objet"] == "Servo":
            cmd = buildCMD(CMD_ID_SERVO_ANGLE)
        if choice_maked["Objet"] == "Stop":
            cmd = buildCMD(CMD_ID_STOP_WATCH)
        inputQueue.put(cmd)
    
    ### Functions for changing parameters ###################################
    def retrieve_input():
        input_value = entry.get()
        print(input_value)    
    
    def startButton_pressed():
        if startButton["text"] == 'Start Engine' :
            inputQueue.put(buildCMD(CMD_ID_ENGINE, [0, 1]))
            print("Engine started")
            startButton['text'] = 'Stop Engine' 
        elif startButton["text"] == 'Stop Engine' :
            inputQueue.put(buildCMD(CMD_ID_ENGINE, [0, 0]))
            print("Engine stopped")
            startButton['text'] = 'Start Engine'
        

    ### Configure GUI ######################################################
    root = tk.Tk()

    # Set window size
    root.geometry('400x300')  # Width x Height

    # Dropdown list for choosing what camera to watch
    label_camera_choice = tk.Label(root, text="Select what you want to watch")
    label_camera_choice.grid(column=0, row=0)  
    camera_choice_var = tk.StringVar(root)
    camera_choice_var.trace_add('write', update_choice)  # Use trace_add instead of trace
    camera_choices = ['Camera Far', 'Camera Near', 'Speed', 'Servo', 'Stop']
    dropdown_camera = tk.OptionMenu(root, camera_choice_var, *camera_choices)
    dropdown_camera.grid(column=0, row=1)  # Place in column 1

    # Dropdown list
    label_watch_choice = tk.Label(root, text="Select detail of data (for camera only)")
    label_watch_choice.grid(column=0, row=2) 
    watch_choice_var = tk.StringVar(root)
    watch_choice_var.trace_add('write', update_choice)  # Use trace_add instead of trace
    watch_choices = ['Data', 'Data Diff', 'Others', 'NumberEdge', 'None']
    dropdown_watch = tk.OptionMenu(root, watch_choice_var, *watch_choices)
    dropdown_watch.grid(column=0, row=3)  # Place in column 1

    button = tk.Button(root, text="Submit", command=summitWatch)
    button.grid(column=0, row=4)

    ### Changing parameters
    label = tk.Label(root, text="Enter a value")
    label.grid(column=3, row=0)

    entry = tk.Entry(root)
    entry.grid(column=3, row=1)

    button = tk.Button(root, text="Submit", command=retrieve_input)
    button.grid(column=3, row=2)

    # Toggle Start/ Stop Engine button
    startButton = tk.Button(root, text="Start Engine", command=startButton_pressed)
    startButton.grid(column=3, row=3)
    
    

    # Add a separator
    separator = ttk.Separator(root, orient='vertical')
    separator.grid(column=1, row=0, rowspan=10, sticky='ns')

    separator2 = ttk.Separator(root, orient='vertical')
    separator2.grid(column=2, row=0, rowspan=10, sticky='ns')
    try :
        root.mainloop()
        exit_event.set()
        print("Exiting inputUser") 
    except exit_event.is_set():
        print("Exiting inputUser")    

def test_inputUser(inputQueue):
    print("Start Test")
    try:
        while True:
            if not inputQueue.empty():
                command = inputQueue.get()
                print(command)
    except KeyboardInterrupt:
        print("Exiting test")

if __name__ == "__main__":
    inputQueue = mp.Queue()
    #p_main = mp.Process(target=watch, args=(inputQueue, ))

    p_input = mp.Process(target=inputUser, args=(inputQueue, ))
    p_input.start()

    p_output = mp.Process(target=test_inputUser, args=(inputQueue, ))
    p_output.start()
    try:
        # Wait for both processes to finish
        p_input.join()
        p_output.join()
    except KeyboardInterrupt:
        # If the main process receives a KeyboardInterrupt (Ctrl+C), it sets the exit_event.
        # This signals the subprocesses to exit their loops and finish execution.
        p_input.join()
        p_output.join()
        if p_input.is_alive() & p_output.is_alive():
            print("Warning: process did not terminate correctly")
        else:
            print("Process terminated correctly")
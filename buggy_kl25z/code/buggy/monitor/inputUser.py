import tkinter as tk
from tkinter import ttk
import multiprocessing as mp

### Constants
# PARAMETERS
CMD_ID_ENGINE = 0x01
CMD_ID_CAMERA_MODE = 0x02   # Not used
CMD_ID_CAMERA_KP = 0x03
CMD_ID_CAMERA_KI = 0x04     # Not used
CMD_ID_CAMERA_KD = 0x05
CMD_ID_DIFFERENTIAL_KP = 0x06
CMD_ID_DIFFERENTIAL_KI = 0x07
CMD_ID_DIFFERENTIAL_KDP = 0x08
CMD_ID_SPEED_START = 0x09
CMD_ID_SPEED_TARGET = 0x0A
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

def inputUser(inputQueue, outputMethod, exit_event):
    def buildCMD(cmd_id, data = [0,0]) -> list:
        cmd = [cmd_id]
        cmd.append(data[0])
        cmd.append(data[1])
        cmd.append(cmd[0] ^ cmd[1] ^ cmd[2])
        return cmd

    ### Functions for watching data ##############################################
    # Init defaut watch choice
    watch_choice_maked = {
        "Objet": "Camera Far",
        "Watch": "Data"
    }

    def update_watch_choice(*args):   
        watch_choice_maked["Objet"] = camera_choice_var.get()
        watch_choice_maked["Watch"] = watch_choice_var.get()
    
    def summitWatch():
        cmd = 0
        if watch_choice_maked["Objet"] == "Camera Near":
            if watch_choice_maked["Watch"] == "Data":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_DATA)
                #print(buildCMD(CMD_ID_CAMERA_NEAR_DATA, ACTIVATE))
            elif watch_choice_maked["Watch"] == "Data Diff":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_DATA_DIFF)
            elif watch_choice_maked["Watch"] == "NumberEdge":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_NUM_BORDERS)
            elif watch_choice_maked["Watch"] == "Others":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_OTHERS)
        if watch_choice_maked["Objet"] == "Camera Far":
            if watch_choice_maked["Watch"] == "Data":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_DATA)
            elif watch_choice_maked["Watch"] == "Data Diff":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_DATA_DIFF)
            elif watch_choice_maked["Watch"] == "NumberEdge":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_NUM_BORDERS)
            elif watch_choice_maked["Watch"] == "Others":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_OTHERS)
        if watch_choice_maked["Objet"] == "Speed":
            cmd = buildCMD(CMD_ID_SPEED)
        if watch_choice_maked["Objet"] == "Servo":
            cmd = buildCMD(CMD_ID_SERVO_ANGLE)
        if watch_choice_maked["Objet"] == "Stop":
            cmd = buildCMD(CMD_ID_STOP_WATCH)
        # Send command to the queue
        inputQueue.put(cmd)
    
    ### Functions for changing parameters ###################################
    param_choice_maked = {
        "Parameter": 0
    }

    def update_param_choice(*args):
        param_choice_maked["Parameter"] = param_choice_var.get()

    def retrieve_input():
        cmd = 0
        if param_choice_maked["Parameter"] == 0:
            print("No parameter selected")
            return
        input_value = entryParam.get()
        if input_value == "":
            print("No input value")
            return
        #if input_value.isnumeric() == False:
        #    print("Invalid input value, must be a number")
        #    return
        if param_choice_maked["Parameter"] == "Camera Mode":
            print("Camera Mode not used (use only mode 2)")
            #input_value = int(input_value) 
            #if input_value > 0 and input_value < 5:
                #cmd = buildCMD(CMD_ID_CAMERA_MODE, [0, input_value])
                #print("Camera Mode updated: ", input_value)
            #else:
                #print("Invalid value for Camera Mode")
        elif param_choice_maked["Parameter"] == "Camera KP":
            print("Camera KP updated: ", float(input_value))
            input_value = round(float(input_value)*100, 2)
            input_value = int(input_value)
            cmd = buildCMD(CMD_ID_CAMERA_KP, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Camera KI":
            print("Camera KI not used")
            #print("Camera KI updated: ", float(input_value))
            #input_value = round(float(input_value)*100, 2)
            #print(input_value)
            #input_value = int(input_value)
            #cmd = buildCMD(CMD_ID_CAMERA_KI, [input_value & 0xFF00, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Camera KD":
            print("Camera KD updated: ", float(input_value))
            input_value = float(input_value)*100
            input_value = int(input_value)
            cmd = buildCMD(CMD_ID_CAMERA_KD, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Differential KP":
            print("Differential KP updated: ", float(input_value))
            input_value = float(input_value)*100
            input_value = int(input_value)
            cmd = buildCMD(CMD_ID_DIFFERENTIAL_KP, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Differential KI":
            print("Differential KI updated: ", float(input_value))
            input_value = float(input_value)*100
            input_value = int(input_value)
            cmd = buildCMD(CMD_ID_DIFFERENTIAL_KI, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Differential KDP":
            print("Differential KDP updated: ", float(input_value))
            input_value = float(input_value)*100
            input_value = int(input_value)
            cmd = buildCMD(CMD_ID_DIFFERENTIAL_KDP, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Speed Start":
            input_value = int(input_value)
            print("Speed Start updated: ", input_value)
            cmd = buildCMD(CMD_ID_SPEED_START, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Speed Target":
            input_value = int(input_value)
            print("Speed Target updated: ", input_value)
            cmd = buildCMD(CMD_ID_SPEED_TARGET, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])
        elif param_choice_maked["Parameter"] == "Speed Turn":
            input_value = int(input_value)
            print("Speed Turn updated: ", input_value)
            cmd = buildCMD(CMD_ID_SPEED_TURN, [(input_value & 0xFF00) >> 8, input_value & 0x00FF])

        # Send command to the queue
        inputQueue.put(cmd)    
    
    def startButton_pressed():
        if startButton["text"] == 'Start Engine' :
            inputQueue.put(buildCMD(CMD_ID_ENGINE, [0, 0xAA]))
            print("Engine started")
            startButton['text'] = 'Stop Engine' 
        elif startButton["text"] == 'Stop Engine' :
            inputQueue.put(buildCMD(CMD_ID_ENGINE, [0, 0x55]))
            print("Engine stopped")
            startButton['text'] = 'Start Engine'
        
    ### Functions for exiting ################################################
    def on_exit():
        exit_event.set()
        root.destroy()
        print("Exiting inputUser") 

    ### Configure GUI ######################################################
    root = tk.Tk()

    # Set window size
    root.geometry('480x250')  # Width x Height

    # Dropdown list for choosing what camera to watch
    label_camera_choice = tk.Label(root, text="Select what you want to watch")
    label_camera_choice.grid(column=0, row=0)  
    camera_choice_var = tk.StringVar(root)
    camera_choice_var.trace_add('write', update_watch_choice)  # Use trace_add instead of trace
    camera_choices = ['Camera Far', 'Camera Near', 'Speed', 'Servo', 'Stop']
    dropdown_camera = tk.OptionMenu(root, camera_choice_var, *camera_choices)
    dropdown_camera.grid(column=0, row=1)  # Place in column 1

    # Dropdown list
    label_watch_choice = tk.Label(root, text="Select detail of data (for camera only)")
    label_watch_choice.grid(column=0, row=2) 
    watch_choice_var = tk.StringVar(root)
    watch_choice_var.trace_add('write', update_watch_choice)  
    watch_choices = ['Data', 'Data Diff', 'Others', 'NumberEdge', 'None']
    dropdown_watch = tk.OptionMenu(root, watch_choice_var, *watch_choices)
    dropdown_watch.grid(column=0, row=3)  # Place in column 1

    button = tk.Button(root, text="Submit", command=summitWatch)
    button.grid(column=0, row=4)

    ### Changing parameters
    label = tk.Label(root, text="Select a parameter to change")
    label.grid(column=3, row=0)
    param_choice_var = tk.StringVar(root)
    param_choice_var.trace_add('write', update_param_choice)  
    param_choices = ['Camera Mode', 'Camera KP', 'Camera KI', 'Camera KD', 'Differential KP', 'Differential KI', 'Differential KDP', 'Speed Start', 'Speed Target', 'Speed Turn']
    dropdown_param = tk.OptionMenu(root, param_choice_var, *param_choices)
    dropdown_param.grid(column=3, row=1)  # Place in column 3

    entryParam = tk.Entry(root)
    entryParam.grid(column=3, row=2)

    button = tk.Button(root, text="Submit", command=retrieve_input)
    button.grid(column=3, row=3)

    label_guide_cammode = tk.Label(root, text="Camera mode: 1 to 4")
    label_guide_cammode.grid(column=3, row=4)
    label_guide_gain = tk.Label(root, text="Gain: float, max 655.35")
    label_guide_gain.grid(column=3, row=5)
    label_guide_speed = tk.Label(root, text="Speed: int, max 65535 (mm/s)")
    label_guide_speed.grid(column=3, row=6)

    # Toggle Start/ Stop Engine button
    startButton = tk.Button(root, text="Start Engine", command=startButton_pressed, height=3, width=10)
    startButton.grid(column=1, row=15)
    

    # Add a separator
    separator = ttk.Separator(root, orient='vertical')
    separator.grid(column=1, row=0, rowspan=10, sticky='ns')

    #separator2 = ttk.Separator(root, orient='vertical')
    #separator2.grid(column=2, row=0, rowspan=10, sticky='ns')

    # When windows is closed
    root.protocol("WM_DELETE_WINDOW", on_exit)
    try :
        root.mainloop() 
    except KeyboardInterrupt:
        print("Exiting inputUser")
        

def test_inputUser(inputQueue, exit_event):
    print("Start Test")
    try:
        while not exit_event.is_set():
            if not inputQueue.empty():
                command = inputQueue.get()
                if command != 0 :
                    print(command)
        print("Exiting test")
    except KeyboardInterrupt:
        print("Exiting test")

if __name__ == "__main__":
    inputQueue = mp.Queue()
    outputMethod = mp.Queue()
    exit_event = mp.Event()

    #p_main = mp.Process(target=watch, args=(inputQueue, ))

    p_input = mp.Process(target=inputUser, args=(inputQueue, outputMethod ,exit_event,))
    p_input.start()

    p_output = mp.Process(target=test_inputUser, args=(inputQueue, exit_event,))
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
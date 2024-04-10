import tkinter as tk
from tkinter import ttk

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
CMD_ID_CAMERA_NEAR_DATA = 0x0C
CMD_ID_CAMERA_NEAR_DATA_DIFF = 0x0D
CMD_ID_CAMERA_NEAR_BORDER = 0x0E
CMD_ID_CAMERA_NEAR_CENTER = 0x0F
CMD_ID_CAMERA_FAR_DATA = 0x10
CMD_ID_CAMERA_FAR_DATA_DIFF = 0x11
CMD_ID_CAMERA_FAR_BORDER = 0x12
CMD_ID_CAMERA_FAR_CENTER = 0x13
CMD_ID_CAMERA_COMBINED_CENTER = 0x14        # Not used
CMD_ID_SPEED = 0x15
CMD_ID_SERVO_ANGLE = 0x16
CMD_ID_STOP_WATCH = 0x17

def inputUser(inputQueue):
    # Init defaut watch choice
    choice_maked = {
        "Objet": "Camera Far",
        "Watch": "Data"
    }
    def buildCMD(cmd_id, data = [0,0]) -> list:
        cmd = [cmd_id]
        cmd.append(data[0])
        cmd.append(data[1])
        cmd.append(cmd[0] ^ cmd[1] ^ cmd[2])
        return cmd


    def retrieve_input():
        input_value = entry.get()
        print(input_value)

    def update_choice(*args):   
        choice_maked["Objet"] = camera_choice_var.get()
        choice_maked["Watch"] = watch_choice_var.get()
    
    def summitWatch():
        cmd = 0
        if choice_maked["Objet"] == "Camera Far":
            if choice_maked["Watch"] == "Data":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_DATA)
                #print(buildCMD(CMD_ID_CAMERA_NEAR_DATA, ACTIVATE))
            elif choice_maked["Watch"] == "Data Diff":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_DATA_DIFF)
            elif choice_maked["Watch"] == "RoadMiddle":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_CENTER)
            elif choice_maked["Watch"] == "NumberEdge":
                cmd = buildCMD(CMD_ID_CAMERA_NEAR_BORDER)
        if choice_maked["Objet"] == "Camera Near":
            if choice_maked["Watch"] == "Data":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_DATA)
            elif choice_maked["Watch"] == "Data Diff":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_DATA_DIFF)
            elif choice_maked["Watch"] == "RoadMiddle":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_CENTER)
            elif choice_maked["Watch"] == "NumberEdge":
                cmd = buildCMD(CMD_ID_CAMERA_FAR_BORDER)
        if choice_maked["Objet"] == "Speed":
            cmd = buildCMD(CMD_ID_SPEED)
        if choice_maked["Objet"] == "Stop":
            cmd = buildCMD(CMD_ID_STOP_WATCH)
        inputQueue.put(cmd)
        
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
    watch_choices = ['Data', 'Data Diff', 'RoadMiddle', 'NumberEdge', 'None']
    dropdown_watch = tk.OptionMenu(root, watch_choice_var, *watch_choices)
    dropdown_watch.grid(column=0, row=3)  # Place in column 1

    button = tk.Button(root, text="Submit", command=summitWatch)
    button.grid(column=0, row=4)

    label = tk.Label(root, text="Enter a value")
    label.grid(column=3, row=0)

    entry = tk.Entry(root)
    entry.grid(column=3, row=1)



    button = tk.Button(root, text="Submit", command=retrieve_input)
    button.grid(column=3, row=2)

    # Add a separator
    separator = ttk.Separator(root, orient='vertical')
    separator.grid(column=1, row=0, rowspan=10, sticky='ns')

    separator2 = ttk.Separator(root, orient='vertical')
    separator2.grid(column=2, row=0, rowspan=10, sticky='ns')

    root.mainloop()

if __name__ == "__main__":
    inputUser()
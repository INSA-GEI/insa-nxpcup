def checkReceivedData(ser):
    if (int.from_bytes(ser.read()) == 0xFF):
        if (int.from_bytes(ser.read()) == 0xFF):
            return True
    return False

def getData(ser):
    i = 0
    data = []
    dataLSB = 0
    dataMSB = 0
    dataLengthMSB = int.from_bytes(ser.read())
    dataLengthLSB = int.from_bytes(ser.read())
    dataLength = int(((dataLengthMSB << 8) + dataLengthLSB)/2)
    
    for i in range(dataLength):
        dataMSB = int.from_bytes(ser.read())
        dataLSB = int.from_bytes(ser.read())
        data.append((dataMSB << 8) + dataLSB)
    return data

def printData(ser):
    if (int.from_bytes(ser.read()) == 0xFF):
        if (int.from_bytes(ser.read()) == 0xFF):
            i = 0
            data = []
            dataLSB = 0
            dataMSB = 0
            id = int.from_bytes(ser.read())
            dataLengthMSB = int.from_bytes(ser.read())
            dataLengthLSB = int.from_bytes(ser.read())
            dataLength = int(((dataLengthMSB << 8) + dataLengthLSB)/2)
            
            for i in range(dataLength):
                dataMSB = int.from_bytes(ser.read())
                dataLSB = int.from_bytes(ser.read())
                data.append((dataMSB << 8) + dataLSB)
            print(data)
            print("\n")

def printAllAsInteger(ser):
    dataMSB = int.from_bytes(ser.read())
    dataLSB = int.from_bytes(ser.read())
    data = (dataMSB) 
    #if (dataMSB > 0):
    print(" | " + str(data) + "", end = "")
    #else:
        #print(" | " + str(dataLSB) + "", end = "")
    
def printDataRaw(ser):
    data = int.from_bytes(ser.read())
    print(" | " + str(data) + "", end = "")
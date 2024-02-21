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
    dataLengthLSB = int.from_bytes(ser.read())
    dataLengthMSB = int.from_bytes(ser.read())
    dataLength = int(((dataLengthMSB << 8) + dataLengthLSB)/2)
    
    for i in range(dataLength):
        dataLSB = int.from_bytes(ser.read())
        dataMSB = int.from_bytes(ser.read())
        data.append((dataMSB << 8) + dataLSB)
    return data

def printData(ser):
    i = 0
    data = []
    dataLSB = 0
    dataMSB = 0
    dataLengthLSB = int.from_bytes(ser.read())
    dataLengthMSB = int.from_bytes(ser.read())
    dataLength = int(((dataLengthMSB << 8) + dataLengthLSB)/2)
    
    for i in range(dataLength):
        dataLSB = int.from_bytes(ser.read())
        dataMSB = int.from_bytes(ser.read())
        data.append((dataMSB << 8) + dataLSB)
    print(data)
    print("\n")

def printAllAsInteger(ser):
    dataLSB = int.from_bytes(ser.read())
    dataMSB = int.from_bytes(ser.read())
    print(" | " + str((dataMSB << 8) + dataLSB))
    
def printDataRaw(ser):
    data = int.from_bytes(ser.read())
    print(" | " + str(data))
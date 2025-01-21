import serial
import time


# Function to read serial, check, make and save to file
def readserial(comport, baudrate, timestamp=False):

    ser = serial.Serial(comport, baudrate, timeout=0.1)         # 1/timeout is the frequency at which the port is read

    while True:

        data = ser.readline()

        if data and timestamp:
            timestamp = time.strftime('%d/%m/%Y,%H:%M:%S')
            print(f'{timestamp},{data}')
            with open('cansatdata.csv', 'a', newline="") as file:
                file.writelines(f'{timestamp},{data}\r\n')
                file.flush()
            file.close()
        elif data:
            print(data)
            


if __name__ == '__main__':

    readserial('COM5', 115200, True)



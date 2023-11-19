
#pip install pyserial

#from symbol import pass_stmt
import serial
import time

class serialCom:
    def __init__(self,port, baud_rate):
        print("Port connection: " + port + " Baud rate: " + str(baud_rate))
        self.source = serial.Serial(
    port=port, baudrate=baud_rate, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

    def serial_loop(self):
        while True:
            try:
                self.line = self.source.readline()#.decode('utf-8')
                print(self.line)

            except KeyboardInterrupt:
                print("closing loop")
                self.source.close()

            num = input('Enter the integer:')
            return self.write_read(num)
            
    def write_read(self, num):
        self.source.write(num,'utf-8')
        time.sleep(0.05)
        data=self.source.readline()
        return data



if __name__ == '__main__':
    port = "COM8"
    baud_rate = 512000
    serialCom = serialCom(port, baud_rate)
    serialCom.serial_loop()
    
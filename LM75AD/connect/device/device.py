
import sys
import glob
import serial
from serial.serialutil import SerialTimeoutException

class WrongFirmware(Exception):

    def __init__(self):
        Exception.__init__(self, "Wrong Firmware")

class BoardNotConnected(Exception):

    def __init__(self):
        Exception.__init__(self, "Board Not Connected")

class Board:

    def __init__(self,serial_name='COM2', baud_rate=9600):
        super(Board,self).__init__()

        self.serial_name = serial_name
        self.baud_rate = baud_rate
        self.serial_port = None
        self.is_connected = False

    def connect(self):
        self.is_connected = False
        try:
            self.serial_port = serial.Serial(self.serial_name, self.baud_rate, timeout=0.02)
            if self.serial_port.isOpen():
                self._reset()
                self.is_connected = True
            else:
                raise BoardNotConnected()
        except Exception as exception:
            self.serial_port = None
            raise exception

    def disconnect(self):
        if self.is_connected:
            try:
                if self.serial_port is not None:
                    self.is_connected = False
                    self.serial_port.close()
                    del self.serial_port
            except serial.SerialException:
                raise "Error closing the port"

    def readline(self):
        return self.serial_port.readline().decode('utf-8')

    def send_command(self,data):
        if self.is_connected == True:
            self.serial_port.flushInput()
            self.serial_port.flushOutput()
            self.serial_port.write(str.encode(data + "\r\n"))

    def _reset(self):
        self.serial_port.flushInput()
        self.serial_port.flushOutput()
        self.serial_port.write(str.encode("\x18\r\n"))  # Ctrl-x

    def get_ports():
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        return result[::-1]

import sys
import time
from datetime import datetime
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import serial

from gui import gui
from device import device

class DataReceiver(QThread):
    signal_data = pyqtSignal(str)

    def __init__(self, connect):
        super().__init__()
        self.connect = connect
        self.run_flag = True

    def run(self):
        while self.connect.is_connected & self.run_flag:
            data_receiver = self.connect.readline()
            self.signal_data.emit(data_receiver)
            time.sleep(0.01)

    def stop(self):
        self.run_flag = False
        self.connect.is_connected = False
        self.connect.disconnect()

class App(QWidget):
    def __init__(self, *args, **kwargs):
        super(App,self).__init__()

        self.board = None
        self.temp = 0
        self.reload_time = 100
        self.initGui()
        
    def initGui(self):

        self.serial_panel = gui.SerialForm()
        self.canvas = gui.PlotCanvas(self, width=5, height=4, dpi=100, delay=self.reload_time)

        hbox = QHBoxLayout(self)
        hbox.addWidget(self.serial_panel)
        hbox.addWidget(self.canvas)

        self.serial_panel.connected.clicked.connect(self.connect_serial)
        self.serial_panel.disconected.clicked.connect(self.disconect_serial)

    @pyqtSlot(str)
    def show_data_receiver(self,data_receiver):
        if len(data_receiver) != 0:
            self.serial_panel.addDataReceived(data_receiver)
            if data_receiver[0] == ':' :
                data_receiver = data_receiver.replace('\r\n','')
                self.temp = float(data_receiver[1:])

                if self.board != None:
                    if self.board.is_connected == True:
                        delta_time = datetime.now()-self.time_base

                        self.canvas.update_plot(self.temp,delta_time.total_seconds())

    def connect_serial(self):
        try:
            if self.board == None:
                portname = self.serial_panel.port_cb.currentText()
                baudrate = int(self.serial_panel.baud_cb.currentText())
                self.board = device.Board(serial_name=portname,baud_rate=baudrate)
                self.board.connect()
                
                self.thread_serial = DataReceiver(connect=self.board)
                self.thread_serial.signal_data.connect(self.show_data_receiver)
                self.thread_serial.start()
                self.time_base = datetime.now()

                QMessageBox.information(self,"","Connected !")
                self.serial_panel.setText("{}. {}".format(portname,baudrate))
            else:
                QMessageBox.information(self,"","Connected !")
        except Exception as error:
            self.board = None
            QMessageBox.warning(self,"",str(error))

    def disconect_serial(self):
        if self.board != None:
            if self.board.is_connected == True:
                self.board.disconnect()
                self.board = None
                self.thread_serial.stop()
                self.thread_serial = None
                QMessageBox.information(self,"","Disconnected !")
                self.serial_panel.setText("")
        else:
            QMessageBox.information(self,"","Disconnected !")

def main():
    app = QApplication(sys.argv)
    app.setStyle('Fusion')
    my_app = App()
    my_app.show()
    app.exec_()

if __name__ == '__main__':
    main()
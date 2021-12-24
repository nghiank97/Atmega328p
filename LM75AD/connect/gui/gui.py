
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from device.device import Board

import matplotlib
matplotlib.use('Qt5Agg')
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure

class PlotCanvas(FigureCanvas):

    def __init__(self, parent=None, width=5, height=4, dpi=100 ,delay=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)

        self.x_lim = [0,100]
        self.y_lim = [0,200]

        self.axes.set_title("Plot")
        self.axes.set_xlabel("Time")
        self.axes.set_ylabel("Temp")
        self.axes.set_xlim(self.x_lim)
        self.axes.set_ylim(self.y_lim)
        super(PlotCanvas, self).__init__(fig)

        self.xdata = [0]
        self.ydata = [0]

    def update_plot(self,value,time):
        if len(self.xdata) == 100:
            self.ydata=self.ydata[25:]
            self.xdata=self.xdata[25:]

        if self.xdata[-1] > self.x_lim[1]:
            self.x_lim[0]+=50
            self.x_lim[1]+=self.xdata[-1] - self.x_lim[1]+50

        if self.y_lim[1] < value:
            self.y_lim[1]=value+50

        self.ydata.append(value)
        self.xdata.append(time)
        self.axes.cla()
        self.axes.plot(self.xdata, self.ydata, 'b')
        # self.axes.fill_between(self.xdata, self.ydata,color="blue")

        self.axes.set_title("Plot")
        self.axes.set_xlabel("Time")
        self.axes.set_ylabel("Temp")
        self.axes.set_xlim(self.x_lim)
        self.axes.set_ylim(self.y_lim)
        self.draw()


class SerialForm(QWidget):
    def __init__(self,*args,**kwargs):
        super(SerialForm,self).__init__()

        self.port_cb = QComboBox()
        self.port_cb.addItems(Board.get_ports())

        self.baud_cb = QComboBox()
        self.baud_cb.addItems(['2400', '4800', '9600',
                               '14400', '19200', '38400', '56000', '57600', '115200'])
        self.baud_cb.setCurrentText('9600')

        self.connected = QPushButton("LOAD")
        self.disconected = QPushButton("UNLOAD")

        self.data_serial = QTextBrowser()

        self.receivers = QLineEdit()
        self.send = QPushButton("S")
        self.clean = QPushButton("X")
        self.clean.clicked.connect(self.clean_data)
        self.status = QLabel()

        vbox = QVBoxLayout(self)
        hbox = QHBoxLayout()
        hbox.addWidget(self.port_cb)
        hbox.addWidget(self.baud_cb)
        hbox.addWidget(self.connected)
        hbox.addWidget(self.disconected)
        vbox.addLayout(hbox)
        vbox.addWidget(self.data_serial)

        hbox = QHBoxLayout()
        hbox.addWidget(self.receivers)
        hbox.addWidget(self.send)
        hbox.addWidget(self.clean)
        vbox.addLayout(hbox)

        vbox.addWidget(self.status)

    def setText(self,txt):
        self.status.setText(txt)

    def clean_data(self):
        self.data_serial.clear()
    
    def addDataTrasmited(self,txt):
        self.data_serial.append(">>"+txt)

    def addDataReceived(self,txt):
        self.data_serial.append("<<"+txt)

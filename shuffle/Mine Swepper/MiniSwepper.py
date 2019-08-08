import sys

from PyQt5.QtWidgets import *

from MiniSwepperInterface import *

class mywindow(QtWidgets.QMainWindow,Ui_MainWindow):
    def __init__(self):
        super(mywindow, self).__init__()
        self.setupUi(self)

    def mouseDoubleClickEvent(self, event):
        print('double click...')
        self.shuffle()
        self.refreshGrid()



if __name__ == '__main__':

    app = QApplication(sys.argv)
    window = mywindow()
    window.show()
    sys.exit(app.exec())
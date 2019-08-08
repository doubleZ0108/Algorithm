import sys

from PyQt5.QtWidgets import *

from MiniSwepperInterface import *

class mywindow(QtWidgets.QMainWindow,Ui_MainWindow):
    def __init__(self):
        super(mywindow, self).__init__()
        self.setupUi(self)

    '''鼠标双击屏幕事件（非按钮部分）'''
    def mouseDoubleClickEvent(self, event):
        print('double click...')

        # 调用洗牌算法
        self.myshuffle()

        # 更新布局
        self.refreshGrid()



if __name__ == '__main__':

    app = QApplication(sys.argv)
    window = mywindow()
    window.show()
    sys.exit(app.exec())
from random import randint
from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def __init__(self):
        '''
        :param boardSize 棋盘大小(正方形)
        :param mineNum (地雷总数)
        '''
        self._boardSize = 20
        self._mineNum = 50
        self._board = self.grow_board()

    def grow_board(self):
        board = [0 for _ in range(self._boardSize ** 2)]
        '''
        不能用
        board = [[0]*self._boardSize] * self._boardSize
        这样只产生引用, 同一列的元素会一起更改
        '''
        temp = self._mineNum
        for i in range(self._mineNum):
            board[i] = 1
        return board

    def shuffle(self):
        print('shuffle...')
        for i in range(len(self._board) - 1, 0, -1):
            pos = randint(0, i + 1)
            self._board[i], self._board[pos] = self._board[pos], self._board[i]



    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(600, 610)
        MainWindow.setStyleSheet("background-color: rgb(145, 123, 56);")

        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")


        self.buildGrid()


        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 22))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Mine Swepper"))

    def buildGrid(self):
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(0, 0, 600, 600))
        self.gridLayoutWidget.setStyleSheet("background-color: rgb(0, 0, 0);")
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")

        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")

        positions = [(i, j) for i in range(20) for j in range(20)]  # 构造20行20列的格子

        for position, name in zip(positions, self._board):
            button = QtWidgets.QPushButton(str(name))
            button.setStyleSheet("background-color: rgb(160, 160, 160);")
            self.gridLayout.addWidget(button, *position)  # 放到布局里

    def refreshGrid(self):
        print('refresh grid...')


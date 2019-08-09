from random import randint, shuffle
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import  QApplication
import sip


class Ui_MainWindow(object):
    def __init__(self):
        '''
        :param  _boardSize 棋盘大小(正方形)
        :param _mineNum (地雷总数)
        :param  _board 棋盘 (0 =>正常 1 =>地雷)
        :param _position (棋盘各格子位置)
        '''
        self._boardSize = 20
        self._mineNum = 50
        self._board = self.grow_board()
        self._positions = [(i, j) for i in range(20) for j in range(20)]  # 构造20行20列的格子

    '''生成初始棋盘（默认所有雷都在最前面依次排列）'''
    def grow_board(self):
        board = [0 for _ in range(self._boardSize ** 2)]
        for i in range(self._mineNum):
            board[i] = 1
        return board


    '''洗牌算法'''
    def myshuffle(self):
        print('shuffle...')
        for i in range(len(self._board) - 1, 0, -1):
            pos = randint(0, i)
            self._board[i], self._board[pos] = self._board[pos], self._board[i]

        # 也可以使用库函数进行洗牌
        # shuffle(self._board)

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(600, 615)
        MainWindow.setStyleSheet("background-color: rgb(160, 160, 160);")

        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")


        self.buildGrid()        # 生成初始布局


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


    '''生成初始布局'''
    def buildGrid(self):
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(0, 0, 600, 610))
        self.gridLayoutWidget.setStyleSheet("background-color: rgb(0, 0, 0);")

        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)

        # 根据位置和棋盘上的内容构建button
        for position, name in zip(self._positions, self._board):
            button = QtWidgets.QPushButton(str(name))

            if name == 1:   # 雷
                button.setStyleSheet("background-color: rgb(230, 50, 36);")

            else:
                button.setStyleSheet("background-color: rgb(160, 160, 160);")

            self.gridLayout.addWidget(button, *position)  # 放到布局里


    '''更新布局'''
    def refreshGrid(self):
        print('refresh grid...')

        # 获取所有布局中的button
        buttons = self.gridLayoutWidget.findChildren(QtWidgets.QPushButton)
        for button in buttons:
            self.gridLayout.removeWidget(button)
            sip.delete(button)      # 要加这句话，否则容易删完没效果


        for position, name in zip(self._positions, self._board):
            button = QtWidgets.QPushButton(str(name))

            if name == 1:
                button.setStyleSheet("background-color: rgb(230, 50, 36);")
            else:
                button.setStyleSheet("background-color: rgb(160, 160, 160);")

            self.gridLayout.addWidget(button, *position)  # 放到布局里





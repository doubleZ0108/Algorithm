from random import randint

'''扫雷类'''


class MineSweeper(object):
    def __init__(self, boardSize, mineNum):
        '''
        :param boardSize 棋盘大小(正方形)
        :param mineNum (地雷总数)
        '''
        self._boardSize = boardSize
        self._mineNum = mineNum
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

    @property
    def show_board(self):
        for i in range(self._boardSize):
            for j in range(self._boardSize):
                print(self._board[i * self._boardSize + j], end=' ')
            print()

    def shuffle(self):
        for i in range(len(self._board) - 1, 0, -1):
            pos = randint(0, i + 1)
            self._board[i], self._board[pos] = self._board[pos], self._board[i]


def main():
    boardSize = 20
    mineNum = 50

    minesweeper = MineSweeper(boardSize, mineNum)
    print(minesweeper.show_board)
    minesweeper.shuffle()
    print(minesweeper.show_board)


if __name__ == "__main__":
    main()

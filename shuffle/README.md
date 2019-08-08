# 洗牌(随机)算法

[TOC]

## 基本思想

把牌放到一个数组中, 每次取两张牌交换位置, 随机k次即可, 但是k取多大呢? 等于牌的总数就真的公平了🐎

## 公平性

洗牌的结果是所有元素的一个排列, 一副牌有n个元素, 最终的排列有n!种可能性; 公平的洗牌算法应该能等概率的给出这n!个排列🀄️的一个

------

每个元素都能等概率的出现在每一个位置, 或者说每一个位置都能等概率的放置每个元素



## 暴力算法

生成n个元素的排列, 共n!个, 然后随机选择一个

### 评价

- 算法能保证公平性
- 但算法时间复杂度为`O(n!)`, 时间上不可容忍



## Knuth洗牌算法

### 算法思想

i从后往前, 每次随机选择[0 ... i]之间的一个下标, 交换arr[i]和这个下标的元素

### 代码实现

```c++
for (int i=arr.size()-1;i>0;--i)
{
  swap(arr[i], arr[rand() % (i+1)]);
}
```

### 算法分析

以5个元素为例, 模拟算法的执行过程, 对于每一步, 计算概率值

- 初始时刻

  ![](https://mmbiz.qpic.cn/mmbiz_png/j4elhCicRBPdfILW5XmibyDv1Iy0b1vx27sSGQZlf01EaxzTXhEc1Ovwnibzic2opxczTvIkzIqCyP20TxS6wP3Uwg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

- 在5⃣️个元素中选择一个和最后的5交换, 假设随机选了2

  则**2出现在最后一个位置的概率是: $\frac{1}{5}$** (因为这次是从5个元素中随便选的)

  ![](https://mmbiz.qpic.cn/mmbiz_png/j4elhCicRBPdfILW5XmibyDv1Iy0b1vx27wKiaoiaJUAmdubk9LnQCbSEHZQUCMVEMWIRL1Hc3cXzSa4J1bu3Oaj1A/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

- 在前4⃣️个元素中随机选一个, 放到倒数第二的位置, 假设随机选了3

  **则3出现在倒数第二位置的概率是: $\frac{4}{5}*\frac{1}{4}=\frac{1}{5}$** (第一次没选到3 ->  $\frac{4}{5}$概率, 第二次在四个数中选到3 -> $\frac{1}{4}$概率)

  ![](https://mmbiz.qpic.cn/mmbiz_png/j4elhCicRBPdfILW5XmibyDv1Iy0b1vx270cjvW1Wia4ichzl7UuNBkHhQcxMqnrZpr5teEO8iaDnPgryvy7RicnX8oA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

- 再在前3⃣️个数中随机选一个, 放到中间的位置, 假设随机选了1

  **则1出现在中间位置的概率是: $\frac{4}{5}*\frac{3}{4}*\frac{1}{3}=\frac{1}{5}$**  (第一次没选到1 ->  $\frac{4}{5}$概率, 第二次没选到1 -> $\frac{3}{4}$概率, 第三次在三个数中选到1 -> $\frac{1}{3}$)

  ![](https://mmbiz.qpic.cn/mmbiz_png/j4elhCicRBPdfILW5XmibyDv1Iy0b1vx27m9RUFXprBWKPs0FvL1gp3uXRG8zCP8DIFiba9peGHMyaycf5RC9Rzqg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

  ![](https://mmbiz.qpic.cn/mmbiz_png/j4elhCicRBPdfILW5XmibyDv1Iy0b1vx27RUAoia9wGibOauY652cGT7NbLoMibk2OghDCVMopxDEjGattQWBYnBdAA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

- ......

- 以此类推, 每个元素出现在每一个位置的概率都是$\frac{1}{5}$

- 将其推广到n个数也是成立的

### 时间复杂度

`O(n)`



## 算法应用

### 扫雷生成随机棋盘

- 将二维棋盘看作👀是一维的一横行
- 先把k个雷从开始出接次排列
- 使用Knuth洗牌算法执行一次
- 得到随机棋盘

#### PyQt实现

- 棋盘为 20 * 20, 雷总数为50个
- 雷用数字1 和 红色背景标示
- 初始时刻所有雷从最前面依次排开
- 双击屏幕空白位置(非按钮), 进行一次洗牌

##### 代码实现

**生成初始棋盘**

棋盘物理上是一维的, 但是当作二维的样子使用

```python
'''生成初始棋盘（默认所有雷都在最前面依次排列）'''
def grow_board(self):
  board = [0 for _ in range(self._boardSize ** 2)]
  for i in range(self._mineNum):
    board[i] = 1
    return board
```

**生成初始布局**

- 定义栅格布局, 并定义20 * 20个格子
- 初始时根据棋盘添加400个button
- 根据board此处的值设定button的样式

```python
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
```

**双击界面**

- 调用洗牌算法
- 更新布局

**更新布局**

- 删掉布局中所有按钮
- 重新按照board添加

```python
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
```



##### 初始时刻

![屏幕快照 2019-08-08 21.57.19.png](https://upload-images.jianshu.io/upload_images/12014150-47021ead71d4ff5b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 洗牌

![Mine-Sweeper_1.gif](https://upload-images.jianshu.io/upload_images/12014150-fa28f8b9149dc76f.gif?imageMogr2/auto-orient/strip)

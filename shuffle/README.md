# 洗牌(随机)算法

## 目录

- [基本思想](#基本思想)
- [公平性](#公平性)
- [暴力算法](#暴力算法)
  * [评价](#评价)
- [Knuth洗牌算法](#Knuth洗牌算法)
  * [算法思想](#算法思想)
  * [代码实现](#代码实现)
  * [算法分析](#算法分析)
  * [时间复杂度](#时间复杂度)
- [算法应用](#算法应用)
  * [扫雷生成随机棋盘](#扫雷生成随机棋盘)
    + [PyQt实现](#PyQt实现)
      - [代码实现](#1代码实现)
      - [初始时刻](#1初始时刻)
      - [洗牌](#1洗牌)
    + [HTML + JavaScript 实现](#HTML+JavaScript实现)
      - [代码实现](#代码实现)
      - [初始时刻](#2初始时刻)
      - [洗牌](#2洗牌)

<a name="基本思想"></a>

## 基本思想

把牌放到一个数组中, 每次取两张牌交换位置, 随机k次即可, 但是k取多大呢? 等于牌的总数就真的公平了🐎

<a name="公平性"></a>

## 公平性

洗牌的结果是所有元素的一个排列, 一副牌有n个元素, 最终的排列有n!种可能性; 公平的洗牌算法应该能等概率的给出这n!个排列🀄️的一个

------

每个元素都能等概率的出现在每一个位置, 或者说每一个位置都能等概率的放置每个元素



<a name="暴力算法"></a>

## 暴力算法

生成n个元素的排列, 共n!个, 然后随机选择一个

<a name="评价"></a>

### 评价

- 算法能保证公平性
- 但算法时间复杂度为`O(n!)`, 时间上不可容忍



<a name="Knuth洗牌算法"></a>

## Knuth洗牌算法

<a name="算法思想"></a>

### 算法思想

i从后往前, 每次随机选择[0 ... i]之间的一个下标, 交换arr[i]和这个下标的元素

<a name="代码实现"></a>

### 代码实现

```c++
for (int i=arr.size()-1;i>0;--i)
{
  swap(arr[i], arr[rand() % (i+1)]);
}
```

<a name="算法分析"></a>

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

<a name="时间复杂度"></a>

### 时间复杂度

`O(n)`



<a name="算法应用"></a>

## 算法应用

<a name="扫雷生成随机棋盘"></a>

### 扫雷生成随机棋盘

- 将二维棋盘看作👀是一维的一横行
- 先把k个雷从开始出接次排列
- 使用Knuth洗牌算法执行一次
- 得到随机棋盘

<a name="PyQt实现"></a>

#### PyQt实现

- 棋盘为 20 * 20, 雷总数为50个
- 雷用数字1 和 红色背景标示
- 初始时刻所有雷从最前面依次排开
- 双击屏幕空白位置(非按钮), 进行一次洗牌

<a name="1代码实现"></a>

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

<a name="1初始时刻"></a>

##### 初始时刻

![屏幕快照 2019-08-08 21.57.19.png](https://upload-images.jianshu.io/upload_images/12014150-47021ead71d4ff5b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<a name="1洗牌"></a>

##### 洗牌

![Mine-Sweeper_1.gif](https://upload-images.jianshu.io/upload_images/12014150-fa28f8b9149dc76f.gif?imageMogr2/auto-orient/strip)



<a name="HTML+JavaScript实现"></a>

#### HTML + JavaScript 实现

<a name="2代码实现"></a>

##### 代码实现

**生成初始棋盘**

```javascript
window.onload = function () {
  //初始化棋盘数组
  let i=0;
  for(;i<mineNum;++i){
    board[i] = 1;
  }
  for(;i<board.length;++i){
    board[i] = 0;
  }

  //根据棋盘数组构建表格
  buildTable()
}
```

**构建表格 & 更新表格**

- 构建一个table标签🏷️
- 首先清空table中的内容
- 创建boardSize行, 每行创建boardSize个表格项
  - 表格项的值为棋盘上对应的值
  - 如果该处为雷，则将表格项的类设置为mine; 否则为no-mine

```html
<table id="mine-table" border="1">

</table>
```

```javascript
function buildTable() {
  let mine_table = document.getElementById('mine-table');
  mine_table.innerHTML = '';      //清空table内容

  for(let i=0;i<boardSize;++i){
    let row = document.createElement('tr');     //创建一个行元素
    for(let j=0;j<boardSize;++j){
      let elem = document.createElement('td');    //在行中创建boardSize个表格项

      let value = board[i*boardSize + j];
      elem.innerText = String(value);         //表格项的值为棋盘上对应的值
      if (value===1){     //如果该处为雷，则将表格项的类设置为mine
        elem.className = 'mine';
      }else{
        elem.className = 'no-mine';
      }

      row.appendChild(elem);
    }
    mine_table.appendChild(row);
  }

}
```

<a name="2初始时刻"></a>

##### 初始时刻

![屏幕快照 2019-08-09 09.37.26.png](https://upload-images.jianshu.io/upload_images/12014150-99bbb54178c05cab.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<a name="2洗牌"></a>

##### 洗牌

![Mine Sweeper_js.gif](https://upload-images.jianshu.io/upload_images/12014150-d55ba4fb3268cc37.gif?imageMogr2/auto-orient/strip)

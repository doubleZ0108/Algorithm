# AssignmentOne2019_Programming
### 基本信息
- 姓名: 张喆
- 学号: 1754060
- 上课时间: 周一 5-6 节
- 联系方式: doubleZ0108@163.com 

### 问题描述
一只青蛙一次可以跳上 1 级台阶，也可以跳上 2 级台阶。求该青蛙跳上 1 个 n级的台阶总共有多少种跳法。

### 问题分析

假设总共有10级台阶，则只差一步就走到第10级台阶的方法只有两种：
1. 从第9级走一步到第10级
2. 从第8级一下走两步到第十级。

若假设从0到9级有X种方法，从0到8级有Y中方法，则走到第10级的总方法为 `X+Y`

则令F(N)表示从1跳到n级的跳法数, 则`F(N)=F(N-1)+F(N-2)`

### 核心算法
**动态规划**
> 将过程分成若干个互相联系的阶段，在它的每一阶段都需要作出决策，从而使整个过程达到最好的活动效果。当然，各个阶段决策的选取不是任意确定的，它依赖于当前面临的状态，又影响以后的发展，当各个阶段决策确定后，就组成一个决策序列，因而也就确定了整个过程的一条活动路线。

**最优子结构**

由`F(N)=F(N-1)+F(N-2)`得，F(N-1)、F(N-2)是F(N)的**最优子结构**

**边界条件**

1. 只有一级台阶时只有一种跳法
2. 有两级台阶时有两种跳法:一步一步跳、一次跳到第二级
3. 零级台阶的时候特殊定义为0

**状态转移公式**

F(N)=F(N-1)+F(N-2)

### 算法设计
- 蛮力法(未以代码方式呈现)

	利用排列组合的思想, 用一个多层嵌套的循环遍历出所有的可能性, 每遍历出一个组合,让计数器加一

- 普通递归法

	直接利用状态转移公式和边界条件设计递归结构

```
/*递归算法求解跳台阶问题*/
long long JumpStairs_brutal(int n)
{
	if (n == 0) { return 0; }
	else if (n == 1) { return 1; }
	else if (n == 2) { return 2; }
	else 
		{ return JumpStairs_brutal(n - 1) + JumpStairs_brutal(n - 2); }
}
```

- 备忘录递归法

在普通递归方法的递归调用树中有大量的重复节点,如下图所示
![备忘录算法的递归调用树](https://upload-images.jianshu.io/upload_images/12014150-51645c885211b711.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

因此可以设置一个静态的图结构, 将N的值作为索引, F(N)的值作为对象存储

在递归调用的过程中, 先在静态表中查找该值是否曾经计算过(静态图中是否存储过): 如果图中存储过该值,则可直接返回对象值,节省重复计算浪费的时间; 否则也只需计算一次对象的值并将其加入到备忘录中

```
/*在递归算法中增加备忘录*/
long long JumpStairs_map(int n)
{
	static map<int, long long> mymap;	//用静态图储存已经计算出来的值

	if (n == 0) { return 0; }
	else if (n == 1) { return 1; }
	else if (n == 2) { return 2; }

	if (mymap.count(n))	//在递归过程中, 如果静态图中已经存储过该值直接返回
	{
		return mymap[n];
	}
	else
	{
		long long value= JumpStairs_map(n - 1) + JumpStairs_map(n - 2);
		mymap[n] = value;	//将新值记录进静态图
		return value;
	}
}
```

- 动态规划法

由于F(N)只与F(N-1)和F(N-2)有关, 也就是说每一项都只与前面的两项有关, 因此可以设置两个变量用于依次储存相邻的两个元素, 只通过这两个变量就可以计算出下一个变量

计算出下一个变量之后再将设置的两个变量依次向后挪一位达到计算下一项的目的

```
/*迭代算法求解跳台阶问题*/
long long JumpStairs_loop(int n)
{
	if (n == 0) { return 0; }
	else if (n == 1) { return 1; }
	else if (n == 2) { return 2; }

	long long Fn, Fn_1 = 1, Fn_2 = 2;
	for (int i = 3; i <= n; ++i)
	{
		Fn = Fn_1 + Fn_2;
		Fn_1 = Fn_2;
		Fn_2 = Fn;
	}
	return Fn;
}
```

### 功能测试
![数据量_3](https://upload-images.jianshu.io/upload_images/12014150-23c5dc3557637988.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![数据量_5](https://upload-images.jianshu.io/upload_images/12014150-013a4082f3b8c5e9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![数据量_10](https://upload-images.jianshu.io/upload_images/12014150-8ef2416e0ba68d53.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 边界测试
![数据量_0](https://upload-images.jianshu.io/upload_images/12014150-fffd99fedaab9a88.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![数据量_1](https://upload-images.jianshu.io/upload_images/12014150-97441efa94b6f2a4.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![数据量_2](https://upload-images.jianshu.io/upload_images/12014150-7858741fff0cbab6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 性能测试
![数据量_40](https://upload-images.jianshu.io/upload_images/12014150-1a3855a4e24b622f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

数据量为40的时候, 蛮力算法耗时已经很长
![数据量_50](https://upload-images.jianshu.io/upload_images/12014150-c59196b81ea4b3d2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

数据量为90的时候, 蛮力算法长时间无法求解
![数据量_90](https://upload-images.jianshu.io/upload_images/12014150-6a8ac44fc53bce54.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 复杂度分析
- 蛮力法

	指数级别

- 普通递归法

  要计算出F(N),就要先得到F(N-1)和F(N-2);要计算F(N-1)就要先得到F(N-2)和F(N-3)...以此类推可以得到如下递归调用树
![普通递归法的递归调用树](https://upload-images.jianshu.io/upload_images/12014150-ef6680864506e21e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

树的高度为N-1,节点个数差不多为2^(N-1)

时间复杂度近似为O(2^N)

- 备忘录递归法

由于将F(3)~F(N)这N-2个数都只计算一次并存储到备忘录中,因此在递归的过程中相当于只对每个元素计算了一次

因此时间复杂度和空间复杂度都是O(N)

- 动态规划法

对于一个i从3~N的循环,时间复杂度为O(N)

由于只定义了三个临时变量,因此空间复杂度为O(1)

### 出错检测
- 输入的楼梯总数非负
```
/*出错检测: 楼梯总数必须非负*/
while (cin >> n)
{
	if (n >= 0) { break; }
	else { cout << "楼梯总数应非负, 请重新输入: "; }
}
```
![楼梯总数为负](https://upload-images.jianshu.io/upload_images/12014150-9bb5717f3fcea9a9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 选择的算法应为1~3号
```
while (true)
	{
		cout << endl << "请输入你想选择的算法(1普通递归算法, 2备忘录递归算法, 3迭代算法, 0结束程序): ";
		cin >> OpCode;
		if (!OpCode) { break; }

		...

		/*出错检测: 只能选择1~3号算法*/
		default:
			cout << "输入有误, 请重新输入(1普通递归算法, 2备忘录递归算法, 3迭代算法): ";
			break;
		}
	}
```
![算法编号不为1~3](https://upload-images.jianshu.io/upload_images/12014150-3da09df1156352e1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 其他
- 输入100时的问题
*以迭代的算法为例*
	- 将函数返回值及所有中间变量类型设置为long long, 运行结果如下
	![数据量_100_long long](https://upload-images.jianshu.io/upload_images/12014150-994c1e4eaf1b58b3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
	- 将函数返回值及所有中间变量类型设置为double
	![数据量_100_double](https://upload-images.jianshu.io/upload_images/12014150-b1b3d2d9d9d8316a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
	- 将函数返回值及所有中间变量类型设置为double, 并按照0位小数输出`setiosflags(ios::fixed) << setprecision(0)`
	![数据量_100_double_0位小数](https://upload-images.jianshu.io/upload_images/12014150-ff4a623cc427a962.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

如图可见类型为long long和类型为double并以0位小数输出的结果不一致, 而通过计算之后发现数据量100的时候, 应该超过long long类型的最大存储容量

由此, double类型的值应为正确结果

且数据量为90的时候, 结果有19位有效数字, 而数据量为100的时候, long long类型的算法仍是19位有效数字, 显然错误
	


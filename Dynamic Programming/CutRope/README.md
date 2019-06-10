# AssignmentThree2019_Programming

###### 割绳子

[TOC]

## 开发环境

- **开发环境:** Windows 10

- **开发软件:** 

  **Visual Studio 2017** *15.9.28307.665*

- **开发语言:** C++



## 操作说明

- 编译运行`CutRope.cpp`文件, 打开控制台窗口

- 选择算法:

  - 键入`1`代表选择动态规划算法
  - 键入`2`代表选择贪婪算法
  - 输入无效算法将收到提示, 并允许重新选择

  ![image.png](https://upload-images.jianshu.io/upload_images/12014150-c703f40efd137c73.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 选择是否显示各段长度

  - 键入`y`或`Y`代表显示各段长度
  - 键入`n`或`N`代表不显示各段长度, 只显示最大乘积
  - 输入无效字母将收到提示, 并允许重新选择

  ![image.png](https://upload-images.jianshu.io/upload_images/12014150-e7eb3fce2cb67652.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 查看结果



## 问题描述

给你一根长度为n 的绳子，请把绳子剪成m 段（m，n 都是整数，n>1 并且m>1），每段绳子的长度记为k[0], k[1], …, k[m]。请问k[0] k[1] … k[m]可能的最大乘积是多少？

>  例如，当绳子的长度是8 时，我们把它剪成长度分别为2，3，3 的三段，此时得到的最大乘积是18。



## 问题分析

将长度为n的绳子剪第一刀(剪成2段), 有n-1种选择, 第一段绳子长度为1,2,3,...,n-2,n-1, 相应的另一段绳子长度为n-1,n-2,...,2,1

- 接着将第一段绳子继续划分, 第二段绳子继续划分, 再继续细分下去, 知道到达边界情况: 绳子为2的时候只能分成长度为1的两段。这就具备了动态规划的基本要求

  （1）	求一个问题的最优解
  （2）	该问题能分成若干个问题的子问题
  （3）	并且子问题之间还有重叠的更小的子问题

  - 此时可以选择`f(n)=max(f(i)*f(n-i))`。

- 如果在划分成这两段的时候，每次都选择当前利益最大的划分方式，这就具备了贪婪算法的基本要求。

  - 尽可能多的分解出长度为3的绳子，这会使乘积尽可能的大；特殊情况为最后绳子的剩余长度为4，此时分解成2+2的效果比1+3的效果好



## 核心算法

### 	动态规划算法

- 设f(n)为把长度为n的绳子剪成若干段后乘积的最大值

- 由问题分析得知我们可以做`f(n)=max(f(i)*f(n-i))`, 其中 0<i<n

- 这种算法是自上而下的递归算法, 要计算很多的中间变量

- 因此采用自下而上的动态规划算法

- 边界条件为长度为2的时候只能拆分成1+1, 长度为3的时候只能拆分成1+2, 即f(2)=1, f(3)=2

  ### 贪婪算法

- 尽可能多地剪成长度为3的绳子段

- 当剩下的绳子长度为4的时候, 剪成2+2的效果(4)比1+3的效果(3)要好



## 算法设计

### 	动态规划算法

#### 		显示各段长度

```c++
int maxDivide_dp(int length, vector<int> &factor)
{
	factor.clear();
	int maxMulti = 1;
	if (length == 2)
	{
		factor.push_back(1);
		factor.push_back(1);
		maxMulti = 1;
	}
	else if (length == 3)
	{
		factor.push_back(1);
		factor.push_back(2);
		maxMulti = 2;
	}
	else
	{
		vector<vector<int> >dp_factor(length + 1);	//row => 每一个长度, col => 每一个长度的最优分解情况
		vector<int> dp(length + 1, 0);

		/*边界条件*/
		dp[1] = 1; dp_factor[1].push_back(1);
		dp[2] = 2; dp_factor[2].push_back(2);
		dp[3] = 3; dp_factor[3].push_back(3);

		int maxindex, maxthis;		//取得最大值时j的编号, 每一轮的最大值
		for (int i = 4; i <= length; ++i)
		{
			maxthis = 0;
			maxindex = 1;
			for (int j = 1; j <= i / 2; ++j)
			{
				if (dp[j] * dp[i - j] > maxthis)
				{
					maxthis = dp[j] * dp[i - j];
					maxindex = j;
				}
			}
			dp[i] = maxthis;
			dp_factor[i].insert(dp_factor[i].end(), dp_factor[maxindex].begin(), dp_factor[maxindex].end());		//将f(i)的最佳分解并入f(n)的因子
			dp_factor[i].insert(dp_factor[i].end(), dp_factor[i-maxindex].begin(), dp_factor[i-maxindex].end());	//将f(n-i)的最佳分解并入f(n)的因子
		}

		maxMulti = dp[length];
		factor.resize(dp_factor[length].size());
		copy(dp_factor[length].begin(), dp_factor[length].end(), factor.begin());	//将长为length的因子放到原始数组中
	}

	sort(factor.begin(), factor.end());		//由于是分别将f(i)和f(n-i)的因子压入, 导致可能使的factor数组乱序
	return maxMulti;
}

```

#### 		不显示各段长度

```c++
int maxDivide_dp(int length)
{
	int maxMulti = 1;

	//特殊处理边界情况
	if (length == 2)
	{
		maxMulti = 1;
	}
	else if (length == 3)
	{
		maxMulti = 2;
	}
	else
	{
		vector<int> dp(length + 1, 0);
		dp[1] = 1;
		dp[2] = 2;
		dp[3] = 3;

		int maxthis;		//记录每一轮的最大值

		/* f(x) = max{f(i)*f(n-i)}  0<i<n */
		for (int i = 4; i <= length; ++i)
		{
			maxthis = 0;
			for (int j = 1; j <= i / 2; ++j)
			{
				maxthis = max(maxthis, dp[j] * dp[i - j]);
			}
			dp[i] = maxthis;		//更新动态规划存储数组
		}

		maxMulti = dp[length];
	}

	return maxMulti;
}
```

### 	贪婪算法

#### 		显示各段长度

```c++
int maxDivide_gready(int length, vector<int> &factor)
{
	factor.clear();

	if (length == 2) 
	{
		factor.push_back(1);
		return 1; 
	}
	else if (length == 3)
	{
		factor.push_back(2);
		return 2;
	}
	else
	{
		int maxMulti, times_3, times_2;
		times_3 = length / 3;

		if (length - 3 * times_3 == 1) { times_3--; }

		times_2 = (length - 3 * times_3) / 2;

		maxMulti = static_cast<int>(pow(3, times_3)*pow(2, times_2));

		while (times_2--) { factor.push_back(2); }		//将若干2压入因子向量中
		while (times_3--) { factor.push_back(3); }		//将若干3压入因子向量中

		return maxMulti;
	}
}
```

#### 		不显示各段长度

```c++
int maxDivide_gready(int length)
{
	if (length == 2) { return 1; }
	else if (length == 3) { return 2; }
	else
	{
		int maxMulti, times_3, times_2;
		times_3 = length / 3;		//尽可能的拆分成3

		if (length - 3 * times_3 == 1) { times_3--; }	//如果最后剩余值是4, 拆解成2+2的价值(4)比1+3的价值高(3)

		times_2 = (length - 3 * times_3) / 2;	//剩余值拆解成2

		maxMulti = static_cast<int>(pow(3, times_3)*pow(2, times_2));	//返回这些3和2的乘积值

		return maxMulti;
	}
}
```



## 功能测试

### 	动态规划算法

#### 		显示各段长度

![image.png](https://upload-images.jianshu.io/upload_images/12014150-9f6cb04033bb9d09.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 		不显示各段长度

![image.png](https://upload-images.jianshu.io/upload_images/12014150-0e5a1a81a43f5803.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 	贪婪算法

#### 		显示各段长度


![image.png](https://upload-images.jianshu.io/upload_images/12014150-9e9336eddfaf360e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 		不显示各段长度

![image.png](https://upload-images.jianshu.io/upload_images/12014150-ffb281be97a98fd5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



## 复杂度分析

### 	动态规划算法

采用动态规划算法，自底向下的进行算法的实现。采用双重循环，外层循环从4逐步遍历到绳子的长度length；内层循环中选择最大的划分价值。

该算法使用了大小为length+1的数组用于存储各段绳子的最佳划分价值。

因此该算法的时间复杂度为`O(n^2)`, 空间复杂度为O(n)



如果要显示各段长度, 在内存循环中要定位到产生最佳划分的下标, 进而将该下标对应的划分方式加入到该长度绳子的划分方式

另外, 开辟了二维数组, 理论上的空间开销为O(n^2), 但是该二维数组其实为近似的下三角矩阵

显示各段长度的时间复杂度为`O(n^2)`, 空间复杂度为`O(n^2)`

### 	贪婪算法

采用贪婪算法, 直接计算将绳子拆分成长度为3的最大可能数, 如果最后剩余绳子的长度为4, 要进行特殊的处理

空间上只是用两个临时变量记录长度为3的绳子总数和长度为2的绳子总数

因此该算法的时间复杂度为`O(1)`, 空间复杂度为`O(1)`



如果要显示各段长度, 需要一个一维数组储存长度为length时的因子

显示各段长度的时间复杂度为`O(n)`, 空间复杂度为`O(n)`



## 作者信息

- **学号:**	1754060 
- **姓名**:	张喆
- **上课时间:** 周一5-6节
- **联系方式: **  doubleZ0108@gmail.com
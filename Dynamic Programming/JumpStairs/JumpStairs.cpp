/*
	Dynamic Programming --- 跳台阶问题

Q:"一只青蛙一次可以跳上 1 级台阶，也可以跳上 2 级台阶。求该青蛙跳上 1 个 n
	级的台阶总共有多少种跳法"。
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

/*递归算法求解跳台阶问题*/
long long JumpStairs_brutal(int n)
{
	if (n == 0) { return 0; }
	else if (n == 1) { return 1; }
	else if (n == 2) { return 2; }
	else 
		{ return JumpStairs_brutal(n - 1) + JumpStairs_brutal(n - 2); }
}

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

int main(void)
{
	int n;
	cout << "请输入楼梯总数: ";
	while (cin >> n)
	{
		if (n >= 0) { break; }
		else { cout << "楼梯总数应非负, 请重新输入: "; }
	}
	
	int OpCode;
	while (true)
	{
		cout << endl << "请输入你想选择的算法(1普通递归算法, 2备忘录递归算法, 3迭代算法, 0结束程序): ";
		cin >> OpCode;
		if (!OpCode) { break; }

		switch (OpCode)
		{
		case 1: {
			cout << "JumpStairs_brutal算法求得跳上" << n << "级台阶共有"
				<< JumpStairs_brutal(n) << "种跳法" << endl;

			break;
		}
		case 2: {
			cout << "JumpStairs_map算法求得跳上" << n << "级台阶共有"
				<< JumpStairs_map(n) << "种跳法" << endl;

			break;
		}
		case 3: {
			cout << "JumpStairs_loop算法求得跳上" << n << "级台阶共有"
				<< JumpStairs_loop(n) << "种跳法" << endl;

			break;
		}
		default:
			cout << "输入有误, 请重新输入(1普通递归算法, 2备忘录递归算法, 3迭代算法): ";
			break;
		}
	}

	system("pause");
	return 0;
}

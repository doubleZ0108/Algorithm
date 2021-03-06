#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

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

int main(void)
{
	int length, maxMulti;
	vector<int> factor;

	while (true)
	{
		cout << "请输入绳子的长度: ";
		cin >> length;
		if (length > 1) { break; }
		cerr << "绳子的长度应为大于1的整数, 请重新输入" << endl;
	}

	int algorithm;
	while (true)
	{
		cout << "请选择算法(1.动态规划 2.贪婪算法): ";
		cin >> algorithm;
		if (algorithm == 1 || algorithm == 2) { break; }
		cerr << "算法应为1或2, 请重新输入" << endl;
	}

	char type;
	while (true)
	{
		cout << "请选择是否显示各段长度(y或n): ";
		cin >> type;
		if (type == 'y' || type == 'Y' || type == 'n' || type == 'N') { break; }
		cerr << "只能输入y或n, 请重新输入" << endl;
	}
	
	if (algorithm == 1 && (type == 'y' || type == 'Y'))
	{
		maxMulti = maxDivide_dp(length, factor);
	}
	else if (algorithm == 1 && (type == 'n' || type == 'N'))
	{
		maxMulti = maxDivide_dp(length);
	}
	else if (algorithm == 2 && (type == 'y' || type == 'Y'))
	{
		maxMulti = maxDivide_gready(length, factor);
	}
	else
	{
		maxMulti = maxDivide_gready(length);
	}

	cout << endl << "最大乘积为: " << maxMulti << endl;

	if (factor.size())
	{
		cout << "====================================" << endl;
		cout<< "         此时将绳子划分为" << factor.size() << "段" << endl;
		cout << "         各段长度为: ";
		for_each(factor.begin(), factor.end(), [](int buf) {cout << buf << ' '; });
		cout<< endl;
		cout << "====================================" << endl;

	}
	

	system("pause");
	return 0;
}


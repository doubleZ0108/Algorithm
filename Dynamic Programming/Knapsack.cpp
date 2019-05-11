/*
V[i,j]:
	i表示前i个item
	j表示当前背包可承受的最大重量
	V[i,j]为当前i, j下的最优值
	最终目标为V[n,W]

测试样例:
5 4 
2 1 3 2
12 10 20 15
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
	int W, n;
	cout << "请输入背包的总重量W, 和物品数量n: ";
	cin >> W >> n;

	vector<int> w(n+1, 0), v(n+1, 0);
	cout << "请输入每个物体的重量: ";
	for (int i = 1; i <= n; ++i) { cin >> w[i]; }
	cout << "请输入每个物体的价值: ";
	for (int i = 1; i <= n; ++i) { cin >> v[i]; }

	vector<vector<int> > V(n+1, vector<int>(W+1, 0));		//从0计数到n, 从0计数到W
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= W; ++j)
		{
			if (j < w[i]) { V[i][j] = V[i - 1][j]; }
			else
			{
				V[i][j] = max(V[i - 1][j], V[i - 1][j - w[i]] + v[i]);
			}
		}
	}

	cout << endl << "V矩阵: " << endl;
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= W; ++j)
		{
			cout << V[i][j] << ' ';
		}
		cout << endl;
	}

	cout << endl << "最优值为: " << V[n][W] << endl;

	system("pause");
	return 0;
}

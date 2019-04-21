/*
样例输入
3 4
2 -1  1 1
4  1 -1 5
1  1  1 0

等价的线性方程组:
2x0 - x1 - x2 = 1
4x0 + x1 - x2 = 5
 x0 + x1 + x2 = 0
*/

#include <bits/stdc++.h>
using namespace std;

//将矩阵变换成上三角矩阵
//三重循环, 每一行都要减掉上面所有行乘以不同的因子	(第三重循环是每一行中的每一个元素)
template<typename Type>
void tran2UpperTriangular(vector<vector<Type> > &M)
{
	int row = M.size(), col = M[0].size();

	for (int i = 1; i < row; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			for (int k = col - 1; k >= 0; --k)		//必须从右到左递减, 因为左到有的话前面的已经变成0了
			{
				M[i][k] -= M[j][k] * M[i][j] / M[j][j];
			}
		}
	}
}

//反向求解线性方程组的n个未知数
template<typename Type>
void BackwardSubstitution(vector<vector<Type> > &M, vector<Type> &X)
{
	int row = M.size(), col = M[0].size();

	for (int i = row - 1; i >= 0; --i)
	{
		X[i] = M[i][col - 1];				//初始化为右端系数
		for (int j = col - 2; j > i; --j)
		{
			X[i] -= M[i][j] * X[j];
		}
		X[i] /= M[i][i];					//最后除以待求项的系数
	}
}

int main(void)
{
	int row, col;	cin >> row >> col;

	vector<vector<double> > matrix(row, vector<double>(col, 0));
	for (int i = 0; i < row; ++i) { for (int j = 0; j < col; ++j) { cin >> matrix[i][j]; } }

	tran2UpperTriangular(matrix);

	cout << endl << "The UpperTriangular: " << endl;
	for (int i = 0; i < row; ++i) { for (int j = 0; j < col; ++j) { cout << matrix[i][j] << ' '; }cout << endl; }

	vector<double> result(row);
	BackwardSubstitution(matrix, result);

	cout << endl << "The result: " << endl;
	for_each(result.begin(), result.end(), [](double buf) {cout << buf << ' '; });
	cout << endl;

	system("pause");
	return 0;
}

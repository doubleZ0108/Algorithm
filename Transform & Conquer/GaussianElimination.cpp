/*
3 4
2 -1  1 1
4  1 -1 5
1  1  1 0
*/

#include <bits/stdc++.h>
using namespace std;

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
int main(void)
{
	int row, col;	cin >> row >> col;

	vector<vector<double> > matrix(row, vector<double>(col, 0));
	for (int i = 0; i < row; ++i) { for (int j = 0; j < col; ++j) { cin >> matrix[i][j]; } }

	tran2UpperTriangular(matrix);

	for (int i = 0; i < row; ++i) { for (int j = 0; j < col; ++j) { cout << matrix[i][j] << ' '; }cout << endl; }

	system("pause");
	return 0;
}

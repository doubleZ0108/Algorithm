//例: 18 = 2*3*3

/*将整数index分解为质因数的乘积*/
void decompose(vector<int> &seq, int index)
{
	int n = index;	//要提前储存index,否则循环条件会一点点缩小

	for (int i = 2; i < sqrt(index) + 1; ++i)
	{
		while (n%i == 0)
		{
			seq.push_back(i);
			n /= i;
		}
	}
}

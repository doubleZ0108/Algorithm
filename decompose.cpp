//例: 18 = 2*3*3

/*将整数index分解为质因数的乘积*/
void decompose(vector<int> &seq, int index)
{
	for (int i = 2; i < sqrt(index) + 1; ++i)
	{
		while (index%i == 0)
		{
			seq.push_back(i);
			index /= i;
		}
	}
}

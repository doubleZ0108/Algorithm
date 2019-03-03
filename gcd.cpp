/*
	求两个数m,n的最大公约数
	这里默认 m>n
*/


/*欧几里得算法*/
//gcd(m,n) = gcd(n,m%n)  while  gcd(m,0) = m
int gcd_recrusive(int m, int n)
{
	if (n == 0) { return m; }
	else { return gcd_recrusive(n, m%n); }
}

/*将欧几里得算法改成迭代表示*/
int gcd_loop(int m, int n)
{
	int r;
	while (n)
	{
		r = n;
		n = m % n;
		m = r;
	}
	return m;
}

/*暴力枚举 */
int gcd_enum(int m, int n)
{
	//n为0时做特殊处理
	if (n == 0) { return m; }

	int i;

	//从更小的数(默认是n)开始一个一个往前找, 如果m和n都能整除它则返回结果
	//!(m%i==0 && n%i==0)
	for (i = n; m%i!=0 || n%i!=0; --i);

	return i;
}

/*将整数index分解为质因数的乘积*/
void decompose(vector<int> &seq, int index)
{
	int n = index;	//要提前储存index,否则循环条件会一点点缩小

	for (int i = 2; i <= sqrt(index) + 1; ++i)
	{
		while (n%i == 0)
		{
			seq.push_back(i);
			n /= i;
		}
	}

	//存储最后一个数
	seq.push_back(n);
}

/*提取共同的质因数*/
int gcd_decompose(int m, int n)
{
	//n为0特殊考虑
	if (n == 0) { return m; }

	vector<int> seqm, seqn;
	decompose(seqm, m);
	decompose(seqn, n);

	//找出所有的公共质因数并做乘积
	int gcd = 1;
	vector<int>::iterator iterm = seqm.begin(), itern = seqn.begin();
	while (iterm != seqm.end() && itern != seqn.end())
	{
		if (*iterm == *itern)
		{
			gcd *= *iterm;
			iterm++; itern++;
		}
		else if (*iterm < *itern) { iterm++; }
		else { itern++; }
	}

	return gcd;
}

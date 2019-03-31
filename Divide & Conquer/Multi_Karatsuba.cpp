/*返回整数的位数*/
int getLength(int num)
{
	int cnt = 0;
	while (num)
	{
		num /= 10;
		cnt++;
	}
	return cnt;
}

/*将整数划分为高n/2位和低n/2位*/
void divide(int num, int &part1, int &part2, int length)
{
	part1 = num / pow(10, length / 2);			//高n/2位
	part2 = num - part1 * pow(10, length / 2);	//低n/2位
}

/*
	1. 默认A,B两个数的位数相同, 不同时可以在短的数前面补0
	2. 默认两个数的位数必须为偶数(可以正好从 n/2 处划分
*/
int Multi_Karatsuba(int A, int B)
{
	if (A < 10 || B < 10) { return A * B; }

	int length, A1, A2, B1, B2, C0, C1, C2;

	/*获取输入数的位数*/
	length = getLength(A);

	/*将A,B拆分成两部分*/
	divide(A, A1, A2, length);
	divide(B, B1, B2, length);

	/*Divide - 计算三次小规模问题的乘法*/
	C0 = Multi_Karatsuba(A1, B1);
	C1 = Multi_Karatsuba(A1 + A2, B1 + B2);
	C2 = Multi_Karatsuba(A2, B2);

	/*Conquer & Combine*/
	return (C0*pow(10, length) + (C1 - C0 - C2)*pow(10, length / 2) + C2);
}

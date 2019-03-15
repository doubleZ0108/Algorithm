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
#include <ctime>
using namespace std;

int JumpStairs_brutal(int n)
{
	if (n == 0) { return 0; }
	else if (n == 1) { return 1; }
	else if (n == 2) { return 2; }
	else 
		{ return JumpStairs_brutal(n - 1) + JumpStairs_brutal(n - 2); }
}
int JumpStairs_map(int n)
{
	static map<int, int> mymap;

	if (n == 0) { return 0; }
	else if (n == 1) { return 1; }
	else if (n == 2) { return 2; }

	if (mymap.count(n))
	{
		return mymap[n];
	}
	else
	{
		int value= JumpStairs_map(n - 1) + JumpStairs_map(n - 2);
		mymap[n] = value;
		return value;
	}
}
int JumpStairs_loop(int n)
{
	if (n == 0) { return 0; }
	else if (n == 1) { return 1; }
	else if (n == 2) { return 2; }

	int Fn, Fn_1 = 1, Fn_2 = 2;
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
	srand(time(NULL));
	//int n; cin >> n;
	for (int n = 0; n < 10; ++n)
	{
		cout << JumpStairs_brutal(n) << ' '
			<< JumpStairs_map(n) << ' '
			<< JumpStairs_loop(n) << endl;
	}
	

	system("pause");
	return 0;
}

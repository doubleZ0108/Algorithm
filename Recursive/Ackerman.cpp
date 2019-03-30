#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
using namespace std;
int Ackerman_recursive(int n,int m)
{
	cout << "********" << n << ' ' << m << endl;

	if (n == 1 && m == 0) { return 2; }
	else if (n == 0) { return 1; }
	else if (m == 0) { return n + 2; }
	else
	{
		return Ackerman_recursive(Ackerman_recursive(n - 1, m), m - 1);
	}
}

int Ackerman_memo(int n, int m)
{
	//cout << "********" << n << ' ' << m << endl;

	static map<pair<int, int>, int> memo;

	if (n == 1 && m == 0) { return 2; }
	else if (n == 0) { return 1; }
	else if (m == 0) { return n + 2; }
	else if (memo.count(pair<int, int>(n, m)))
	{
		return memo[pair<int, int>(n, m)];
	}
	else
	{
		int tmp= Ackerman_memo(Ackerman_memo(n - 1, m), m - 1);
		memo[pair<int, int>(n, m)] = tmp;
		return tmp;
	}
}

int main(void)
{
	int n, m;
	cin >> n >> m;

	cout << Ackerman_recursive(n,m) << endl;
	cout << Ackerman_memo(n, m) << endl;


	system("pause");
	return 0;
}

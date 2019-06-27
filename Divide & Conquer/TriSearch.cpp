#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

#define NOTFOUND -1

int TriSearch(vector<int> &ivec, int key)
{
	if (!ivec.size())
	{
		return NOTFOUND;
	}

	int left = 0, right = ivec.size() - 1;
	int firstmiddle, secondmiddle;

	while (left <= right)
	{
		firstmiddle = left + (right - left) / 3;
		secondmiddle = right - (right - left) / 3;
		if (key == ivec[firstmiddle])
		{
			return firstmiddle;
		}
		else if (key == ivec[secondmiddle])
		{
			return secondmiddle;
		}
		else if (key < ivec[firstmiddle])
		{
			right = firstmiddle - 1;
		}
		else if (key > ivec[secondmiddle])
		{
			left = secondmiddle + 1;
		}
		else
		{
			left = firstmiddle + 1;
			right = secondmiddle - 1;
		}
	}

	return NOTFOUND;
}

int main(void)
{
	vector<int> ivec = { 1, 3, 5, 6, 10, 14, 16, 20, 35, 57, 78, 89, 99, 100, 150, 300 };
	while (true)
	{
		int key;
		cout << "Please input the key you want to search: ";
		cin >> key;

		if (TriSearch(ivec, key) == NOTFOUND)
		{
			cout << "Sorry, the key you input is not in the vector!" << endl;
		}
		else
		{
			cout << "The position of " << key << " is " << TriSearch(ivec, key) << endl;
		}
	}

	system("pause");
	return 0;
}

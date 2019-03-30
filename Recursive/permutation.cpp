/*
	Perm(R) = {r1Perm(R1), r2Perm(R2),..., rnPerm(Rn)}
		其中Ri = R - ri
	
	例{1,2,3}的排列 <=> 1开头{2,3}的排列 ∪ 2开头{1,3}的排列 ∪ 3开头{1,2}的排
*/
template<typename Type>
void Perm(vector<Type> &seq, int first, int last)
{
	if (first == last)		//递归终止条件：待排序列只有一个元素，则此时一趟已经排好序了，可以输出了
		{ for_each(seq.begin(), seq.end(), [](Type buf) {cout << buf << ' '; }); cout << endl; }
	else
	{
		for (int i = first; i <= last; ++i)
		{
			swap(seq[first], seq[i]);	//每个元素做头: 将序列中的每个元素和第一个元素交换

			Perm(seq, first + 1, last);	//将问题规模缩小, 做后几位的排列

			swap(seq[i], seq[first]);	//最后再换回来, 进入下一轮循环
		}
	}
}

int main(void)
{
	int n;
	cin >> n;
	vector<int> seq(n);
	for (int i = 1; i <= n; ++i) { seq[i-1] = i; }

	Perm(seq, 0, n-1);

	system("pause");
	return 0;
}

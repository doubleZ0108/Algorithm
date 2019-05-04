#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void InitTree(vector<string> &tree)
{
	string buf;
	getline(cin, buf);		//读入一整行数据

	buf.erase(buf.begin(), buf.begin() + 1);	//去掉开始的[

	/*next_iter为循环迭代器; lastend_iter为上个内容终止的迭代器,也即下次该开始的位置迭代器*/
	for (string::iterator next_iter = buf.begin(), lastend_iter = buf.begin(); next_iter != buf.end(); )
	{
		while (*next_iter != ',' & *next_iter != ']') { ++next_iter; }	//当不是','或']'时代表仍是有效内容

		tree.push_back(string(lastend_iter, next_iter));	//将新内容加入到数组中

		if (*next_iter == ']') { break; }	//如果此时循环迭代器内容为']'代表已经遍历完buf字符串

		next_iter++; next_iter++;	//移动到下个有效位置
		lastend_iter = next_iter;
	}
}
void OutputTree(vector<string> &tree)
{
	cout << tree[0];	//特殊处理第一个元素
	for_each(tree.begin()+1, tree.end(), [](string &buf) {cout << ", " << buf ; });
	cout << endl;
}

vector<string> mergeTrees(vector<string> &tree1, vector<string> &tree2)
{
	vector<string> mergedTree;

	vector<string>::iterator iter1 = tree1.begin(), iter2 = tree2.begin();
	for (; iter1 != tree1.end() && iter2 != tree2.end(); ++iter1, ++iter2)
	{
		if (*iter1 == "null" && *iter2 == "null") {
			mergedTree.push_back(string("null"));
		}
		else if (*iter1 != "null" && *iter2 == "null") {
			mergedTree.push_back(*iter1);
		}
		else if (*iter1 == "null" && *iter2 != "null") {
			mergedTree.push_back(*iter2);
		}
		else {
			mergedTree.push_back(to_string(atoi(iter1->c_str()) + atoi(iter2->c_str())));
		}
	}
	for (; iter1 != tree1.end(); ++iter1) {
		mergedTree.push_back(*iter1);
	}
	for (; iter2 != tree2.end(); ++iter2) {
		mergedTree.push_back(*iter2);
	}

	return mergedTree;
}

int main(void)
{
	vector<string> tree1, tree2, mergedTree;
	cout << "Please input two array which represent two trees: " << endl;
	InitTree(tree1);
	InitTree(tree2);

	mergedTree = mergeTrees(tree1, tree2);
	cout << endl << "The result of the tree after merged: " << endl;
	OutputTree(mergedTree);

	system("pause");
	return 0;
}

# AssignmentTwo2019_Programming

###### 合并二叉树

## 目录

* [问题描述](#问题描述)  
* [问题分析](#问题分析)  
* [核心算法](#核心算法)
* [算法设计](#算法设计)
* [功能测试](#功能测试)
* [复杂度分析](#复杂度分析)
* [其他](#其他)
* [作者信息](#作者信息)

<a name="问题描述"></a>  

## 问题描述

给出两个二叉树，合并它们并返回合并后的二叉树。

**合并规则**：相同位置的节点值相加

- 如果相同位置都不为 null，则数值相加
- 如果相同位置一个树为 null，一个树值为 A，则设置为 A
- 如果相同位置都为 null，则设置为 null

<a name="问题分析"></a>  

## 问题分析

- **树的存储方式**:
  - 数组存储
  - 定义二叉树结点结构体, 通过左右指针构建二叉树
- **输入:**  输入是一个数组形式的字符串代表树的各个结点, 要将其进行适当的转换, 并存储在"树"中

<a name="核心算法"></a>  

## 核心算法

- **数组存储:**

  - 将二叉树用一维数组存储, 没有结点的位置用`NULL`填充
  - 合并时遍历两个数组
    - 如果同为NULL, 则将结果树该位置设置为NULL
    - 如果有一方为NULL, 另一方非NULL, 则将结果树该位置设置为非NULL的值
    - 如果两方都非NULL, 则将二者的值相加放到结果树该位置
  - 最后将更长的数组(树层数更多)后面的结点加到结果树中

- **结构体链式存储:** 

  - 定义树中结点的结构体`struct TreeNode`

  ```C++
  struct TreeNode {
  	int val;
  	TreeNode *left;
  	TreeNode *right;
  	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
  ```

  - 合并时采用递归的方法
    - 如果两指针都为NULL, 则返回NULL
    - 如果有一个指针为NULL, 另一个非NULL, 则返回非空的指针
    - 如果两个指针都非NULL, 则将某一个值加到两一个值, 并对该指针的左右孩子递归调用该方法进行子树的合并

<a name="算法设计"></a>  

## 算法设计

- **数组存储:**

  - 将元素填入数组表示的树中

  ```C++
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
  ```

  

  - 以规定格式输出树

  ```C++
  void OutputTree(vector<string> &tree)
  {
  	cout << tree[0];	//特殊处理第一个元素
  	for_each(tree.begin() + 1, tree.end(), [](string &buf) {cout << ", " << buf; });
  	cout << endl;
  }
  
  ```

  

  - 两棵二叉树的合并

  ```C++
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
  
  ```

- **结构体链式存储:**

  - 以t1树储存结果, 不用另开辟一棵树

  ```C++
  TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
  	if (!t1 && !t2) {
  		return NULL;
  	}
  	else if (t1 && !t2) {
  		return t1;
  	}
  	else if (!t1 && t2) {
  		return t2;
  	}
  	else {
  		t1->val += t2->val;
  		t1->left = mergeTrees(t1->left, t2->left);
  		t1->right = mergeTrees(t1->right, t2->right);
  		return t1;
  	}
  }
  
  ```

  

  - 只分两种情况讨论, 当一方为NULL时, 直接返回另一方

  ```C++
  TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
  	if (!t1) { return t2; }
  	if (!t2) { return t1; }
  
  	t1->val += t2->val;
  	t1->left = mergeTrees(t1->left, t2->left);
  	t1->right = mergeTrees(t1->right, t2->right);
  	return t1;
  }
  
  ```

  

  - 完全重新开辟一棵新树

  ```C++
  TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
  	TreeNode *root;
  	TreeNode *left1 = NULL, *left2 = NULL, *right1 = NULL, *right2 = NULL;
  
  	if (!t1 && !t2) { return NULL; }
  	else if (t1 && t2)
  	{
  		root = new TreeNode(t1->val + t2->val);
  		left1 = t1->left;
  		left2 = t2->left;
  		right1 = t1->right;
  		right2 = t2->right;
  	}
  	else if (t1 && !t2)
  	{
  		root = new TreeNode(t1->val);
  		left1 = t1->left;
  		right1 = t1->right;
  	}
  	else
  	{
  		root = new TreeNode(t2->val);
  		left2 = t2->left;
  		right2 = t2->right;
  	}
  
  	root->left = mergeTrees(left1, left2);
  	root->right = mergeTrees(right1, right2);
  
  	return root;
  }
  ```

  

<a name="功能测试"></a>  

## 功能测试

- **输入格式:** 中括号包裹的一维数组(按层次顺序输入), 每两个元素之间以 *<u>逗号+空格</u>* 隔开
- **输出格式:** 合并后的树(按层次顺序输出), 每两个元素之间以 *<u>逗号+空格</u>* 隔开(末尾没有多余的空格)

![TIM截图20190504183142.png](https://upload-images.jianshu.io/upload_images/12014150-ed574032f09d780c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![TIM截图20190504183203.png](https://upload-images.jianshu.io/upload_images/12014150-ffb7911a6cd590e9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![TIM截图20190504183225.png](https://upload-images.jianshu.io/upload_images/12014150-02da5e02ad4c462d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![TIM截图20190504183104.png](https://upload-images.jianshu.io/upload_images/12014150-2379869a9b771c68.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

<a name="复杂度分析"></a>  

## 复杂度分析

- **数组存储:**
  - 将元素填入数组表示的树中: 将一整行信息全部读入string类型的变量中, 之后遍历该string, 在合适的位置进行分段, 填充进用数组表示的树中, 该过程复杂度为`O(n)`
  - 合并操作定义了两个迭代器分别指向两个树对应的数组, 在二者的公共部分进行四种判断并执行相应的操作, 之后把较长的数组剩下的元素加入到结果数组中, 该过程复杂度为`O(n)`
- **结构体链式存储:**
  - 由于需要遍历两棵树的所有结点, 所以时间复杂度为`O(n)`
  - 不考虑递归消耗, 方法一、二没使用额外的存储空间, 空间复杂度为`O(1)`, 方法三构建了一棵结果树, 空间复杂度为`O(n)`

<a name="其他"></a>  

## 其他

用结构体链式存储的算法只定义了合并两个树的方法`mergeTrees()`, 并没有提供创建两棵树以及输出结果树的方法

该函数参数为指向两个树根节点的指针, 返回结果为指向结果树根节点的指针

<a name="作者信息"></a>  

## 作者信息

- **学号:**	1754060 

	- **姓名**:	张喆
	- **上课时间:** 周一5-6节
	- **联系方式: **  doubleZ0108@gmail.com
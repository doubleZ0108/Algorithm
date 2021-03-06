/*
测试用例:
	2 + 3 * ( 7 - 4 ) + 8 / 4
	( ( 2 + 3 ) * 4 - ( 8 + 2 ) ) / 5
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 *                                计算器
 *****************************************************************************/

typedef int bool;
typedef int DATA;
#define False 0
#define True 1
#define EMPTY_CH '\0'
#define EMPTY_NUM -999999
#define SIZE 50

/*============ 判断表达式括号是否匹配 ============*/
char bucket_stack[100] = "\0";
int bucket_stack_index = -1;

bool isempty_bucket_stack() {
	return bucket_stack_index == -1;
}

void bucket_stack_push(char ch) {
	bucket_stack_index++;
	bucket_stack[bucket_stack_index] = ch;
}

char bucket_stack_pop(void) {
	if (isempty_bucket_stack()) {
		return EMPTY_CH;
	}
	char ch = bucket_stack[bucket_stack_index];
	bucket_stack_index--;
	return ch;
}

void bucket_stack_clear(void) {
	memset(bucket_stack, '\0', sizeof(bucket_stack));
	bucket_stack_index = -1;
}




/*============ 操作数栈 ============*/
int num_stack[100] = { 0 };
int num_stack_index = -1;

bool isempty_num_stack() {
	return num_stack_index == -1;
}

void num_stack_push(int num) {
	num_stack_index++;
	num_stack[num_stack_index] = num;
}

int num_stack_pop(void) {
	if (isempty_num_stack()) {
		return EMPTY_NUM;
	}
	int num = num_stack[num_stack_index];
	num_stack[num_stack_index] = 0;
	num_stack_index--;
	return num;
}

void num_stack_clear(void) {
	memset(num_stack, 0, sizeof(num_stack));
	num_stack_index = -1;
}


/*============ 操作符栈 ============*/
char op_stack[100] = "\0";
int op_stack_index = -1;

bool isempty_op_stack() {
	return op_stack_index == -1;
}

void op_stack_push(char ch) {
	op_stack_index++;
	op_stack[op_stack_index] = ch;
}

char op_stack_pop(void) {
	if (isempty_op_stack()) {
		return EMPTY_CH;
	}
	char ch = op_stack[op_stack_index];
	op_stack[op_stack_index] = '\0';
	op_stack_index--;
	return ch;
}

char op_stack_top(void) {
	if (isempty_op_stack()) {
		return EMPTY_CH;
	}
	return op_stack[op_stack_index];
}

void op_stack_clear(void) {
	memset(op_stack, '\0', sizeof(op_stack));
	op_stack_index = -1;
}


/*============ 优先级 ============*/
int isp(char ch)
//栈内优先级
{
	switch (ch)
	{
	case '#':return 0;
	case '(':return 1;
	case '*':case '/':return 5;
	case '+':case '-':return 3;
	case ')':return 6;
	}
}
int icp(char ch)
//栈外优先级
{
	switch (ch)
	{
	case '#':return 0;
	case '(':return 6;
	case '*':case '/':return 4;
	case '+':case '-':return 2;
	case ')':return 1;
	}
}


/*============ 运算符判断 ============*/
bool isOperator(char c)
{
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '#':
		return True;
		break;
	default:
		return False;
		break;
	}
}

/*============ 单个数字字符判断 ============*/
bool isDigit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

/*============ 数字判断 ============*/
bool isNum(char* exp)
//数字包括 正数 负数 浮点数 (其中+3要进行特殊处理)
{
	char ch = exp[0];
	if (ch == '+' && strlen(exp) > 1)
		// 如 +3 就是储存 3
	{
		exp = exp + 1;	//把+删除
		ch = exp[0];		//更新一下ch
	}

	if (isDigit(ch) || (ch == '-' && strlen(exp) > 1))
		//储存各种数字, 包括正数,负数,浮点数
	{
		return True;
	}

	return False;
}

/*============ 在表达式最后添加 # 标识符 ============*/
void addTail(char* exp) {
	int i;
	for (i = 0; i < strlen(exp); ++i);
	exp[i] = ' ';
	exp[i + 1] = '#';
}

/*============ 封装表达式中的项 ============*/
struct Data {
	int data;	//数据本身
	int flag;	//0->char, 1->int
};
int _current = 0;

/*============ 获取表达式中的下一项 ============*/
struct Data NextContent(char* exp)
{
	char _next[100] = "\0";
	char ch;
	int index = 0;

	for (int i = _current; i < strlen(exp); ++i)
	{
		ch = exp[i];
		if (ch != ' ')
		{
			_next[index] = ch;
			index++;	//因为不同对象以空格隔开,所以只要不是空格就加到_next
		}
		else
		{
			while (exp[i] == ' ') {
				i++;
			}
			_current = i;	//_current指向下一个位置,结束当前对象的寻找
			break;
		}
	}

	if (isOperator(_next[0])) {
		struct Data d;
		d.data = _next[0];
		d.flag = 0;
		return d;
	}
	else {
		struct Data d;
		d.data = atoi(_next);
		d.flag = 1;
		return d;
	}
}


/*============ 根据运算符和两个操作数计算值 ============*/
int Cal(int left, char op, int right)
{
	switch (op)
	{
	case '+':
		return left + right;
		break;
	case '-':
		return left - right;
		break;
	case '*':
		return left * right;
		break;
	case '/':
		return left / right;
		break;
	default:
		return left + right;
		break;
	}
}

/*============ 输出后缀表达式 ============*/
void showBackMode(struct Data result[], int size) {
	printf("The reverse polish notation is: ");
	for (int i = 0; i < size; ++i) {
		if (result[i].flag == 0) {
			printf("%c ", result[i].data);
		}
		else {
			printf("%d ", result[i].data);
		}
	}
	printf("\n");
}

/*============ 计算后缀表达式的结果 ============*/
int calResult(struct Data result[], int size)
{
	num_stack_clear();
	for (int i = 0; i < size; ++i) {
		if (result[i].flag == 1) {
			num_stack_push(result[i].data);
		}
		else {
			int right = num_stack_pop();
			int left = num_stack_pop();
			num_stack_push(Cal(left, result[i].data, right));
		}
	}
	return num_stack_pop();
}



int calculate(char* origin_exp, bool if_showrev, bool if_beauty) {
	/*============ 表达式美化 ============*/
	char exp[100] = "\0";
	int pos = 0;
	for (int i = 0; i < strlen(origin_exp); ++i) {
		if (isOperator(origin_exp[i])) {
			exp[pos] = ' ';
			++pos;
			exp[pos] = origin_exp[i];
			++pos;
			exp[pos] = ' ';
			++pos;
		}
		else if (isDigit(origin_exp[i])) {
			exp[pos] = origin_exp[i];
			++pos;
		}
	}
	
	/*初始两个栈*/
	num_stack_clear();
	op_stack_clear();
	_current = 0;

	struct Data result[100];
	int index = 0;

	/*在表达式尾部添加结束标识符*/
	addTail(exp);

	op_stack_push('#');
	struct Data elem = NextContent(exp);
	while (!isempty_op_stack()) {
		char ch = elem.data;

		if (elem.flag == 1) {		//如果是操作数, 直接读入下一个内容
			result[index] = elem;
			index++;
			elem = NextContent(exp);
		}
		else if (elem.flag == 0) {	//如果是操作符,判断ch的优先级icp和当前栈顶操作符的优先级isp
			char topch = op_stack_top();
			if (isp(topch) < icp(ch)) {		//当前操作符优先级大,将ch压栈,读入下一个内容
				op_stack_push(ch);
				elem = NextContent(exp);
			}
			else if (isp(topch) > icp(ch)) {	//当前优先级小,推展并输出到结果中
				struct Data buf;
				buf.data = op_stack_pop();
				buf.flag = 0;
				result[index] = buf;
				index++;
			}
			else {
				if (op_stack_top() == '(') {	//如果退出的是左括号则读入下一个内容
					elem = NextContent(exp);
				}
				op_stack_pop();
			}
		}
	}

	if (if_showrev) {
		showBackMode(result, index);
	}

	return calResult(result, index);
}

/*判断表达式括号是否匹配*/
bool check_exp_bucket(char* exp) {
	char ch = '\0';

	for (int i = 0; i < strlen(exp); ++i) {
		if (exp[i] == '(') {
			bucket_stack_push('(');
		}
		else if (exp[i] == ')') {
			ch = bucket_stack_pop();
			if (ch == EMPTY_CH || ch != '(') { 
				printf("Buckets in the exprssion you input do not match.\n");
				return False; 
			}
		}
	}
	return isempty_bucket_stack();
}
/*判断表达式是否有非法符号*/
bool check_exp_notion(char* exp) {
	for (int i = 0; i < strlen(exp); ++i) {
		if (!isDigit(exp[i]) && !isOperator(exp[i])) {
			printf("The operator we support: [+-*/()], you have input %c.\n", exp[i]);
			return False;
		}
	}
	return True;
}

int main(void)
{
	while (1)
	{
		char exp[100] = "\0";
		gets(exp);

		if (!check_exp_notion) {
			printf("Please check the expression and try again.");
		}

		bucket_stack_clear();
		if (!check_exp_bucket(exp)) {
			printf("Please check the expression and try again.\n");
		}

		int result = calculate(exp, True, True);
		if (result != EMPTY_NUM) {
			printf("The result is %d\n", result);
		}
		else {
			printf("You can input [help] to know more.\n");
		}
	}
	

	system("pause");
	return 0;
}

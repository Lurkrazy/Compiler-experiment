#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int error;
int num;
char lookahead;
ifstream in("input.txt");
ofstream out("output.txt");
string s;


void match(char ch)
{
	if (ch == lookahead || isdigit(lookahead)) {
		lookahead = s[++num];
	}
	else out << "ch = " << ch << "与 lookahead = " << lookahead << "不匹配" << endl;
}

void T();
void G();
void E();
void F();
void H();

void E()
{
	T();
	G();
}

void G()
{
	if (lookahead == '+') {
		match('+');
		T();
		G();
	}
	else if (lookahead == '-') {
		match('-');
		T();
		G();
	}
}

void T()
{
	F();
	H();
}

void H()
{
	if (lookahead == '*') {
		match('*');
		F();
		H();
	}
	else if (lookahead == '/') {
		match('/');
		F();
		H();
	}
}

void F()
{
	if (lookahead == 'i' || isdigit(lookahead)) {
		match('i');
	}
	else if (lookahead == '(') {
		match('(');
		E();
		if (lookahead == ')') {
			match(')');
		}
		else {
			error = 1;//错误状态置为1
			out << "未匹配到右括号')'  ";
		}
	}
	else {
		error = 1;//错误状态置为1
		out << "第" << num + 1 << "个字符'" << lookahead << "'匹配错误  ";
	}
}

int main()
{
	int number = 0;
	while (!in.eof()) {
		out << ++number << " : ";//计数，没啥鬼用
		num = 0;//数组下标指针初始化为0
		s = "";//s初始化为空
		error = 0;//error状态表示是否产生了错误，初始化为0表示未产生错误
		getline(in, s);//读入一行表达式存放在s中
		lookahead = s[0];
		E();
		out ;
		if (lookahead == '\0' && !error) {
			out << "表达式" << s << "正确" << endl;
		}
		else out <<"\n\t表达式" << s << "错误" << endl;
	}
	return 0;
}
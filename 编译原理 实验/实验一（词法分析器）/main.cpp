#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0])) //数组元素个数

using namespace std;

int lookup(string s)//查找s是否在保留字表keyword中
{
	string keyword[] = { "void","main","short","long","int","double","float","while","if","else","for","break","return" };//keyword表
	for (int i = 0; i < ARRAY_SIZE(keyword); i++) {
		if (s.compare(keyword[i]) == 0)return 1;//是保留字，返回1
	}
	return 0;//不是保留字，返回0
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	string s;
	char ch;

	ch = in.get();

	while (!in.eof()) {
		if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {//识别分界符 4
			out << "<" << ch << ",4>\n";
			ch = in.get();
		}
		else if (isdigit(ch)) {//识别整数 5 / 实数 6
			s = "";
			while (isdigit(ch)) {
				s += ch;
				ch = in.get();
				if (ch == '.') {//出现小数点，有可能是常实数
					s += ch;
					ch = in.get();
					if (isdigit(ch)) {
						while (isdigit(ch)) {
							s += ch;
							ch = in.get();
						}
						out << "<" << s << ",6>\n";//常实数
						break;
					}
					else out << s + " is error!\n";//如果小数点后没有数字，则报错
				}
				if (!isdigit(ch)) {
					out << "<" << s << ",5>\n";//常整数
					break;
				}
			}
		}
		else if (isalpha(ch) || ch == '_') {//识别标识符 1 / 保留字 2
			s = "";
			while (isalpha(ch) || isdigit(ch)||ch =='_') {
				s += ch;
				ch = in.get();
			}
			if (lookup(s)) {//在keyword表中查找s是否是保留字
				out << "<" << s << ",2>\n";//保留字
			}
			else out << "<" << s << ",1>\n";//标识符
		}
		//后面都是运算符 3
		else if (ch == '>') {
			s = "";
			s += ch;
			ch = in.get();
			if (ch == '=') {//">="
				s += ch;
				ch = in.get();
			}
			out << "<" << s << ",3>\n";
		}
		else if (ch == '<') {
			s = "";
			s += ch;
			ch = in.get();
			if (ch == '=') {//"<="
				s += ch;
				ch = in.get();
			}
			else if (ch == '>') {//"<>"
				s += ch;
				ch = in.get();
			}
			out << "<" << s << ",3>\n";
		}
		else if (ch == '=') {
			s = "";
			s += ch;
			ch = in.get();
			if (ch == '=') {//"=="
				s += ch;
				ch = in.get();
			}
			out << "<" << s << ",3>\n";
		}
		else {//跳过当前单词
			ch = in.get();
		}
	}
	return 0;
}

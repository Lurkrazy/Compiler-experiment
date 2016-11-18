#include "initialForm.h"

int main()
{
	initialMap();
	cout << "请输入需要分析的字符串，按回车开始分析：" << endl;
	cin >> input;//输入串存在input中
	input[input.length()] = '$';//将输入串尾部赋为'$'
	Stack.push('$');//初始化栈
	Stack.push('E');
	X = Stack.top();//将栈顶元素赋值给X
	while (X != '$') {
		a = input[index];//a是当前input串指针指向的元素
		x = notTerSym[X];//x对应的预测表达式的一维坐标
		y = terSym[a];//a对应的预测表达式的二维坐标
		if (X == a) {//X等于input串指针指向的元素
			Stack.pop();
			index++;
		}
		else if (isTerSym(X)) {//X是一个终结符
			cout <<"栈顶字符"<<X<<"与输入串第"<<index+1<< "个字符'"<<a<<"'不匹配" << endl;
			break;
		}
		else if (form[x][y].empty()) {//预测分析表中匹配到一个error项
			cout <<"匹配输入串中第"<<index+1<<"个字符'"<<a<<"'时发生错误" << endl;
			break;
		}
		else {//在预测分析表中找到了匹配的产生式
			cout << "匹配 " << X << "->" << form[x][y] << endl;
			Stack.pop();
			
			if (form[x][y] == "#") {//如果产生式是X->#
				//不需要压入栈Stack
			}
			else {
				for (int i = form[x][y].length()-1; i >= 0; i--) {//将产生式右部倒序压入栈
					Stack.push(form[x][y][i]);
				}
			}
		}
		X = Stack.top();//X重新赋值为栈顶元素
	}
	if (index == input.length()) cout << "分析成功，此表达式正确" << endl;
	else cout << "分析失败，此表达式错误" << endl;
	cout << "\n按回车退出....." << endl;
	cin.get();
	cin.get();
	return 0;
}
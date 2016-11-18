#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<stack>
using namespace std;

char S;  //开始符
string VT,VN; //VT表示终结符，VN表示非终结符
set<string> Pro[300];  //产生式
map<string,set<char>> FIRSTS,FIRST;
map<char,set<char>> FIRSTA,FOLLOW; //first集和follow集
string M[300][300];
stack<char> Stack;

void createFIRST();  //构建非终结符和终结符的first集合
void createFIRST(string s);  //构建符号串α的first集合
void createFOLLOW(); //构建非终结符的follow集合
void createMATRIX();  //构造预测分析表
void Parser(string s);    //语法分析
set<char> Union(set<char> A,set<char> B,bool &Change,bool lim);

void Init() {
	S = 'E';
	VN = "ESTQF";
	VT = "i+-*/()";
	Pro['E'].insert("TS");
	Pro['S'].insert("+TS");
	Pro['S'].insert("-TS");
	Pro['S'].insert("$");
	Pro['T'].insert("FQ");
	Pro['Q'].insert("*FQ");
	Pro['Q'].insert("/FQ");
	Pro['Q'].insert("$");
	Pro['F'].insert("(E)");
	Pro['F'].insert("i");
}

int main()
{
	char ch,t;
	string s;
	Init();
	printf("请输入句子(以#结束)\n");
	cin >> s;
	Parser(s);
	system("pause");
	return 0;
}

void Parser(string s)
{
	int i;
	createFIRST();  //构造所有终结符和非终结符的first集合
	for(i = 0; i < VN.size(); i++) {
		for(set<string>::iterator it = Pro[VN[i]].begin(); it != Pro[VN[i]].end(); it++) {
			createFIRST(*it);  //构造所有符号串的first集合
		}
	}
	createFOLLOW(); //构造非终结符的follow集合
	createMATRIX(); //构造预测分析表
	Stack.push('#'); //将界定符'#'压入栈
	Stack.push(S);  //将开始符压入栈
	i = 0; 
	string inStack = "#",tmp;
	inStack += S;
	bool flag = true;
	int step = 1;
	printf("分析步骤\tSTACK栈\t\t剩余输入符号串\t\t动作/使用的产生式\n");
	while(flag) {
		if(s[i] == '#') {
			int a = 1;
		}
		char ch = Stack.top();
		tmp = s.substr(i,s.npos);
		cout << step++ << "\t\t" << inStack << "\t\t" << tmp << "\t\t\t";
		if(VN.find(ch) != VN.npos) { //ch属于非终结符
			tmp = M[ch][s[i]]; //M[X,a] == X->Y1Y2...Yk
			if(tmp.size() == 0) {
				cout << "错误" << endl;
				if(s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-' || s[i] == '#') {
					cout << "在" << s[i] << "附近" << "缺少i" << endl;
				} else if(s[i] == '(') {
					cout << "在(附近缺少运算符" << endl;
				} else if(s[i] != 'i') {
					cout << "未定义标识符" << s[i] << endl;
				} else if(s[i] == 'i') {
					cout << "在i附近缺少运算符" << endl;
				} 
				break;
			}
			cout << "推导/" << ch << "->" << tmp << endl;
			Stack.pop();    //弹出X,把YK,Yk-1，...,Y1以此压入栈，Y1在栈顶
			inStack.erase(inStack.size()-1);
			if(tmp[0] == '$') continue;
			for(int j = tmp.size() - 1; j >= 0; j--) {
				Stack.push(tmp[j]); 
				inStack += tmp[j];
			}
		} else if(ch == s[i]) { //ch属于终结符
			if(ch == '#') {
				cout << "分析成功" << endl;
				flag = false;
				break;
			}
			else {
				cout << "匹配" << endl;
				Stack.pop();
				inStack.erase(inStack.size()-1);
				i++;
			}
		} else {
			cout << "错误" << endl;
			if(s[i] == ')') {
				cout << "缺少" << s[i] << endl;
			} else {
				cout << "缺少" << ch << endl;
			}
			break;
		}
	}
	if(flag == false)
		printf("语法分析成功\n");
	else printf("语法错误\n");
}

void createFIRST()
{
	bool Change;
	string tmp;
	FIRSTA.clear(); 
	FOLLOW.clear();
	for(int i = 0; i < VT.size(); i++) {
		tmp = VT[i];
		FIRST[tmp].insert(VT[i]);
	}
	tmp = "$";
	FIRST[tmp].insert('$');
	do {
		Change = false;
		for(int i = 0; i < VN.size(); i++) {
			string P; //非终结符P 
			P = VN[i];
			for(set<string>::iterator it = Pro[VN[i]].begin(); it != Pro[VN[i]].end(); it++) {
				string s = *it;
				int k = 0;
				bool cont = true;
				while(cont && k < s.size()) {
					tmp = s[k];
					FIRST[P] = Union(FIRST[P], FIRST[tmp], Change, true);
					if(FIRST[tmp].find('$') == FIRST[tmp].end()) cont = false;
					k++;
				}
				if(cont) FIRST[P].insert('$');
			}
		}
	}while(Change == true);
}

void createFIRST(string s)
{
	if(s.size() == 1 && VT.find(s[0]) != VT.npos) return;
	int k = 1;
	string tmp;
	bool Change;
	for(int i = 0; i < s.size(); i++) {
		tmp = s[i];
		FIRST[s] = Union(FIRST[s],FIRST[tmp],Change,true);
		if(FIRST[tmp].find('$') != FIRST[tmp].end()) k++;
		else break;
	}
	if(k == s.size()) FIRST[s].insert('$');
}

void createFOLLOW()
{
	bool Change;
	FOLLOW[S].insert('#');
	do {
		Change = false;
		for(int i = 0; i < VN.size(); i++) {
			for(set<string>::iterator it = Pro[VN[i]].begin(); it != Pro[VN[i]].end(); it++) {
				string s = *it;
				for(int j = 0; j < s.size(); j++) {
					//if Q∈VN
					// FOLLOW(Q) = FOLLOW(Q)∪FIRST(β)-{ε}
					//if ε∈ FIRST(β)
					// FOLLOW(Q) = FOLLOW(Q) ∪ FOLLOW(P) 
					if(VN.find(s[j]) != VN.npos && j < s.size() - 1) {  //非终结符
						string tmp = s.substr(j+1,VN.npos);
						FOLLOW[s[j]] = Union(FOLLOW[s[j]],FIRST[tmp],Change,true);
						if(FIRST[tmp].find('$') != FIRST[tmp].end()) 
							FOLLOW[s[j]] = Union(FOLLOW[s[j]],FOLLOW[VN[i]],Change,false);
					}
					else if(VN.find(s[j]) != string::npos && j == s.size() - 1) {
						FOLLOW[s[j]] = Union(FOLLOW[s[j]],FOLLOW[VN[i]],Change,false);
					}
				}
			}
		}
	}while(Change == true);
}

set<char> Union(set<char> A,set<char> B,bool &Change,bool lim)
{
	if(B.size() == 0) return A;
	for(set<char>::iterator it = B.begin(); it != B.end(); it++) {

		if(*it == '$' && lim) continue;   //用$代替ε
		if(A.find(*it) == A.end()) {
			A.insert(*it);
			Change = true;
		}
	}
	return A;
}

void createMATRIX()
{
	for(int i = 0; i < VN.size(); i++) {
		for(set<string>::iterator it = Pro[VN[i]].begin(); it != Pro[VN[i]].end(); it++) {
			string s = *it;  //得到产生式 P -> α

			for(int j = 0; j < VT.size(); j++) {
				if(FIRST[s].find(VT[j]) != FIRST[s].end()) {
					M[VN[i]][VT[j]] = s;   //每个终结符a∈FIRST(α),把P->α放入M[P,a]	
				}
			} //end for

			if(FIRST[s].find('$') != FIRST[s].end()) {  //ε∈FRIST(α)
				for(set<char>::iterator iter = FOLLOW[VN[i]].begin(); iter != FOLLOW[VN[i]].end(); iter++) {
					M[VN[i]][*iter] = s;   //把每个b∈FOLLOW(P),把P->α放入M[P,b]
				}  //end for
			}  //end if
		} //end for
	}
	printf("\n\n\t\t\t预测分析表\n\t");
	for(int i = 0; i < VT.size(); i++)
		printf("%c\t",VT[i]);
	printf("#\t\n");
	for(int i = 0; i < VN.size(); i++) {
		printf("%c\t",VN[i]);
		for(int j = 0; j < VT.size(); j++) {
			cout << M[VN[i]][VT[j]] << '\t';
		}
		cout << M[VN[i]]['#'] << endl;
	}
	printf("\n\n");
}
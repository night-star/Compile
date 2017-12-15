// Compile.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>  
#include <math.h> 
#include<F:\\文档\\我的程序\\VC\\Compile\\Compile\\table.h>
#include<stack>
using namespace std;
void P();//程序
void FP();//分程序
void CS();//常量说明
void CD();//常量定义
void VS();//变量说明
void GS();//过程说明
void GH();//过程首部
void SE();//语句
void FS();//赋值语句
void HS();//复合语句
void T();//条件
int GX();//关系运算符
void FO();//表达式
void X();//项
void YZ();//因子
void IS();//条件语句
void PS();//过程调用
void RS();//读语句
void DWS();//当型循环语句
void WS();//写语句
void error();
string getID(string a);
double getSval(string a);
string key[14] = { "program","const","var","procedure","begin","end","if","else","then","call","read","write","while","do" };
string dou[6] = { ">=","<=",":=","||","&&" ,"<>"};
char word[20];
Table *table = new Table();
Code *code = new Code();
Cal *cal = new Cal();
string fas[10] = {"main"};
int father = 0;//父亲的下标
void fit(string a,int ca,ofstream* of) {
	int fit = 0;
	switch (ca)
	{
	case 0:
		fit = 0;
		for (int i = 0; i < 14; i++) {
			if (a == key[i]) {
				*of << a << "SYM,_,_" << endl;
				fit = 1;
				break;
			}
		}
		if (fit == 0) {
			*of << "idSYM," << a << ",_" << endl;
		}
		break;
	case 1:
		fit = 0;
		for (int i = 0; i < 6; i++) {
			if (a == dou[i]) {
				*of << a << ",_,_" << endl;
				fit = 1;
				break;
			}
		}
		if (fit == 0) {
			while (a[fit] != '\0') {
				*of << a[fit] << ",_,_" << endl;
				fit++;
			}
		}
		
			break;
	case 2:
		*of << "numSYM" << ",_," << a << endl;
		break;
	default:
		break;
	}
	
}
int row = 0;
string relex;
string geta() {
	ifstream fin(relex);
	string s;
	int i = 0;
	while (i<=row)
	{
		getline(fin, s);
		i++;
	}
	//cout << "geta:\t" << s << endl;
	return s;
}
void error() {
	cout << "wrong" << endl;
	system("pause");
}
string getID(string a) {
	string id;
	char id1[20];
	int i = 6;
	for (i = 6;; i++)
	{
		if (a[i] == ',')
			break;
		id1[i - 6] = a[i];
	}
	id1[i - 6] = '\0';
	id = id1;//得到id
	return id;
}
double getSval(string a) {
	double val;
	char val1[20];
	int i = 9;
	for (i = 9;; i++)
	{
		if (a[i] == '\0')
			break;
		val1[i - 9] = a[i];
	}
	val1[i - 9] = '\0';
	val = atof(val1);//得到val
	return val;
}
void P() {
	cout << "start P" << endl;
	table->inName("main","NoFather",0);
	FP();
	cout << "end P" << endl;
}
void FP() {
	cout << "start FP" << endl;
	while (!geta().empty()) {
		string a = geta();
		if (0 == strcmp(a.substr(0, 3).data(), "end"))
			break;
		CS();
		VS();
		GS();
		SE();
	}
	cout << "end FP" << endl;
}
void CS() {
	cout << "start CS" << endl;
	string a = geta();
	if (0==strcmp(a.substr(0, 5).data(),"const")) {
		row++;//跳过const
		CD();
		a = geta();
		while (0==strcmp(a.substr(0, 1).data(),",")) {
			row++;
			CD();
			a = geta();
		}
		if (0 == strcmp(a.substr(0, 1).data(), ";"))
			row++;
		else
			error();
	}
	cout << "end CS" << endl;
}
void CD() {
	cout << "start CD" << endl;
	string a = geta();
	string id;
	double val;
	if (0 == strcmp(a.substr(0, 2).data(), "id")) {
		id = getID(a);
		row++;
		a = geta();
		if (0 == strcmp(a.substr(0, 1).data(), "=")) {
			row++;
			a = geta();
			if (0 == strcmp(a.substr(0, 3).data(), "num")) {
				row++;
				val = getSval(a);//得到val
				table->inId(id, val, 1);
			}
			else {
				error();
			}
		}
		else
			error();
		
	}
	cout << "end CD" << endl;
}
void VS() {
	cout << "start VS" << endl;
	string a = geta();
	string id;
	if (0 == strcmp(a.substr(0, 3).data(), "var")) {
		row++;
		a = geta();
		if (0 == strcmp(a.substr(0, 2).data(), "id")) {
			row++;
		}
		id = getID(a);//得到id
		table->inId(id, 0, 0);
		a = geta();
		while (0 == strcmp(a.substr(0, 1).data(), ",")) {
			row++;
			a = geta();
			if (0 == strcmp(a.substr(0, 2).data(), "id")) {
				row++;
				id = getID(a);//得到id
				table->inId(id, 0, 0);
			}
			else {
				error();
			}
			a = geta();
		}
		if (0 == strcmp(a.substr(0, 1).data(), ";")) {
			row++;
		}
	}
	cout << "end VS" << endl;
}
void GS() {
	cout << "start GS" << endl;
	string a = geta();
	while (0 == strcmp(a.substr(0, 9).data(), "procedure")) {
		code->insert("poc", 0, 0);
		GH();
		FP();
		a = geta();
		if (0 == strcmp(a.substr(0, 3).data(), "end")) {
			row++;
			father -= 1;
			code->insert("end", 0, 0);
		}
		else {
			error();
		}
	}
	a = geta();
	if (0 == strcmp(a.substr(0, 9).data(), "procedure")) {
		GS();
	}
	cout << "end GS" << endl;
}
void GH() {
	cout << "start GH" << endl;
	string a = geta();
	string id;
	if (0 == strcmp(a.substr(0, 9).data(), "procedure")) {
		row++;
		a = geta();
		if (0 == strcmp(a.substr(0, 2).data(), "id")) {
			row++;
			id = getID(a);
			//cout << id <<"                                       "<< fas[father] << endl;
			int design = code->getId();
			table->inName(id,fas[father],design);
			father += 1;
			fas[father] = id;
			a = geta();
			if (0 == strcmp(a.substr(0, 1).data(), ";")) {
				row++;
				a = geta();
				if (0 == strcmp(a.substr(0, 5).data(), "begin")) {
					row++;
					a = geta();
				}
				else
					error();
			}
			else
				error();
		}
		else
			error();
	}
	cout << "end GH" << endl;
}
void SE() {
	cout << "start SE" << endl;
	FS();
	IS();
	DWS();
	PS();
	RS();
	WS();
	HS();
	string a = geta();
	if (0 == strcmp(a.substr(0, 1).data(), ";")) {
		row++;
	}	
	cout << "end SE" << endl;
}
void FS() {
	cout << "start FS" << endl;
	string a = geta();
	while (0 == strcmp(a.substr(0, 2).data(), "id")) {
		row++;
		string id = getID(a);
		
		a = geta();
		if (0 == strcmp(a.substr(0, 2).data(), ":=")) {
			row++;
			FO();
			a = geta();
			if (0 == strcmp(a.substr(0, 1).data(), ";")) {
				row++;
				int index = table->search(fas[father], id);
				if (table->con[index] == 1) {
					code->insert("lit", 0, table->val[index]);
				}
				else {
					code->insert("str", index, index);
				}
			}
			else {
				error();
			}
		}
		else
			error();
		a = geta();
	}
	cout << "end FS" << endl;
}
void HS() {
	cout << "start HS" << endl;
	string a = geta();
	while (0 == strcmp(a.substr(0, 5).data(), "begin")) {
		row++;
		SE();
		a = geta();
		while (0 != strcmp(a.substr(0, 3).data(), "end")) {
			SE();
			a = geta();
		}
		row++;
	}
	cout << "end HS" << endl;
}
void T() {
	cout << "start T" << endl;
	string a = geta();
	if (0 == strcmp(a.substr(0, 3).data(), "odd")) {
		FO();
	}
	else {
		FO();
		int i = GX();
		FO();
		if (i == 0) {
			code->insert("opr", 0, 10);
		}
		if (i == 1) {
			code->insert("opr", 0, 9);
		}
		if (i == 2) {
			code->insert("opr", 0, 5);
		}
		if (i == 3) {
			code->insert("opr", 0, 8);
		}
		if (i == 4) {
			code->insert("opr", 0, 6);
		}
		if (i == 5) {
			code->insert("opr", 0, 7);
		}
	}
	cout << "end T" << endl;
}
int GX() {
	cout << "start GX" << endl;
	string fu[6] = { "=","#","<","<=",">" ,">=" };
	string a = geta();
	char b[3];
	int i = 0;
	while (a[i] != ',') {
		b[i] = a[i];
		i++;
	}
	b[i] = '\0';
	i = 0;
	int p = 0;
	while (i<6)
	{
		if (0 == strcmp(b, fu[i].data())) {
			p = 1;
			break;
		}
		i++;
	}
	if (p == 1) {
		row++;
		return i;
	}
	else {
		error();
		return -1;
	}
	cout << "end GX" << endl;
}
void FO() {
	cout << "start FO" << endl;
	string a = geta();
	if (0 == strcmp(a.substr(0, 1).data(), "+") || 0 == strcmp(a.substr(0, 1).data(), "-")) {
		row++;
		if(0 == strcmp(a.substr(0, 1).data(), "+"))
			code->insert("opr", 0, 2);
		else
			code->insert("opr", 0, 1);
	}
	X();
	a = geta();
	if (0 == strcmp(a.substr(0, 1).data(), "+")|| 0 == strcmp(a.substr(0, 1).data(), "-"))
	{
		row++;
		
		X();
		if (0 == strcmp(a.substr(0, 1).data(), "+"))
			code->insert("opr", 0, 2);
		else
			code->insert("opr", 0, 1);
	}
	cout << "end FO" << endl;
}
void X() {
	cout << "start X" << endl;
	YZ();
	string a = geta();
	if (0 == strcmp(a.substr(0, 1).data(), "*") || 0 == strcmp(a.substr(0, 1).data(), "/"))
	{
		row++;
		
		YZ();
		if (0 == strcmp(a.substr(0, 1).data(), "*"))
			code->insert("opr", 0, 4);
		else
			code->insert("opr", 0, 3);
	}
	cout << "end X" << endl;
}
void YZ() {
	cout << "start YZ" << endl;
	string a = geta();
	if (0 == strcmp(a.substr(0, 2).data(), "id")) {
		row++;
		string id;
		id = getID(a);
		int index = table->search(fas[father], id);
		if (table->con[index] == 1) {
			code->insert("lit", 0, table->val[index]);
		}
		else {
			code->insert("lod", index, index);
		}
	}
	else {
		if (0 == strcmp(a.substr(0, 3).data(), "num")) {
			row++;
			double number = getSval(a);
			code->insert("lit", 0, number);
		}
		else {
			if (0 == strcmp(a.substr(0, 1).data(), "(")) {
				row++;
				FO();
				a = geta();
				if(0 == strcmp(a.substr(0, 1).data(), ")")){
					row++;
				}
				else {
					error();
				}
			}
			else {
				error();
			}
		}
	}
	cout << "end YZ" << endl;
}
void IS() {
	cout << "start IS" << endl;
	string a = geta();
	while (0 == strcmp(a.substr(0, 2).data(), "if")) {
		row++;
		T();
		code->insert("jpc", 0, 0);
		int codenum = code->getId() - 1;
		a = geta();
		if (0 == strcmp(a.substr(0, 4).data(), "then")) {
			row++;
			SE();
		}
		int coden = code->getId();
		code->change(codenum, "jpc", 0, coden);
	}
	cout << "end IS" << endl;
}
void PS() {
	cout << "start PS" << endl;
	string a = geta();
	while (0 == strcmp(a.substr(0, 4).data(), "call")) {
		row++;
		a = geta();
		if (0 == strcmp(a.substr(0, 2).data(), "id")) {
			row++;
			string id = getID(a);
			int index = table->searchp(id);
			int design = table->val[index];
			code->insert("cal", 0, design);
		}
		else {
			error();
		}
	}
	cout << "end PS" << endl;
}
void DWS() {
	cout << "start DWS" << endl;
	string a = geta();
	while (0 == strcmp(a.substr(0, 5).data(), "while")) {
		row++;
		int codenum = code->getId() - 1;
		T();
		code->insert("jpc", 0, 0);
		int codep = code->getId() - 1;
		a = geta();
		if (0 == strcmp(a.substr(0, 2).data(), "do")) {
			row++;
			SE();
		}
		else {
			error();
		}
		int coden = code->getId();
		code->insert("jmp", 0, codenum+1);
		code->change(codep, "jpc", 0, coden+1);
	}
	cout << "end DWS" << endl;
}
void RS() {
	cout << "start RS" << endl;
		string a = geta();
		while (0 == strcmp(a.substr(0, 4).data(), "read")) {
			row++;
			a = geta();
			if (0 == strcmp(a.substr(0, 1).data(), "(")) {
				row++;
				a = geta();
			}
			else {
				error();
			}
			if (0 == strcmp(a.substr(0, 2).data(), "id")) {
				row++;
				code->insert("opr", 0, 16);
				string id = getID(a);
				int index = table->search(fas[father], id);
				code->insert("str", index, index);
				a = geta();
				while (0 == strcmp(a.substr(0, 1).data(), ",")) {
					row++;
					a = geta();
					if (0 == strcmp(a.substr(0, 2).data(), "id")) {
						row++;
						code->insert("opr", 0, 16);
						string id = getID(a);
						int index = table->search(fas[father], id);
						code->insert("str", index, index);
					}
					else {
						error();
					}
					a = geta();
				}
			}
			if (0 == strcmp(a.substr(0, 1).data(), ")")) {
				row++;
				a = geta();
			}
			else {
				error();
			}
		}
		cout << "end RS" << endl;
	}
void WS() {
	cout << "start WS" << endl;
	string a = geta();
	while (0 == strcmp(a.substr(0, 5).data(), "write")) {
		row++;
		a = geta();
		if (0 == strcmp(a.substr(0, 1).data(), "(")) {
			row++;
			a = geta();
		}
		else {
			error();
		}
		if (0 == strcmp(a.substr(0, 2).data(), "id")) {
			row++;
			string id = getID(a);
			int index = table->search(fas[father], id);
			if (table->con[index] == 1) {
				code->insert("lit", 0, table->val[index]);
			}
			else {
				code->insert("lod", index, index);
			}
			code->insert("opr", 0, 15);
			a = geta();
			while (0 == strcmp(a.substr(0, 1).data(), ",")) {
				row++;
				a = geta();
				if (0 == strcmp(a.substr(0, 2).data(), "id")) {
					row++;
					string id = getID(a);
					int index = table->search(fas[father], id);
					if (table->con[index] == 1) {
						code->insert("lit", 0, table->val[index]);
					}
					else {
						code->insert("lod", index, index);
					}
					code->insert("opr", 0, 15);
				}
				else {
					error();
				}
				a = geta();
			}
		}
		if (0 == strcmp(a.substr(0, 1).data(), ")")) {
			row++;
			a = geta();
		}
		else {
			error();
		}
	}
	cout << "end WS" << endl;
	}
int main(int arg,char* argv[])
{

	if (arg == 1) {
		cout << "Please input the operation" << endl;
		cout << "-h for help" << endl;
		system("pause");
	}
	else {
		if (0 == strcmp(argv[1], "-c")) {
			string sou, mu;
			cout << "Please input the path of the source code" << endl;
			cin >> sou;
			cout << "Please input the path of the lexical analysis" << endl;
			cin >> mu;
			ifstream fin(sou);
			ofstream ofile(mu);
			string s;
			int i = 0;//读取每一行每个字符
			int t = 0;//匹配//
			int st = 0;//匹配/* */
			int index = 0;//符号的下标
			int cas = 0;//种类 0字串 1符号串 2数字
			while (getline(fin, s))
			{
				i = 0;
				t = 0;
				while (s[i] != '\0')
				{
					if (s[i] == '/'&&s[i + 1] == '/')
					{
						t = 1;
					}
					if (s[i] == '/'&&s[i + 1] == '*')
					{
						st = 1;
					}
					if (s[i] == '*'&&s[i + 1] == '/')
					{
						st = 0;
						s[i] = ' ';
						s[i + 1] = ' ';
					}
					if (st == 1)
						s[i] = ' ';
					else
					{
						if (t == 1)
							s[i] = ' ';
						else
						{
							if ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z')) {//字母
								if (cas == 0) {
									word[index] = s[i];
									index++;
								}
								else {
									string c = word;
									if (word[0] != '\0') {
										fit(c, cas, &ofile);
										memset(word, 0, sizeof(word));
									}
									cas = 0;
									index = 0;
									word[index] = s[i];
									index++;
								}
							}
							if ((s[i] >= '0'&&s[i] <= '9') || s[i] == '.') {//数字
								if (cas == 1) {
									string c = word;
									if (word[0] != '\0') {
										fit(c, cas, &ofile);
										memset(word, 0, sizeof(word));
									}
									index = 0;
									cas = 2;
									word[index] = s[i];
									index++;
								}
								else {
									if (index == 0) cas = 2;
									word[index] = s[i];
									index++;
								}
							}
							if (s[i] == ' ') {//空格
								string c = word;
								if (word[0] != '\0') {
									fit(c, cas, &ofile);
									memset(word, 0, sizeof(word));
								}
								index = 0;
							}
							if (s[i] == '+'||s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')' || s[i] == ',' || s[i] == ';' || s[i] == '}' || s[i] == '{' || s[i] == '<' || s[i] == '>' || s[i] == '=' || s[i] == ':' || s[i] == '|' || s[i] == '&'||s[i]=='#') {//单符号
								if (cas == 1) {
									word[index] = s[i];
									index++;
								}
								else {
									string c = word;
									if (word[0] != '\0') {
										fit(c, cas, &ofile);
										memset(word, 0, sizeof(word));
									}
									cas = 1;
									index = 0;
									word[index] = s[i];
									index++;
								}

							}
							if (s[i] == '-') {
								if (s[i + 1] >= '0'&&s[i + 1] <= '9') {
									if (cas == 1) {
										string c = word;
										if (word[0] != '\0') {
											fit(c, cas, &ofile);
											memset(word, 0, sizeof(word));
										}
										index = 0;
										cas = 2;
										word[index] = s[i];
										index++;
									}
									else {
										if (index == 0) cas = 2;
										word[index] = s[i];
										index++;
									}
								}
								else {
									if (cas == 1) {
										word[index] = s[i];
										index++;
									}
									else {
										string c = word;
										if (word[0] != '\0') {
											fit(c, cas, &ofile);
											memset(word, 0, sizeof(word));
										}
										cas = 1;
										index = 0;
										word[index] = s[i];
										index++;
									}
								}
							}
						}
					}
					i++;
				}
				string c = word;
				if (word[0] != '\0') {
					fit(c, cas, &ofile);
					memset(word, 0, sizeof(word));
				}
				index = 0;

			}
		}
		if (0 == strcmp(argv[1], "-g")) {
			cout << "Please input the path of the result of lexical analysis" << endl;
			cin >> relex;
			//relex = "F:\\文档\\我的程序\\VC\\Compile\\Debug\\a.txt ";
			cout << relex << endl;
			P();
			cout << "**************************** Debug Information ****************************" << endl << endl;
			cout << "Symbol Table:" << endl;
			table->optput();
			cout << "************************" << endl << endl;
			cout << "Middle Code:" << endl;
			code->output();
			
		}
		if (0 == strcmp(argv[1], "-p")) {
			cout << "Please input the path of the result of lexical analysis" << endl;
			cin >> relex;
			//cout << relex << endl;
			
			P();
			cout << "**************************** Debug Information ****************************" << endl << endl;
			cout << "Console:" << endl << endl;
			int ex = 1;
			stack<int> *ret = new stack<int>();//返回地址
			stack<double> *s = new stack<double>();//运算栈
			for (int i = 0; i < code->idn; i++) {
				if (code->ops[i].compare("poc") == 0) {
					//cout << i << endl;
					ex = 0;
				}
				if (code->ops[i].compare("end") == 0) {
					if (ex == 0)
						ex = 1;
					else {
						i = ret->top();
						//cout << i << " eeeeeeeeee" << endl;
						continue;
					}
				}
				if (ex == 1) {
					if (code->ops[i].compare("opr") == 0) {
						double a, b;
						if ((int)code->as[i] < 15) {
							b = s->top();
							s->pop();
							a = s->top();
							s->pop();
						}
						else {
							if ((int)code->as[i] == 15) {
								a = s->top();
								s->pop();
							}
						}
						if ((int)code->as[i] == 0) {
							system("pause");
						}
						if ((int)code->as[i] == 1) {
							double val1 = a - b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 2) {
							double val1 = a + b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 3) {
							double val1 = a / b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 4) {
							double val1 = a * b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 5) {
							bool val1 = a < b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 6) {
							bool val1 = a > b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 7) {
							bool val1 = a >= b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 8) {
							bool val1 = a <= b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 9) {
							bool val1 = a != b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 10) {
							bool val1 = a == b;
							double c = val1;
							s->push(c);
						}
						if ((int)code->as[i] == 15) {
							cout << a << endl;
						}
						if ((int)code->as[i] == 16) {
							double temp;
							cout << "input requst:";
							cin >> temp;
							double c= temp;
							s->push(c);
						}
					}
					if (code->ops[i].compare("lit") == 0) {
						double c = code->as[i];
						s->push(c);
					}
					if (code->ops[i].compare("str") == 0) {
						double temp = s->top();
						s->pop();
						int index = code->ls[i];
						cal->insert(index, temp);
					}
					if (code->ops[i].compare("lod") == 0) {
						int index = code->ls[i];
						double temp = cal->getLocalVal(index);
						s->push(temp);
					}
					if (code->ops[i].compare("jpc") == 0) {
						bool c = s->top();
						s->pop();
						if (!c) {
							int index = (int)code->as[i];
							if (index > code->idn)
								system("pause");
							else {
								i = index-1;
								continue;
							}
						}
					}
					if (code->ops[i].compare("jmp") == 0) {
						int index = (int)code->as[i];
						if (index > code->idn)
							system("pause");
						else {
							i = index - 1;
							continue;
						}
					}
					if (code->ops[i].compare("cal") == 0) {
						int index = (int)code->as[i];
						if (index > code->idn)
							system("pause");
						else {
							ret->push(i);//保存返回地址
							i = index - 1;
							//cout << i << "  ffffffffffff" << endl;
							continue;
						}
					}
				}
			}
			//system("pause");
		}
		if (0 == strcmp(argv[1], "-h")) {
			cout << "-c for lexical analysis" << endl;
			cout << "-g for grammatical analysis" << endl;
			cout << "-p for execute code";
		}
	}
	return 0;
}


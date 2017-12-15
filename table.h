#pragma once
#include <string>
#include<iostream>
using namespace std;
class Table {
public:
	Table();
	//����������ƣ����ŵ�ֵ�������Ƿ�const 1����const 0�����const ;val=1  const>2�������
	void inId(string id, double value, short constT);
	//���������,�Լ����׵�����
	void inName(string name, string Fa,int design);
	//���̽���
	void inEnd(string name);
	//����name�������Ƿ���id����
	int search(string name, string id);
	//����name�Ĺ��̵�λ��
	int searchp(string name);
	//��name�����е�id���Ÿ�ֵvalue
	bool setVal(string name, string id, double value);
	//�õ�name�����е�idֵ
	double getVal(string name, string id);
	//���
	void optput();
	string tid[100];
	double val[100];
	short con[100];
	int num, nump;
};
class Code {
public:
	Code();
	void insert(string op, int l, double a);
	void change(int id, string op, int l, double a);
	int getId();
	void output();
	string ops[100];
	int ls[100];
	double as[100];
	int idn;
};
class Cal {
public:
	Cal();
	double getLocalVal(int l);
	void insert(int l, double v);
	int local[100];
	double val[100];
	int id;
};
Cal::Cal() {
	id = 0;
}
void Cal::insert(int l, double v) {
	int flag = 0;
	for (int i = 0; i < id; i++) {
		if (local[i] == l) {
			val[i] = v;
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		local[id] = l;
		val[id] = v;
		id++;
	}
}
double Cal::getLocalVal(int l) {
	for (int i = 0; i < id; i++) {
		if (local[i] == l)
			return val[i];
	}
	return 0;
}
Code::Code() {
	idn = 0;
}
void Code::insert(string op, int l, double a) {
	ops[idn] = op;
	ls[idn] = l;
	as[idn] = a;
	idn++;
}
void Code::change(int id, string op, int l, double a) {
	ops[id] = op;
	ls[id] = l;
	as[id] = a;
}
int Code::getId() {
	return idn;
}
void Code::output() {
	for (int i = 0; i < idn; i++)
	{
		cout<<i<<"\t" << ops[i] << "\t" << ls[i] << "\t" << as[i] << endl;
	}
}
Table::Table() {
	num = 0;
	nump = 0;

}
void Table::inId(string id, double value, short constT) {
	tid[num] = id;
	val[num] = value;
	con[num] = constT;
	num++;
}
void Table::inName(string name, string Fa,int design) {//con-3 �����Լ��������ڵķ��ű���
	tid[num] = name;
	val[num] = design;
	con[num] = 2;
	for (int i = 0; i < num; i++) {
		if (name.compare("main") == 0) {
			break;
		}
		if (tid[i].compare(Fa) == 0 && con[i]>1) {
			con[num] += i + 1;
		}
	}
	num++;
}
void Table::inEnd(string name) {
	tid[num] = name;
	val[num] = -1;
	con[num] = 3;
	num++;
}
int Table::search(string name, string id) {//����ֵΪ�������е����ꡣ-1Ϊû�ҵ�
	int p = 0;
	int fid = 0;
	for (int i = 0; i < num; i++) {
		if (con[i] >1 && tid[i].compare(name) == 0) {
			p = 1;
			fid = con[i] - 3;
		}
		if (con[i] > 1 && tid[i].compare(name) != 0) {
			p = 0;
		}
		if (p == 1) {
			if (tid[i].compare(id) == 0)
				return i;
		}
	}
	p = 0;
	while (fid != -1) {
		//cout << fid << endl;
		string fa = tid[fid];
		for (int i = 0; i < num; i++) {
			if (con[i] >1 && tid[i].compare(fa) == 0) {
				p = 1;
				fid = con[i] - 3;
			}
			if (con[i] >1 && tid[i].compare(fa) != 0) {
				p = 0;
			}
			if (p == 1) {
				if (tid[i].compare(id) == 0)
					return i;
			}
		}
	}
	return -1;
}
int Table::searchp(string name) {
	for (int i = 0; i < num; i++) {
		cout << tid[i] << "                   " << name << endl;
		if (tid[i].compare(name) == 0) {
		
			return i;
		}
		
	}
	return -1;
}
bool Table::setVal(string name, string id, double value) {
	int a = search(name, id);
	if (a != -1) {
		val[a] = value;
		return true;
	}
	else {
		return false;
	}
}
double Table::getVal(string name, string id) {
	int a = search(name, id);
	if (a != -1) {
		return val[a];
	}
	else {
		
		return -0.000001;
	}
}
void Table::optput() {
	for (int i = 0; i < num; i++) {
		cout << tid[i] << "\t" << con[i] << "\t" << val[i] << endl;
	}
}
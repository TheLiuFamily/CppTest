#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <map>
#include "mycomplex.h"
using namespace std;

class Expression
{
public:
	Expression(const string& str);
	string GetError() const;
private:
	string m_strExp;						//���ʽ�ַ���
	string m_strError;				//����ԭ��

	map<string, double> m_mapDouble;		//�����Ӧ��double
	string m_strDoubleHead;
	int m_nDoubleIndex1;
	int m_nDoubleIndex2;
	string m_strScanDouble;

	map<string, mycomplex> m_mapComplex;	//�����Ӧ�ĸ���
	string m_strComplexHead;
	int m_nComplexIndex1;					//�ַ�����1
	int m_nComplexIndex2;					//�ַ�����2
	string m_strScanComplex;
	string m_strInfix;

	vector<string> m_vecInfix;
	vector<string> m_vecPostfix;

public:
	//����ֵ��ʾ���ʽ�Ƿ���ȷ������comΪ������
	bool Compute(mycomplex& com);
protected:
	//������������������Ƿ��Ƕ�Ӧ
	bool CheckParenthesis(const string& str);
	//��������ŵ���һ���ַ��Ƿ��ǲ�����
	//��������ŵ���һ���ַ��Ƿ��ǲ�����
	bool CheckOperatorPos(const string& str);
	bool CheckImageFlag(const string& str);
	//���������ת�����ַ�
	string ConvertDouble(const string& str);
	string AddMapDoubleMember(double d);
	string ConvertComplex(const string& str);
	string AddMapComplexMember(mycomplex com);
	string ConvertDoubleToComplex(const string& str);
	vector<string> ConvertStringToInfix(const string& str);
	vector<string> ConvertInfixToPostfix(vector<string>& vec);
	int Level(string c);
	mycomplex Compute2(vector<string>& vec, string& str);
	int isOperator(char c);
	bool CheckDotPos(const string& str);
};
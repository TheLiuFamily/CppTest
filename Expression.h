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
	string m_strExp;						//表达式字符串
	string m_strError;				//错误原因

	map<string, double> m_mapDouble;		//保存对应的double
	string m_strDoubleHead;
	int m_nDoubleIndex1;
	int m_nDoubleIndex2;
	string m_strScanDouble;

	map<string, mycomplex> m_mapComplex;	//保存对应的复数
	string m_strComplexHead;
	int m_nComplexIndex1;					//字符索引1
	int m_nComplexIndex2;					//字符索引2
	string m_strScanComplex;
	string m_strInfix;

	vector<string> m_vecInfix;
	vector<string> m_vecPostfix;

public:
	//返回值表示表达式是否正确，参数com为计算结果
	bool Compute(mycomplex& com);
protected:
	//检查左括号与右括号是否是对应
	bool CheckParenthesis(const string& str);
	//检查左括号的下一个字符是否是操作符
	//检查右括号的下一个字符是否是操作符
	bool CheckOperatorPos(const string& str);
	bool CheckImageFlag(const string& str);
	//把相关数字转换成字符
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
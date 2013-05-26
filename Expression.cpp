#include "Expression.h"
Expression::Expression(const string& str)
	: m_strExp(str)
	, m_strDoubleHead("")
	, m_nDoubleIndex1(0)
	, m_nDoubleIndex2(0)
	, m_strScanDouble("")
	, m_strComplexHead("")
	, m_nComplexIndex1(0)
	, m_nComplexIndex2(0)
	, m_strScanComplex("")
	, m_strInfix("")
	, m_strError("")
{

}
string Expression::GetError() const
{
	return m_strError;
}
bool Expression::Compute(mycomplex& com)
{
	if(CheckParenthesis(m_strExp) == false)
	{
		m_strError = "括号不匹配";
		return false;
	}
	if(CheckOperatorPos(m_strExp) == false)
	{
		m_strError = "操作符不对应";
		return false;
	}
	if(CheckDotPos(m_strExp) == false)
	{
		m_strError = "小数点没有填写对";
		return false;
	}
	m_strScanDouble = ConvertDouble(m_strExp);
	if(m_strScanDouble == "error")
	{
		m_strError = "数字输入错误";
		return false;
	}
	m_strScanComplex = ConvertComplex(m_strScanDouble);
	if(CheckImageFlag(m_strScanComplex) == false)
	{
		m_strError = "输入复数格式错误";
		return false;
	}
	m_strInfix = ConvertDoubleToComplex(m_strScanComplex);
	m_vecInfix = ConvertStringToInfix(m_strInfix);
	m_vecPostfix = ConvertInfixToPostfix(m_vecInfix);
	string str("");
	com = Compute2(m_vecPostfix, str);
	if(str == "error")
	{
		m_strError = "输入表达式错误";
		return false;
	}
	return true;
}
bool Expression::CheckImageFlag(const string& str)
{
	size_t found = str.find('i');
	if(found != string::npos)
		return false;
	return true;
}


bool Expression::CheckParenthesis(const string& str)
{
	stack<char> s;
	for(int i = 0; i != str.size(); i++)
	{
		if(str[i] == '(')
		{
			s.push('(');
		} else if(str[i] == ')')
		{
			if(s.empty())
				return false;
			s.pop();
		}
	}
	if(s.empty())
		return true;
	else
		return false;
}
int Expression::isOperator(char c)
{
	int t = 0;
	switch(c)
	{
	case '+':
		t = 1;
		break;
	case '-':
		t = 2;
		break;
	case '*':
		t = 3;
		break;
	case '/':
		t = 4;
		break;
	case '(':
		t = 5;
		break;
	case ')':
		t = 6;
		break;
	case 'i':
		t = 7;
		break;
	}
	return t;
}
bool Expression::CheckOperatorPos(const string& str)
{
	char c = str[0];
	if(isOperator(c) > 0 && isOperator(c) < 5)
		return false;
	c = str[str.size()-1];
	if(isOperator(c) > 0 && isOperator(c) < 5)
		return false;
	for(int i = 1; i != str.size()-1; i++)
	{
		if(isOperator(str[i]) > 0 && isOperator(str[i]) < 5)
		{
			if(isOperator(str[i-1]) > 0 && isOperator(str[i-1]) < 5)
				return false;
			else if(isOperator(str[i+1]) > 0 && isOperator(str[i+1]) < 5)
				return false;
			else if(isOperator(str[i-1]) == 5)
				return false;
			else if(isOperator(str[i+1]) == 6)
				return false;
		}
	}
	return true;
}
bool Expression::CheckDotPos(const string& str)
{
	if(str[0] == '.' || str[str.size()-1] == '.')
		return false;
	size_t found = str.find('.');
	while(found != string::npos)
	{
		if(isOperator(str[found-1]) || isOperator(str[found+1]))
			return false;
		found = str.find('.', found+1);
	}
	return true;
}

string Expression::ConvertDouble(const string& str)
{
	string result = "";
	for(int i = 0; i != str.size(); ++i)
	{
		string t = "";
		if(isdigit(str[i]))
		{
			if(str[i] == '0')
			{
				if(i+1 != str.size());
				{
					if(isdigit(str[i+1]))
						return string("error");
				}
			}
			t = "";
			t += str[i];
			if(i+1 != str.size())
			{
				while(isdigit(str[i+1]) || str[i+1] == '.')
				{
					++i;
					t += str[i];
				}
			}
			if(t.find('.') != t.rfind('.'))
			{
				return string("error");
			}
			double d = 0;
			d = atof(t.c_str());
			result += AddMapDoubleMember(d);
		}
		else
		{
			result += str[i];
		}
	}
	return result;
}
string Expression::AddMapDoubleMember(double d)
{
	m_strDoubleHead = "d";
	m_strDoubleHead += m_nDoubleIndex1 + '0';
	m_strDoubleHead += m_nDoubleIndex2 + '0';
	m_mapDouble[m_strDoubleHead] = d;
	if(m_nDoubleIndex2 == 9)
	{
		m_nDoubleIndex2 = 0;
		m_nDoubleIndex1++;
	}
	else
		m_nDoubleIndex2++;
	return m_strDoubleHead;
}

string Expression::ConvertComplex(const string& str)
{
	string result;


	if(str.size() < 10)
	{
		result += str;
	} else
	{
		int current = 0;
		for(int i = 0; i < str.size()-9; ++i)
		{
			if(str[i] == '('
				&& m_mapDouble.find(str.substr(i+1, 3)) != m_mapDouble.end()
				&& str[i+4] == '+'
				&& m_mapDouble.find(str.substr(i+5, 3)) != m_mapDouble.end()
				&& str[i+8] == 'i'
				&& str[i+9] == ')')
			{
				result += AddMapComplexMember(mycomplex(m_mapDouble[str.substr(i+1, 3)]
				, m_mapDouble[str.substr(i+5, 3)]));
				i = i+9;
			}else if(str[i] == '('
				&& m_mapDouble.find(str.substr(i+1, 3)) != m_mapDouble.end()
				&& str[i+4] == '-'
				&& m_mapDouble.find(str.substr(i+5, 3)) != m_mapDouble.end()
				&& str[i+8] == 'i'
				&& str[i+9] == ')')
			{
				result += AddMapComplexMember(mycomplex(m_mapDouble[str.substr(i+1, 3)]
				, -m_mapDouble[str.substr(i+5, 3)]));
				i = i+9;
			} else
			{
				result += str[i];
			}
			current = i;
		}
		current++;
		if(current != str.size())
		{
			result += str.substr(current, str.size()-current);
		}
	}
	return result;
}
string Expression::AddMapComplexMember(mycomplex com)
{
	m_strComplexHead = "c";
	m_strComplexHead += m_nComplexIndex1 + '0';
	m_strComplexHead += m_nComplexIndex2 + '0';
	m_mapComplex[m_strComplexHead] = com;
	if(m_nComplexIndex2 == 9)
	{
		m_nComplexIndex2 = 0;
		m_nComplexIndex1++;
	}
	else
		m_nComplexIndex2++;
	return m_strComplexHead;
}

string Expression::ConvertDoubleToComplex(const string& str)
{
	string result;
	if(str.size() < 3)
	{
		result += str;
	} else
	{
		int current = 0;
		for(int i = 0; i < str.size()-2; ++i)
		{
			if(m_mapDouble.find(str.substr(i, 3)) != m_mapDouble.end())
			{
				result += AddMapComplexMember(mycomplex(m_mapDouble[str.substr(i, 3)], 0));
				i = i+2;
			}
			else
			{
				result += str[i];
			}
			current = i;
		}
		current++;
		if(current != str.size())
		{
			result += str.substr(current, str.size()-current);
		}
	}
	return result;
}

vector<string> Expression::ConvertStringToInfix(const string& str)
{
	vector<string> vec;
	if(str.size() < 3)
	{
		vec.push_back(str);
	}
	else
	{
		int current = 0;
		for(int i = 0; i < str.size() - 2; ++i)
		{
			if(m_mapComplex.find(str.substr(i, 3)) != m_mapComplex.end())
			{
				vec.push_back(str.substr(i, 3));
				i = i+2;
			}
			else
			{
				vec.push_back(str.substr(i, 1));
			}
			current = i;
		}
		current++;
		for(int j = current; j != str.size(); ++j)
		{
			vec.push_back(str.substr(j, 1));
		}
	}
	return vec;
}

vector<string> Expression::ConvertInfixToPostfix(vector<string>& vec)
{
	vector<string> result;
	stack<string> s;
	int j = 0;
	for(int i = 0; i != vec.size(); ++i)
	{
		if(vec[i].size() == 3)
		{
			result.push_back(vec[i]);
		}
		else if(s.empty())
		{
			s.push(vec[i]);
		}
		else if(Level(vec[i]) == 4)
		{
			while(Level(s.top()) != 3)
			{
				result.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
		else if(Level(s.top()) == 3)
		{
			s.push(vec[i]);
		}
		else if(Level(s.top()) < Level(vec[i]))
		{
			s.push(vec[i]);
		}
		else if(Level(s.top()) >= Level(vec[i]))
		{ 
			do
			{
				result.push_back(s.top());
				s.pop();
			}while(!s.empty() && Level(s.top()) >= Level(vec[i]) && Level(s.top()) != 3);
			s.push(vec[i]);
		}
	}
	while(!s.empty())
	{
		result.push_back(s.top());
		s.pop();
	}
	return result;
}

int Expression::Level(string c)
{
	int l = 0;
	switch(c[0])
	{
	case '+':
	case '-':
		l = 1;
		break;
	case '*':
	case '/':
		l = 2;
		break;
	case '(':
		l = 3;
		break;
	case ')':
		l = 4;
		break;
	default:
		break;
	}
	return l;
}

mycomplex Expression::Compute2(vector<string>& vec, string& str)
{
	stack<string> s;
	for(int i = 0; i != vec.size(); ++i)
	{
		if(vec[i].size() == 3)
		{
			s.push(vec[i]);
		} else
		{
			mycomplex c1 = m_mapComplex[s.top()];
			s.pop();
			mycomplex c2 = m_mapComplex[s.top()];
			s.pop();
			mycomplex c3(0, 0);
			switch(vec[i][0])
			{
			case '+':
				c3 = c1+c2;
				break;
			case '-':
				c3 = c2-c1;
				break;
			case '*':
				c3 = c1*c2;
				break;
			case '/':
				c3 = c2/c1;
				break;
			}

			s.push(AddMapComplexMember(c3));

		}
	}
	mycomplex result = m_mapComplex[s.top()];
	s.pop();
	if(!s.empty())
	{
		str = "error";
	}
	return result; 
}

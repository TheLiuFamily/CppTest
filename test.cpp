#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	long sum = 0;
	int a[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,
	16384,32768};
	do {
		cout << "请输入二进制数： ";
		cin >> s;
		for(int i = 0; i != s.size(); ++i)
		{
			if(s[i] != '0' || s[i] != '1')
				continue;
		}
		sum = 0;
		if(s.length() >= 32)
			cout << "闹火" << endl;
		cout << s << endl;
		reverse(s.begin(), s.end());
		cout << s << endl;
		for(int i = 0; i != s.size(); ++i)
		{

			if(s[i] == '1')
			{
				sum += a[i];
			}

		}
		cout << "十进制： " << sum << endl;
	} while(s.compare("quit") != 0);

	return 0;
}
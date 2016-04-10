#include "postfix.h"
int main()
{
	try{
	setlocale(0,"");
	string str;
	cout << "������� �������������� ���������:";
	getline(cin, str);
	Postfix<char> postfix;

	string postfix_str = postfix.PostfixForm(str);
	cout << endl << "��������� � ����������� �����: " << postfix_str << endl;

	//cout << "������ ����������� ��������� ��� ��������:" << endl;
	cout << "Result: " << postfix.Calcul(postfix_str);
	
	}
	catch (exception &e)
	{
		cout << e.what()<< endl;
		return 0;
	}
	return 0;
}
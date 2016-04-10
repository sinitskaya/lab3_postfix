#include "postfix.h"
int main()
{
	try{
	setlocale(0,"");
	string str;
	cout << "Введите арифметическое выражение:";
	getline(cin, str);
	Postfix<char> postfix;

	string postfix_str = postfix.PostfixForm(str);
	cout << endl << "Выражение в постфиксной форме: " << postfix_str << endl;

	//cout << "Ведите постфиксное выражение для подсчета:" << endl;
	cout << "Result: " << postfix.Calcul(postfix_str);
	
	}
	catch (exception &e)
	{
		cout << e.what()<< endl;
		return 0;
	}
	return 0;
}
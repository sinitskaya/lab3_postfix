#include "stack.h"
#include <string>
#include <map>
typedef float RT;

template<class VT> 
class Postfix
{
private:
	Stack<VT> operators;
	Stack<VT> arguments;
	
	Stack<RT> S;
	int IsOperator(char) const;
	int IsArgument(char) const;
	//////////////////////////////
	char* Enter (string str, char*alfavit);
	string ReadyString(string str);
	string Newstring(string str, char* chisla, char* alfavit);
	bool GetTwoOperands (RT & op1, RT & op2);
	void Compute (char op);
public:
	Postfix();
	~Postfix();

	string PostfixForm(string);
	///////////////////////////////////
	RT Calcul (string str);
};

template<class VT>
Postfix<VT>:: Postfix()
{}
template<class VT>
Postfix<VT>:: ~Postfix()
{}

template<class VT>
int Postfix<VT>:: IsOperator(char value) const
{
	switch (value)
	{
		case '*': return 1;
		case '/': return 1;
		case '+': return 1;
		case '-': return 1;
		case '(': return 1;
		case ')': return 1;
		case '=': return 1;
		default:
			return 0;
	}
}

template<class VT>
int Postfix<VT>:: IsArgument(char value) const
{
	if ( (IsOperator(value)) || (value == ' ') )
		return 0;
	return 1;
}

template<class VT>
string Postfix<VT>:: PostfixForm(string str)
{
	map <char, int> priority;
	priority ['*'] = 3;
	priority ['/'] = 3;
	priority ['+'] = 2;
	priority ['-'] = 2;
	priority ['('] = 1;
	priority [')'] = 1;
	priority ['='] = 0;

	char value;
	for (unsigned int i=0; i < str.length(); i++)
	{
		value = str[i];
		if (value == ' ')
			continue;
		if (IsOperator(value))
		{
			if ( (value == ')') || (value == '(') )
			{
				if (value == ')')
				{
					while ((!operators.IsEmpty()) && (operators.GetValue() != '('))
						arguments.Push(operators.Pop());
					if (operators.IsEmpty())
						throw exception ("Not correct data");//*
					operators.Pop();
				}
				else
				{
					operators.Push(value);
					continue;
				}
			}
			else
				if (!operators.IsEmpty())
				{
					if (priority[value] <= priority[operators.GetValue()])
					{
						while ((!operators.IsEmpty()) && (priority[value] <= priority[operators.GetValue()]))
							arguments.Push(operators.Pop());
						operators.Push(value);
					}
					else
						operators.Push(value);
				}
				else
					operators.Push(value);
		}
		else
			arguments.Push(value);
	}

	if (!operators.IsEmpty())
		while (!operators.IsEmpty())
			arguments.Push(operators.Pop());

	if (arguments.IsEmpty())
		throw exception ("Not correct data");//*

	while (!arguments.IsEmpty())
		operators.Push(arguments.Pop());

	string str_result = "";
	while (!operators.IsEmpty())
		str_result = str_result + operators.Pop();
	
	for (unsigned int i=0; i < str_result.length(); i++)
	{
		value = str_result[i];
		if (value == '(')
			throw exception ("Not correct data");//*
	}

	return str_result;
}

////////////////////////////////////
template<class VT>
string Postfix<VT>:: ReadyString(string str)
{
	const int N = str.length();
	char *alfavit = new char [N]; //различные буквы
	for (int j=0; j<N; j++)
		alfavit[j]  = '0';
	
	int c=0; int res = 1;
	char ch;
	for (unsigned int i=0; i< str.length(); i++)
	{///заполняет масс различными буквами, без повторений
		ch = str[i];
		if (IsArgument(ch)){
			res = 1;
			for (unsigned int j=0; j< str.length(); j++)
				if (alfavit[j]==ch){
					res = 0;
					break;
				}
			if (res==1){
				alfavit[c] = ch;
				c++;
			}
		}
	}///

	char* chisla = Enter(str,alfavit);
	string newstring = Newstring(str,chisla,alfavit);
	delete [] alfavit;
	delete [] chisla;
	return newstring;
}

template<class VT>
char* Postfix<VT>:: Enter(string str, char *alfavit)
{
	const int N = str.length();
	char *chisla = new char [N];  //числа, которые подставятся вместо букв
	for (int j=0; j<N; j++)
		chisla[j]  = 'z';

	char ch;
	for (int i=0; i<N; i++)
	{
		ch = alfavit[i];
		if (ch!='0')
		{
			cout << "Enter " << ch << ": ";
			cin >> chisla[i];
		}
	}
	return chisla;
}

template<class VT>
string Postfix<VT>:: Newstring(string str, char* chisla, char* alfavit)
{
	const int N = str.length();
	int j=0;
	while (chisla[j]!='z'){//берем из alfavita
		for (int i=0; i<N; i++)
			if (chisla[j]!='0'){
				if (alfavit[j]==str[i])
					str[i] = chisla[j];
			}
			j++;
	}
	return str;
}

template<class VT>
RT Postfix<VT>:: Calcul(string str)
{
	char ch;
	string s1 = ReadyString(str);
	RT newop;
	for (unsigned int i=0; i < s1.length(); i++) 
	{
		ch = s1[i];
		if((ch!=' ')&&(ch != '='))
			switch(ch)
			{
				case '+':
				case '-':
				case '*':
				case '/':
					Compute(ch);
					break;
				default://не оператор вернуть символ
					cin.putback(ch);
					cin>> newop;//читать оператор передать в стек
					S.Push(newop);
					break;
			}
	}

	RT Result;
	if (!S.IsEmpty())
		Result = S.Pop();
	if (!S.IsEmpty())
		cout << "error Calcul"<< endl;
	while (!S.IsEmpty())
		S.Pop();//очистить стек

	return Result;
}

template<class VT>
bool Postfix<VT>:: GetTwoOperands (RT & op1, RT & op2)
{
	if (S.IsEmpty())
	{
		cout<<"false" << endl;
		return false;
	}
	op1 = S.Pop(); //извлечь первый операнд
	if (S.IsEmpty())
	{
		cout<<"false" << endl;
		return false;
	}
	op2 = S.Pop();
	return true;
}

template<class VT>
void Postfix<VT>:: Compute (char op)
{//выполнение операции
	bool result;
	RT op1, op2;
	//извлечь два операнда и получить код завершения
	result = GetTwoOperands(op1,op2);
	//выполнить оператор поместить в стек иначе очистить стек, проверка на деление на 0
	if (result==true)
	switch (op)
	{
	case '+': S.Push(op2+op1); break;
	case '-': S.Push(op2-op1); break;
	case '*': S.Push(op2*op1); break;
	case '/':
		if (op1 == 0)
			throw ("error"); //{ cout << "NULL" << endl;}
		else
			S.Push(op2/op1);
		break;
	}
	else 
		cout << "error1" << endl;
}
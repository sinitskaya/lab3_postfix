#include "stack.h"

int main()
{
	setlocale(0,"");
	Stack <double> *stack = new Stack <double>;
	cout << "�������� �� ������� �����:" <<(stack->IsEmpty())<< endl;

	for (int i=0; i<5; i++)
		stack->Push(i);
	cout << "��������� ����� ����������:" << endl;
	stack->Print();

	cout << "�������� �������� � ��������, ��� ��������: "; 
	cout << stack->GetValue()<< endl;
	cout << "STACK:"<< endl; stack->Print();

	cout << "����� �������� � ��������: ";
	cout << stack->Pop() << endl;
	cout << "STACK:"<< endl; stack->Print();
	return 0;
}
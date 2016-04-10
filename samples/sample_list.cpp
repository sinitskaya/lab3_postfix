#include "list.h"

int main()
{
	setlocale(0,"");
	//List<int> *list = new List<int>;
	List<double> *list = new List<double>;
	list->Print();
	cout << "������� � ������ ������" << endl;
	list->PushStart(2.1);
	list->Print();
	cout << "������� � ����� ������" << endl;
	list->PushEnd(5);
	list->Print();

	cout << "������� � ������� ����� ����� 2.1" << endl;
	list->PushAfter(2.1,4);
	list->Print();
	cout << "������� � ������� ����� ������ 4" << endl;
	list->PushBefore(4,3);
	list->Print();

	cout << "�������� � ������ 5" << endl;
	list->Remove(5);
	list->Print();
	return 0;
}
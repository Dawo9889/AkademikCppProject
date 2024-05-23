#include "Interface.h"
#include <iomanip>

using namespace std;

void Interface::welcomePage()
{
	cout << "Witaj";
	Sleep(3000);
}
int Interface::pageWhenUCanLoginOrRegisterOrExit()
{
	int decision{};
	system("cls");

	cout << "														"<<endl;
	cout << "    -------------      -------------      -----------      " << endl;
	cout << "   |  Logowanie  |    | Rejestracja |    |  Wyjœcie  |      " << endl;
	cout << "   |             |    |             |    |           |      " << endl;
	cout << "   |      1      |    |      2      |    |     3     |      " << endl;
	cout << "   |             |    |             |    |           |      " << endl;
	cout << "    -------------      -------------      -----------      " << endl;

	cin >> decision;
	if (decision == 1 || decision == 2 || decision == 3)
	{
		system("cls");
		return decision;
	}
	else
	{
		cin.clear();
		cin.ignore();
		cout << " >>> Nieprawidlowa decyzja <<< " << endl;
		Sleep(1000);
		system("cls");
	}
}
int Interface::loginPage()
{

}
int Interface::registerPage()
{

}
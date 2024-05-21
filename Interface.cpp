#include "Interface.h"
#include <iomanip>

using namespace std;

void Interface::welcomePage()
{
	cout << "Witaj";
	Sleep(300);
}
void Interface::pageWhenUCanLoginOrRegisterOrExit()
{
	int deciscion{};
	system("cls");

	//while (true)
	{
		cout << "														"<<endl;
		cout << "    -------------      -------------      -----------      " << endl;
		cout << "   |  Logowanie  |    | Rejestracja |    |  Wyjœcie  |      " << endl;
		cout << "   |             |    |             |    |           |      " << endl;
		cout << "   |      1      |    |      2      |    |     3     |      " << endl;
		cout << "   |             |    |             |    |           |      " << endl;
		cout << "    -------------      -------------      -----------      " << endl;
	}
}
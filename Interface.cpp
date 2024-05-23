#include "Interface.h"
#include <iomanip>
#include <string>
#include <conio.h>

using namespace std;

string getPassword() {
	string password;
	char ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') {
			if (!password.empty()) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else {
			password.push_back(ch);
			cout << ' ';
		}
	}
	cout << endl;
	return password;
}

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

	cout << "Podaj opcjê od 1 do 3 co chcesz zrobic: ";
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
	string password;
	string login;

	while (true)
	{
		cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
		cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
		cout << "[Wpisz login: ";
		cin >> login;
		if (login == "0")
		{
			return 0;
		}
		cout << "[Wpisz haslo: ";
		cin >> password;
		/*if (t.loginCheck(login, pass) == true) //za pomoca metody loginCheck sprawdzamy czy wszystko jest git
		{
			Sleep(1000);
			break;
		}*/
		system("cls");
	}
	return 0;
}
int Interface::registerPage()
{
	string login, password,passwordConfirm, role;
	bool passwordChecker = true;
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
	cout << "[Podaj login: ";
	cin >> login;
	if (login == "0")
	{
		return 0;
	}
	while (passwordChecker) {
		cout << "[Podaj haslo: ";
		password = getPassword();
		cout << "[Powtorz haslo: ";
		passwordConfirm = getPassword();
		if (password == passwordConfirm) {
			// addrow
			break;
		}
		else {
			cout << "Hasla nie pasuja do siebie, podaj ponownie haslo" << endl;
		}
	}
}
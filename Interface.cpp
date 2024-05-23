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
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
	cout << "[Podaj login: ";
	cin >> login;
	if (login == "0")
	{
		return 0;
	}
	while (true) {
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
int Interface::addRoomToStudentHouse()
{
	int roomNumber, numberOfBeds;
	bool isAvailable = true;

	while (true)
	{
		cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu -1 + ENTER]" << endl;
		cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
		cout << "[Wpisz login: ";
		cin >> roomNumber;
		if (roomNumber == -1)
		{
			return 0;
		}
		cout << "[Podaj ilosc lozek: ";
		cin >> numberOfBeds;
		if (numberOfBeds < 0 and numberOfBeds > 3)
		{
			cout << "Liczba lozek jest nieprawidlowa!" << endl;
		}
		else
		{
			//addroom
			break;
		}
		system("cls");
	}

}
int Interface::addResident()
{
	string PESEL, firstName, lastName, email;
	int roomNumber;
	while (true)
	{
		cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
		cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
		cout << "[Wpisz PESEL: ";
		cin >> PESEL;
		if (PESEL == "0")
		{
			return 0;
		}
		if (PESEL.size() != 11)
		{
			cout << "PESEL nie jest ciagiem 11 cyfr" << endl;
		}
		cout << "[Podaj imie mieszkanca: ";
		cin >> firstName;
		cout << "Podaj nazwisko mieszkanca: ";
		cin >> lastName;
		cout << "Podaj adres email mieszkanca: ";
		cin >> email;
		cout << "Podaj pokoj do ktorego chcesz przydzielic mieszkanca: ";
		cin >> roomNumber;
		//if ()
		//{
		//	cout << "Podany pokoj nie istnieje!";
		//}
		//else
		//{
		//	//dodaj mieszkanca
		//	break;
		//}
		system("cls");
	}

}
string createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
"pesel VARCHAR(11) PRIMARY KEY,"
"first_name VARCHAR(30) NOT NULL,"
"last_name VARCHAR(30) NOT NULL,"
"email VARCHAR(40) NOT NULL,"
"room_number VARCHAR(4),"
"FOREIGN KEY (room_number) REFERENCES Room(room_number)"
");";
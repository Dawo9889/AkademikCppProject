#include "Interface.h"
#include <iomanip>
#include <string>
#include <conio.h>
#include "User.h"
#include "Room.h"
#include "Resident.h"
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

void Interface::welcomePage(User& user, Room& room, Resident& resident)
{
	/*cout << "Witaj";
	Sleep(3000);*/
	mainMenu(user, room, resident);
}
int Interface::mainMenu(User& user, Room& room, Resident& resident)
{
	int decision{};
	while (true)
	{
		while (true)
		{
			decision = pageWhenUCanLoginOrRegisterOrExit(); //ekran wyboru: 1 - logowanie, 2 - rejestracja, 3 - wyjscie
			if (decision == 1)
			{
				decision = loginPage(user, room, resident);
				if (decision == 4)
				{
					break;
				}
			}
			else if (decision == 2)
			{
				registerPage(user);
			}
			else
			{
				return 0;
			}
		}
	}
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
int Interface::loginPage(User& user, Room& room, Resident& resident)
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
		password = getPassword();
		if (user.validateCredentials(login, password)) {
			if (user.getUserRole(login) == "admin") {
				administrationPanel(user, room, resident);
			}
			else {
				cout << "User is not an admin";
				Sleep(3000);
			}
		}
		else {
			cout << "There is no such an user";
			Sleep(3000);
		}
		system("cls");
	}
	return 4;
}
int Interface::registerPage(User& user)
{
	string login, password, passwordConfirm, email;
	int decision{};
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;

	while (true) {
		cout << "[Podaj login: ";
		cin >> login;
		if (login == "0")
		{
			return 0; // Exit the registration
		}

		cout << "[Podaj email: ";
		cin >> email;
		if (email == "0")
		{
			return 0; // Exit the registration
		}

		while (true) {
			cout << "[Podaj haslo: ";
			password = getPassword();
			cout << "[Powtorz haslo: ";
			passwordConfirm = getPassword();

			if (password == passwordConfirm) {
				decision = user.addUser(login, email, password);
				if (decision == 0)
				{
					cout << "!!! User already exists !!! " << endl << endl;
					Sleep(2000);
					break;
				}
				else {
					Sleep(2000);
					return 1;
				}
			}
			else {
				cout << "Hasla nie pasuja do siebie, podaj ponownie haslo" << endl;
			}
		}
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
void Interface::logoutPage(User& user, Room& room, Resident& resident)
{
	system("cls");
	cout << ">>> Pomyslnie wylogowano z systemu <<<" << endl;
	Sleep(2000);
	loginPage(user, room, resident);
}

int Interface::goodbyePage()
{
	system("cls");
	cout << " -------------- " << endl;
	cout << "| Do widzenia! |" << endl;
	cout << " -------------- " << endl;
	Sleep(2000);
	return 0;
}
void Interface::managingResidentsPage()
{

}
int Interface::managingRoomsPage(User& user, Room& room, Resident& resident)
{
	int decision{};
	while (true)
	{
		system("cls");
		cout << " ----------------------------------------  " << endl;
		cout << "|          Zarzadzanie pokojami          | " << endl;
		cout << "|                                        | " << endl;
		cout << "|> 1 + ENTER: Dodawanie pokojow          | " << endl;
		cout << "|> 2 + ENTER: Usuwanie pokojow           | " << endl;
		cout << "|> 3 + ENTER  Wstecz                     | " << endl;
		cout << "|                                        | " << endl;
		cout << " ----------------------------------------  " << endl;
		cout << "Wybierz opcje: ";
		cin >> decision;

		if (decision == 1)
		{
			addRoomInterface(user, room, resident);
		}
		else if (decision == 2)
		{

		}
		else if (decision == 3)
		{
			administrationPanel(user, room, resident);
			return 1;
		}
		else
		{
			cin.clear();
			cin.ignore();
			system("cls");
			cout << ">>> Nieprawidlowa decyzja <<<" << endl;
			Sleep(1000);
		}
	}
}
int Interface::addRoomInterface(User& user, Room& room, Resident& resident)
{
	string roomNumber;
	int decision{}, numberOfBeds{};
	bool isAvailable = true;
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;
	cout << "[Podaj numer pokoju: ";
	cin >> roomNumber;
	if (roomNumber == "0")
	{
		return 0;
	}
	while (true) {
		cout << "[Podaj ilosc lozek w pokoju: ";
		cin >> numberOfBeds;
		if (numberOfBeds > 0 and numberOfBeds < 4) {
			decision = room.addRoom(roomNumber, numberOfBeds, isAvailable);
			if (decision == 0)
			{
				cout << "!!! Pokoj juz istnieje !!! " << endl << endl;
				Sleep(2000);
				break;
			}
			else
			{
				return 1;
			}
		}
		else {
			cout << "Ilosc w lozek w pokoju to 1,2 lub 3" << endl;
		}
	}
}
int Interface::administrationPanel(User& user, Room& room, Resident& resident)
{
	int decision{};
	while (true)
	{
		system("cls");
		cout << " ----------------------------------------  " << endl;
		cout << "|          Panel administracyjny         | " << endl;
		cout << "|                                        | " << endl;
		cout << "|> 1 + ENTER: Zarzadzanie mieszkancami   | " << endl;
		cout << "|> 2 + ENTER: Zarzadzanie pokojami       | " << endl;
		cout << "|> 3 + ENTER  Wylogowanie                | " << endl;
		cout << "|> 4 + ENTER  Zamknij aplikacje          | " << endl;
		cout << "|                                        | " << endl;
		cout << " ----------------------------------------  " << endl;
		cout << "Wybierz opcje: ";
		cin >> decision;

		if (decision == 1)
		{
			managingResidentsPage();
		}
		else if (decision == 2)
		{
			managingRoomsPage(user, room, resident);
		}
		else if (decision == 3)
		{
			logoutPage(user, room, resident);
			return 1;
		}
		else if (decision == 4)
		{
			goodbyePage();
			return 0;
		}
		else
		{
			cin.clear();
			cin.ignore();
			system("cls");
			cout << ">>> Nieprawidlowa decyzja <<<" << endl;
			Sleep(1000);
		}
	}
	return 0;
}
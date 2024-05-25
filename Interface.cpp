#include "Interface.h"
#include <iomanip>
#include <string>
#include <conio.h>
#include "User.h"
#include "Room.h"
#include "Resident.h"
using namespace std;
Interface::Interface(User& user, Room& room, Resident& resident) : user(user), room(room), resident(resident)
{
	this->user = user;
	this->room = room;
	this->resident = resident;
}
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
	/*cout << "Witaj";
	Sleep(3000);*/
	mainMenu();
}
int Interface::mainMenu()
{
	int decision{};
	while (true)
	{
		while (true)
		{
			decision = pageWhenUCanLoginOrRegisterOrExit(); //ekran wyboru: 1 - logowanie, 2 - rejestracja, 3 - wyjscie
			if (decision == 1)
			{
				decision = loginPage();
				if (decision == 4)
				{
					break;
				}
				else if (decision == 0)
				{
					return 0;
				}
				else if (decision == 1)
				{
					pageWhenUCanLoginOrRegisterOrExit();
				}
			}
			else if (decision == 2)
			{
				registerPage();
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

	cout << "														" << endl;
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
	int decision{};
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
				decision = administrationPanel();
				return decision;
				break;
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
int Interface::registerPage()
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
int Interface::addResident() {
	string PESEL, firstName, lastName, email;
	int roomNumber{};
	while (true) {
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
		string roomNumberStr = to_string(roomNumber);

		if (!resident.isResidentInDatabase(PESEL)) {
			if (!room.isRoomInDatabase(roomNumberStr)) {
				system("cls");
				cout << "Pokoj nie istnieje";
				Sleep(2000);
				break;
			}
			resident.addResident(PESEL, firstName, lastName, email, roomNumber);
			system("cls");
			cout << "Mieszkaniec dodany";
			Sleep(2000);
			break;
		}
		else {
			system("cls");
			cout << "Mieszkaniec taki juz znajduje sie w naszej bazie danych";
			Sleep(2000);
			break;
		}
	}
}
void Interface::logoutPage()
{
	system("cls");
	cout << ">>> Pomyslnie wylogowano z systemu <<<" << endl;
	Sleep(2000);
}

void Interface::goodbyePage()
{
	system("cls");
	cout << " -------------- " << endl;
	cout << "| Do widzenia! |" << endl;
	cout << " -------------- " << endl;
	Sleep(2000);
}
int Interface::managingResidentsPage()
{
	int decision{};
	while (true)
	{
		system("cls");
		cout << " ----------------------------------------  " << endl;
		cout << "|       Zarzadzanie mieszkancami         | " << endl;
		cout << "|                                        | " << endl;
		cout << "|> 1 + ENTER: Dodawanie mieszkanca       | " << endl;
		cout << "|> 2 + ENTER: Usuwanie mieszkanca        | " << endl;
		cout << "|> 3 + ENTER  Wstecz                     | " << endl;
		cout << "|                                        | " << endl;
		cout << " ----------------------------------------  " << endl;
		cout << "Wybierz opcje: ";
		cin >> decision;

		if (decision == 1)
		{
			addResident();
		}
		else if (decision == 2)
		{
		}
		else if (decision == 3)
		{
			administrationPanel();
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
int Interface::managingRoomsPage()
{
	int decision{};
	while (true)
	{
		system("cls");
		room.displayAllRooms();
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
			addRoomInterface();
		}
		else if (decision == 2)
		{
			deleteRoomInterface();
		}
		else if (decision == 3)
		{
			administrationPanel();
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
int Interface::addRoomInterface()
{
	system("cls");
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
int Interface::deleteRoomInterface()
{
	system("cls");
	string roomNumber;
	int decision{};
	room.displayAllRooms();
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Podaj numer pokoju ktory chcesz usunac: ";
	cin >> roomNumber;
	if (roomNumber == "0")
	{
		return 0;
	}
	decision = room.deleteRoom(roomNumber);
	if (decision == 0)
	{
		cout << "Pomyslnie usunieto pokoj: " << roomNumber;
		Sleep(1000);
		return 0;
	}
	else
	{
		cout << "BLAD: ";
		Sleep(1000);
		return 0;
	}
}
int Interface::administrationPanel()
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
			managingRoomsPage();
		}
		else if (decision == 3)
		{
			logoutPage();
			return 1;
			break;
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
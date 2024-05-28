#include <iomanip>
#include <string>
#include <conio.h>

#include "Interface.h"
#include "User.h"
#include "Room.h"
#include "Resident.h"

using namespace std;
Interface::Interface(User& user, Room& room, Resident& resident) : user(user), room(room), resident(resident) //konstruktor parametryczny klasy Interface
{
	this->user = user;
	this->room = room;
	this->resident = resident;
}
string getPassword() { //funkcja ktora zamienia wprowadzane litery w hasle na znak spacji
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
bool validatePassword(const string& password) {
	// walidacja dlugosci hasla (min 5 znakow)
	if (password.length() < 5) {
		std::cout << "Haslo musi miec co najmniej 5 znakow." << std::endl;
		return false;
	}

	// sprawdzanie czy haslo ma znak specjalny
	bool hasSpecialChar = false;
	for (char ch : password) {
		if (!std::isalnum(ch)) {
			hasSpecialChar = true;
			break;
		}
	}

	if (!hasSpecialChar) {
		std::cout << "Haslo musi zawierac co najmniej jeden znak specjalny." << std::endl;
		return false;
	}

	return true;
}
bool isValidEmail(const string& email) 
//walidacja adresu email
{  
	if (email.find('@') == string::npos || email.find('.') == string::npos) {
		cout << "Podaj poprawny adres email. Poprawny adres email zawiera '@' i domene, np '.com' " << std::endl;
		return false;
	}
	return true;
}
bool isNumber(const string& str) {
	if (str.empty()) return false;
	for (char c : str) {
		if (!isdigit(c)) return false;
	}
	return true;
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
				if (decision == 0)
				{
					return 0;
				}
				else
				{
					break;
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
	
	while (true)
	{
	system("cls");
	cout << "	         	   AKADEMIK                		" << endl;
	cout << "														" << endl;
	cout << "    -------------      -------------      -----------      " << endl;
	cout << "   |  Logowanie  |    | Rejestracja |    |  Wyjscie  |      " << endl;
	cout << "   |             |    |             |    |           |      " << endl;
	cout << "   |      1      |    |      2      |    |     3     |      " << endl;
	cout << "   |             |    |             |    |           |      " << endl;
	cout << "    -------------      -------------      -----------      " << endl;

	cout << "Podaj opcje od 1 do 3 co chcesz zrobic: ";
	cin >> decision;
	if (decision == 1 || decision == 2 || decision == 3)
	{
		system("cls");
		return decision;
		break;
	}
	else
	{
		system("cls");
		cout << " >>> Nieprawidlowa decyzja <<< " << endl;
		Sleep(1000);
	}
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
			return -1;
		}
		cout << "[Wpisz haslo: ";
		password = getPassword(); //pobranie hasla z funkcji ktora ukrywa haslo w konsoli
		if (user.validateCredentials(login, password)) { //sprawdzanie loginu i has³a
			if (user.getUserRole(login) == "admin") { //przejscie do panelu administratora jesli uzytkownik jest adminem
				return administrationPanel();
				break;
			}
			else {
				cout << "Uzytkownik nie jest administratorem"; //a tutaj jest uruchamiany widok uzytkownika
				Sleep(1000);
				decision = userPanel(login);
				if (decision == 0)
					return 0;
				break;
			}
		}
		else {
			cout << "Uzytkownik nie istnieje";
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
			return 0; // Zakoncz rejestracje
		}
		if (login.length() < 5) { // Sprawdzanie dlugosci loginu
			cout << "Login musi miec przynajmniej 5 znakow." << endl;
			continue;
		}

		while (true) {
			std::cout << "[Podaj email: ";
			std::cin >> email;
			if (email == "0") {
				return 0; //Zakoncz rejestracje
			}
			if (isValidEmail(email)) {
				break; // Przerwanie petli jesli email jest poprawny
			}
		}
		while (true) {
			std::cout << "[Podaj haslo: ";
			password = getPassword();
			if (!validatePassword(password)) {
				cout << "Haslo musi miec przynajmniej 5 znakow i znak specjalny!" << endl;
				Sleep(2000);
				continue; // Powtórz pêtlê
			}
			std::cout << "[Powtorz haslo: ";
			passwordConfirm = getPassword();



			if (password == passwordConfirm) {
				decision = user.addUser(login, email, password);
				if (decision == 0) {
					std::cout << "!!! Uzytkownik juz istnieje !!! " << std::endl << std::endl;
					Sleep(2000);
					break;
				}
				else {
					Sleep(2000);
					return 1;
				}
			}
			else {
				std::cout << "Hasla nie pasuja do siebie, podaj ponownie haslo" << std::endl;
			}
		}
	}
}
int Interface::administrationPanel()
{
	int decision{}, returnedDecision{};
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
			returnedDecision = managingResidentsPage();
			return returnedDecision;
		}
		else if (decision == 2)
		{
			returnedDecision = managingRoomsPage();
			return returnedDecision;
		}
		else if (decision == 3)
		{
			logoutPage();
			return 1;
		}
		else if (decision == 4)
		{
			goodbyePage();
			return 0;
			break;
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
int Interface::userPanel(string& login)
{
	string email = user.getEmailByLogin(login);
	resident.isResidentInDatabase(email, 1);

	int decision{};
	while (true)
	{
		if (!(resident.isResidentInDatabase(email, 1))) { // sprawdznie czy uzytkownik istnieje w tabeli mieszkancow
			system("cls");
			cout << "W systemie twoj email: '" + email + "' nie nalezy do zadnego pokoju. Skontaktuj sie z administratorem." << endl;
			cout << endl;
		}
		else {
			system("cls");
			cout << "Ponizej znajduja sie wszystkie dane o Twoim pokoju:" << endl;
			string roomNumberStr = resident.returnRoomNumber(email, 1);
			room.displayRoomDetails(roomNumberStr);
		}

		cout << " ----------------------------------------  " << endl;
		cout << "|          Panel uzytkownika             | " << endl;
		cout << "|                                        | " << endl;
		cout << "|> 1 + ENTER  Wylogowanie                | " << endl;
		cout << "|> 2 + ENTER  Zamknij aplikacje          | " << endl;
		cout << "|                                        | " << endl;
		cout << " ----------------------------------------  " << endl;
		cout << "Wybierz opcje: ";
		cin >> decision;
		if (decision == 1) {
			logoutPage();
			return 1;
		}
		else if (decision == 2)
		{
			goodbyePage();
			return 0;
			break;
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
int Interface::managingResidentsPage()
{
	int decision{},returnedDecision{};
	while (true)
	{
		system("cls");
		cout << " ----------------------------------------------  " << endl;
		cout << "|       Zarzadzanie mieszkancami               | " << endl;
		cout << "|                                              | " << endl;
		cout << "|> 1 + ENTER: Dodawanie mieszkanca             | " << endl;
		cout << "|> 2 + ENTER: Usuwanie mieszkanca              | " << endl;
		cout << "|> 3 + ENTER: Zmiana pokoju mieszkanca         | " << endl;
		cout << "|> 4 + ENTER  Wyswietl wszystkich mieszkancow  | " << endl;
		cout << "|> 5 + ENTER  Wstecz                           | " << endl;
		cout << "|                                              | " << endl;
		cout << " ----------------------------------------------  " << endl;
		cout << "Wybierz opcje: ";
		cin >> decision;

		if (decision == 1)
		{
			addResident();
		}
		else if (decision == 2)
		{
			deleteResidentInterface();
		}
		else if (decision == 3)
		{
			updateRoomOfResident();
		}
		else if (decision == 4)
		{
			displayResidents();
		}
		else if (decision == 5)
		{
			returnedDecision = administrationPanel();
			return returnedDecision;
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
int Interface::managingRoomsPage()
{
	int decision{}, returnedDecision{};
	while (true)
	{
		system("cls");
		cout << " ----------------------------------------  " << endl;
		cout << "|          Zarzadzanie pokojami          | " << endl;
		cout << "|                                        | " << endl;
		cout << "|> 1 + ENTER: Dodawanie pokojow          | " << endl;
		cout << "|> 2 + ENTER: Usuwanie pokojow           | " << endl;
		cout << "|> 3 + ENTER: Wyswietl wszystkie pokoje  | " << endl;
		cout << "|> 4 + ENTER: Wstecz                     | " << endl;
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
			displayRooms();
		}
		else if (decision == 4)
		{
			returnedDecision = administrationPanel();
			return returnedDecision;
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
int Interface::addResident() {
	system("cls");
	string PESEL, firstName, lastName, email, roomNumberStr;
	int roomNumber{};
	char decision{};
	while (true) {
		cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
		cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;

		while (true) 
			// walidacja PESEL
		{
			cout << "[Podaj numer PESEL mieszkanca ktorego chcesz dodac: ";
			cin >> PESEL;
			if (PESEL == "0") {
				return 0;
			}
			if (PESEL.size() == 11 && all_of(PESEL.begin(), PESEL.end(), ::isdigit)) {
				break;
			}
			else {
				cout << "PESEL nie jest ciagiem 11 cyfr. Sprobuj ponownie." << endl;
				continue;
			}
		}

		cout << "Podaj imie mieszkanca: ";
		cin >> firstName;
		cout << "Podaj nazwisko mieszkanca: ";
		cin >> lastName;
		while (true) {
			std::cout << "Podaj adres email mieszkanca: ";
			std::cin >> email;
			if (email == "0") {
				return 0; // przerwanie rejestracji
			}
			if (isValidEmail(email)) {
				break; // wyjscie z petli w wyniku poprawnego adresu email
			}
		}

		while (true) {
			cout << "Podaj pokoj do ktorego chcesz przydzielic mieszkanca: ";
			cin >> roomNumberStr;
			if (!isNumber(roomNumberStr)) {
				cout << "Numer pokoju musi byc liczba. Sprobuj ponownie." << endl;
				continue;
			}
			else
			{
				roomNumber = stoi(roomNumberStr);
				break;
			}


		}

		if (!resident.isResidentInDatabase(PESEL, 0)) { // 0 - jest to argument typu bool, w tej funckji przyjmuje falsz poniewaz szukamy na podstawie PESELu
			if (!room.isRoomInDatabase(roomNumberStr)) {
				system("cls");
				cout << "Pokoj nie istnieje" << endl;
				cout << "Czy chcesz dodac pokoj teraz [t/n]? ";
				cin >> decision;
				if (decision == 'n' || decision == 'N')
				{
					break;
				}
				else
				{
					addRoomInterface();
				}
				Sleep(2000);
			}
			if (!room.isRoomAvailable(roomNumberStr)) {
				system("cls");
				cout << "Pokoj nie ma juz miejsc";
				Sleep(2000);
				break;
			}

			resident.addResident(PESEL, firstName, lastName, email, roomNumber);
			//po dodaniu mieszkanca aktualizujemy dostepnosc pokoju wzgledem ilosci lozek
			room.updateRoomAvailability(roomNumberStr);
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
	return 1;
}
int Interface::deleteResidentInterface()
{
	system("cls");
	string PESEL;
	string roomNumber;
	int decision{};
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	while (true)
		// walidacja PESEL
	{
		cout << "[Podaj numer PESEL mieszkanca ktorego chcesz usunac: ";
		cin >> PESEL;
		if (PESEL == "0") {
			return 0;
		}
		if (PESEL.size() == 11 && all_of(PESEL.begin(), PESEL.end(), ::isdigit)) {
			break;
		}
		else {
			cout << "PESEL nie jest ciagiem 11 cyfr. Sprobuj ponownie." << endl;
			continue;
		}
	}

	if (resident.isResidentInDatabase(PESEL, 0))
	{
		roomNumber = resident.returnRoomNumber(PESEL, 0);
		decision = resident.deleteResident(PESEL);
		if (decision == 0)
		{
			cout << "Pomyslnie usunieto mieszkanca: " << PESEL;
			room.updateRoomAvailability(roomNumber);
			Sleep(1000);
			return 0;
		}
	}
	else
	{
		cout << "Mieszkaniec o podanym numerze PESEL nie istnieje!";
		Sleep(1000);
	}
}
int Interface::updateRoomOfResident()
{
	system("cls");
	string PESEL, newRoomNumber, oldRoomNumber;
	int decision{};
	char decisionChar{};
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	while (true)
		// walidacja PESEL
	{
		cout << "[Podaj numer PESEL mieszkanca ktoremu chcesz zmienic pokoj: ";
		cin >> PESEL;
		if (PESEL == "0") {
			return 0;
		}
		if (PESEL.size() == 11 && all_of(PESEL.begin(), PESEL.end(), ::isdigit)) {
			break;
		}
		else {
			cout << "PESEL nie jest ciagiem 11 cyfr. Sprobuj ponownie." << endl;
			continue;
		}
	}
	while (true) {
		if (resident.isResidentInDatabase(PESEL, 0)) //sprawdzanie czy mieszkaniec jest w bazie
		{
			oldRoomNumber = resident.returnRoomNumber(PESEL, 0); //pobranie numeru pokoju w ktorym obecnie znajduje sie mieszkaniec
			
			while (true)
			{
				cout << "[Podaj numer pokoju na ktory chcesz zmienic: ";
				cin >> newRoomNumber;
				if (!isNumber(newRoomNumber)) {
					cout << "Numer pokoju musi byc liczba. Sprobuj ponownie." << endl;
					continue;
				}
				else if (newRoomNumber == "0")
				{
					break;
					return 0; // przerwanie usuwania pokoju
				}
				else
				{
					break;
				}
			}
			if (newRoomNumber == "0") //jesli podany pokoj wynosi 0 to rowniez zmiana pokoju jest przerywana
			{
				break;
			}

			if (newRoomNumber == oldRoomNumber)
			{
				cout << "Mieszkaniec znajduje sie obecnie w tym pokoju!";
				Sleep(2000);
				break;
			}
			if (!room.isRoomInDatabase(newRoomNumber)) { //sprawdzenie czy pokoj istnieje w bazie
				system("cls");
				cout << "Pokoj nie istnieje" << endl;
				cout << "Czy chcesz dodac pokoj teraz [t/n]? ";
				cin >> decisionChar;
				if (decisionChar == 'n' || decisionChar == 'N')
				{
					return 0;
					break;
				}
				else
				{
					addRoomInterface(); //kreator nowego pokoju
				}
				Sleep(2000);
			}
			if (!room.isRoomAvailable(newRoomNumber)) //sprawdzenie czy w nowym pokoju jest miejsce
			{
				cout << "Pokoj juz jest pelny!";
				Sleep(2000);
				break;
			}
			decision = resident.changeRoomOfResitent(PESEL, newRoomNumber); //zmiana pokoju
			if (decision == 0)
			{
				cout << "Pomyslnie zmieniono pokoj mieszkanca: " << PESEL;
				room.updateRoomAvailability(oldRoomNumber);
				room.updateRoomAvailability(newRoomNumber); //aktualizacja miejsca w starym i nowym pokoju
				Sleep(1000);
				return 0;
			}
		}
		else
		{
			cout << "Mieszkaniec o podanym numerze PESEL nie istnieje!";
			Sleep(1000);
			break;
		}
	}
}
void Interface::displayResidents()
{
	char sign;
	do
	{
		system("cls");
		resident.displayAllResidents();
		cout << "[Jezeli chcesz wyjsc wpisz 0 + ENTER]" << endl;
		cout << "Wprowadz opcje: ";
		cin >> sign;
	} while (sign != '0');
}
int Interface::addRoomInterface() {
	system("cls");
	string roomNumber, numberOfBedsStr;
	int decision{}, numberOfBeds{};
	bool isAvailable = true;

	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	cout << "[Zatwierdzaj dane kilkajac ENTER]" << endl << endl;

	while (true) {
		cout << "[Podaj numer pokoju: ";
		cin >> roomNumber;
		if (roomNumber == "0") {
			return 0; // przerwanie dodawania pokoju
		}
		if (!isNumber(roomNumber)) {
			cout << "Numer pokoju musi byc liczba. Sprobuj ponownie." << endl;
			continue;
		}

		while (true) {
			cout << "[Podaj ilosc lozek w pokoju: ";
			cin >> numberOfBedsStr;
			if (!isNumber(numberOfBedsStr)) {
				cout << "Ilosc lozek musi byc liczba. Sprobuj ponownie." << endl; //walidacja czy wprowadzone dane sa liczbami
				continue;
			}
			numberOfBeds = stoi(numberOfBedsStr);
			if (numberOfBeds > 0 && numberOfBeds < 4) {
				decision = room.addRoom(roomNumber, numberOfBeds, isAvailable);
				if (decision == 0) {
					cout << "!!! Pokoj juz istnieje !!! " << endl << endl;
					Sleep(2000);
					break; // przerwanie petli poniewaz pokoj juz istnieje
				}
				else {
					cout << "Pokoj zostal dodany pomyslnie." << endl << endl;
					Sleep(2000);
					return 1;
				}
			}
			else {
				cout << "Ilosc lozek w pokoju to 1, 2 lub 3" << endl;
			}
		}
		if (decision == 0) {
			break;
		}
	}
	return 0;
}
int Interface::deleteRoomInterface()
{
	system("cls");
	string roomNumber;
	int decision{};
	cout << "[Jezeli chcesz przerwac wpisz w pierwszym wierszu 0 + ENTER]" << endl;
	while (true) 
	{
		cout << "[Podaj numer pokoju ktory chcesz usunac: ";
		cin >> roomNumber;
		if (!isNumber(roomNumber)) {
			cout << "Numer pokoju musi byc liczba. Sprobuj ponownie." << endl;
			continue;
		}
		else if (roomNumber == "0")
		{
			break;
			return 0; // przerwanie usuwania pokoju
		}
		else
		{
			break;
		}
	}
	if (resident.isAnyResidentInRoom(roomNumber) && roomNumber != "0")
	{
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
	else if (roomNumber == "0")
	{
	}
	else
	{
		cout << "Pokoj jest zajety!";
		Sleep(1000);
	}
}
void Interface::displayRooms()
{
	char sign;
	do
	{
		system("cls");
		room.displayAllRooms();
		cout << "[Jezeli chcesz wyjsc wpisz 0 + ENTER]" << endl;
		cout << "Wprowadz opcje: ";
		cin >> sign;
	} while (sign != '0');
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

#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <string>
#include "System.h"

using namespace std;

System::System()
{
	currentUser = nullptr;
}

System::~System()
{
}

void System::Initialise()
{
	struct tm datetime;

	time_t timestamp;
	time(&timestamp);

	datetime = *localtime(&timestamp);

	string currentDate = to_string(datetime.tm_mday) + "/" + to_string(datetime.tm_mon + 1) + "/" + to_string(datetime.tm_year - 100);

	cout << "Current Date: " << currentDate << endl;

	//below here can honestly end up as the function for setting due dates, until tomorrow when V tells me no. Also should definitally set 7 as a variable in a rule instead so the amount of time you have the book for can be changed in rules by the admin

	switch (datetime.tm_mon + 1)
	{
	case 1:
		cout << "It's January, so if due date pushes tm_mday over 31, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 31)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 31;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 2:
		cout << "It's February, so if due date pushes tm_mday over 28, will reset and push this up. Unless it's a leap year, which would mean the year can be divided by 4." << endl;
		if (floor(datetime.tm_year / 4) == datetime.tm_year / 4)
		{
			cout << "It's a leap year, so if due date pushes tm_mday over 29, will reset and push this up." << endl;
			if (datetime.tm_mday + 7 > 29)
			{
				datetime.tm_mday = (datetime.tm_mday + 7) - 29;
				datetime.tm_mon += 1;
			}
			else
			{
				datetime.tm_mday += 7;
			}
		}
		else
		{
			cout << "It's not a leap year, so if due date pushes tm_mday over 28, will reset and push this up." << endl;
			if (datetime.tm_mday + 7 > 28)
			{
				datetime.tm_mday = (datetime.tm_mday + 7) - 28;
				datetime.tm_mon += 1;
			}
			else
			{
				datetime.tm_mday += 7;
			}
		}
		break;
	case 3:
		cout << "It's March, so if due date pushes tm_mday over 31, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 31)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 31;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 4:
		cout << "It's April, so if due date pushes tm_mday over 30, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 30)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 30;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 5:
		cout << "It's May, so if due date pushes tm_mday over 31, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 31)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 31;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 6:
		cout << "It's June, so if due date pushes tm_mday over 30, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 30)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 30;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 7:
		cout << "It's July, so if due date pushes tm_mday over 31, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 31)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 31;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 8:
		cout << "It's August, so if due date pushes tm_mday over 31, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 31)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 31;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 9:
		cout << "It's September, so if due date pushes tm_mday over 30, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 30)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 30;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 10:
		cout << "It's October, so if due date pushes tm_mday over 31, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 31)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 31;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 11:
		cout << "It's November, so if due date pushes tm_mday over 30, will reset and push this up." << endl;
		if (datetime.tm_mday + 7 > 30)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 30;
			datetime.tm_mon += 1;
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	case 12:
		cout << "It's December, so if due date pushes tm_mday over 31, will reset and push this back to 1, while pushing up tm_year." << endl;
		if (datetime.tm_mday + 7 > 31)
		{
			datetime.tm_mday = (datetime.tm_mday + 7) - 31;
			datetime.tm_mon += 1;

			if (datetime.tm_mon > 12)
			{
				datetime.tm_mon = 1;
				datetime.tm_year += 1;
			}
		}
		else
		{
			datetime.tm_mday += 7;
		}
		break;
	}

	string dueDate = to_string(datetime.tm_mday) + "/" + to_string(datetime.tm_mon + 1) + "/" + to_string(datetime.tm_year - 100);

	cout << "Due Date: " << dueDate << endl;

	nonPrivateInformation.push_back(new Member("Steve", "Password1", 1234));
	nonPrivateInformation.push_back(new Member("John", "Password2", 5678));
	nonPrivateInformation.push_back(new Librarian("Lucy", "Password3", 9012));

	listOfBooks.push_back(new Book("The Great Gatsby", "F. Scott Fitzgerald"));
	listOfBooks.push_back(new Book("To Kill a Mockingbird", "Harper Lee"));
	listOfBooks.push_back(new Book("1984", "George Orwell"));
	listOfBooks.push_back(new Book("Pride and Prejudice", "Jane Austen"));
	listOfBooks.push_back(new Book("The Catcher in the Rye", "J.D. Salinger"));
	listOfBooks.push_back(new Book("The Lord of the Rings", "J.R.R. Tolkien"));
	listOfBooks.push_back(new Book("The Hobbit", "J.R.R. Tolkien"));
	listOfBooks.push_back(new Book("The King In Yellow", "Robert W. Chambers"));
}

void System::Register()
{
	cout << "~~~~~~~~~~~~~~~ REGISTER ~~~~~~~~~~~~~~~" << endl;

	string usernameInp = "";
	string passwordInp = "";
	int createdID = 0;

	do
	{
		cout << "Please enter your username: ";
		cin >> usernameInp;

		for (User* user : nonPrivateInformation)
		{
			if (user->GetUsername() == usernameInp)
			{
				cout << "An account with this username already exists. Please choose a new username." << endl << endl;
				usernameInp = "";
			}
		}
	} 
	while (usernameInp == "");

	cout << endl << "Please enter your password: ";
	cin >> passwordInp;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(0, 9999);

	createdID = distrib(gen);

	cout << endl << "Please confirm the following information:" << endl; 
	cout << "Your username will be: " << usernameInp << endl;
	cout << "Your password will be: " << passwordInp << endl;

	char confirmationInp = ' ';

	while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
	{
		cout << endl << "Is this information correct? (Y/N): ";
		cin >> confirmationInp;
	}

	if (confirmationInp == 'N' || confirmationInp == 'n')
	{
		cout << endl << "Registration cancelled. Please start again." << endl;
		Register();
		return;
	}

	cout << endl << "Your account has been created. Your ID is: " << createdID << endl;

	Member* newUser = new Member(usernameInp, passwordInp, createdID);
	nonPrivateInformation.push_back(newUser);

	currentUser = newUser;
	delete newUser;
	newUser = nullptr;
}

void System::Login()
{
	cout << "~~~~~~~~~~~~~~~ LOG IN ~~~~~~~~~~~~~~~" << endl;

	string usernameInp = "";
	string passwordInp = "";
	bool loggedIn = false;
	int passTries = 0;

	cout << "Please enter your username: ";
	cin >> usernameInp;

	for (User* user : nonPrivateInformation)
	{
		if (user->GetUsername() == usernameInp)
		{
			currentUser = user;
		}
	}

	if (currentUser == NULL)
	{
		cout << "Account not found. Please try again.";
		return;
	}

	while (!loggedIn && passTries < 3)
	{
		cout << "Please enter your password: ";
		cin >> passwordInp;

		if (currentUser->GetPassword() == passwordInp)
		{
			loggedIn = true;
		}
		else 
		{
			passTries++;
			cout << "Incorrect password entered." << endl;
		}

		if (passTries == 3)
		{
			cout << "Too many incorrect password attempts. Please try again later.";
			delete currentUser;
			currentUser = nullptr;
			return;
		}
	}

	cout << "Login Validated.";
}

void System::SendDueAlert()
{
	Member* temp = dynamic_cast<Member*>(currentUser);

	if (temp == nullptr)
	{
		return;
	}

	if (temp->GetNumberOfBorrowedBooks() != 0)
	{
		for (Book* book : listOfBooks)
		{

		}
	}
}

void System::SendOverdueAlert()
{
}

void System::SendReserveAlert()
{
}

list<Book*> System::GetListOfBooks()
{
	return listOfBooks;
}
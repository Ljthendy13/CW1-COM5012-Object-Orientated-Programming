#include <iostream>
#include <random>
#include "System.h"

using namespace std;

System::System()
{
}

System::~System()
{
}

void System::Initialise()
{
	Member* defaultUser1 = new Member("Steve", "Password1", 1234);
	Member* defaultUser2 = new Member("John", "Password2", 5678);

	nonPrivateInformation.push_back(defaultUser1);
	nonPrivateInformation.push_back(defaultUser2);

	Book* defaultBook1 = new Book("The Great Gatsby", "F. Scott Fitzgerald");
	Book* defaultBook2 = new Book("To Kill a Mockingbird", "Harper Lee");
	Book* defaultBook3 = new Book("1984", "George Orwell");
	Book* defaultBook4 = new Book("Pride and Prejudice", "Jane Austen");
	Book* defaultBook5 = new Book("The Catcher in the Rye", "J.D. Salinger");
	Book* defaultBook6 = new Book("The Lord of the Rings", "J.R.R. Tolkien");
	Book* defaultBook7 = new Book("The Hobbit", "J.R.R. Tolkien");
	Book* defaultBook8 = new Book("The King In Yellow", "Robert W. Chambers");

	listOfBooks.push_back(defaultBook1);
	listOfBooks.push_back(defaultBook2);
	listOfBooks.push_back(defaultBook3);
	listOfBooks.push_back(defaultBook4);
	listOfBooks.push_back(defaultBook5);
	listOfBooks.push_back(defaultBook6);
	listOfBooks.push_back(defaultBook7);
	listOfBooks.push_back(defaultBook8);
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
}

void System::Login()
{
	cout << "~~~~~~~~~~~~~~~ LOG IN ~~~~~~~~~~~~~~~" << endl;

	string usernameInp = "";
	string passwordInp = "";
	User* thisUser = NULL;
	bool loggedIn = false;


	cout << "Please enter your username: ";
	cin >> usernameInp;

	for (User* user : nonPrivateInformation)
	{
		if (user->GetUsername() == usernameInp)
		{
			thisUser = user;
		}
	}

	if (thisUser == NULL)
	{
		cout << "Account not found. Please try again.";
		return;
	}

	while (!loggedIn)
	{
		cout << "Please enter your password: ";
		cin >> passwordInp;

		if (thisUser->GetPassword() == passwordInp)
		{
			loggedIn = true;
		}
		else 
		{
			cout << "Incorrect password entered." << endl;
		}
	}

	cout << "Login Validated.";
}

void System::HidePrivateData()
{
}

void System::SendDueAlert()
{
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
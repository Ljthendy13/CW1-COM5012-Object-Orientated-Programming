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

	for (User* user : nonPrivateInformation)
	{
		if (user->GetUsername() == "Steve")
		{
			//borrowBook
		}
	}
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
			if (book->GetDueDate() > 0);
			{
				cout << book->GetTitle() << " is due in " << book->GetDueDate() << " hours." << endl << endl;
			}
		}

		char confirmationInp = ' ';

		do
		{
			cout << "Please confirm your acknowledgement (Y): ";
			cin >> confirmationInp;
		} 
		while (confirmationInp != 'Y' && confirmationInp != 'y');
	}

	return;
}

void System::SendOverdueAlert()
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
			if (book->GetDueDate() <= 0);
			{
				cout << book->GetTitle() << " is overdue. You will not be able to borrow another book until it is returned." << endl << endl;
			}
		}

		char confirmationInp = ' ';

		do
		{
			cout << "Please confirm your acknowledgement (Y): ";
			cin >> confirmationInp;
		} while (confirmationInp != 'Y' && confirmationInp != 'y');
	}

	return;
}

void System::SendReserveAlert()
{
	Member* temp = dynamic_cast<Member*>(currentUser);

	if (temp == nullptr)
	{
		return;
	}

	for (Request* request : listOfRequests)
	{
		if (request->GetRequestee() == temp->GetUsername())
		{
			for (Book* book : listOfBooks)
			{
				if (request->GetRelatedBook() == book->GetTitle())
				{
					if (book->GetAvailability() == true)
					{
						cout << "Your Reserved Book: " << book->GetTitle() << " was returned, and is now borrowed by you. It will be due for return on " << book->GetDueDate();
					}
				}
			}
		}
	}
}

list<Book*> System::GetListOfBooks()
{
	return listOfBooks;
}
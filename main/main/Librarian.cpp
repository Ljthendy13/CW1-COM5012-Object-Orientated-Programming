#include <iostream>
#include "Librarian.h"
#include "System.h"

using namespace std;

Librarian::Librarian(string username, string password, int id) : User(username, password, id, typeOfUser)
{
}

Librarian::~Librarian()
{
}

void Librarian::AddBook(System mainSystem)
{
	cout << "~~~~~~~~~~~~~~~ ADD NEW BOOK ~~~~~~~~~~~~~~~" << endl;

	string titleInp = "";
	string authorInp = "";

	do
	{
		cout << "Please enter the title of the book you would like to add: ";
		cin >> titleInp;

		for (Book* book : mainSystem.GetListOfBooks())
		{
			if (book->GetTitle() == titleInp)
			{
				cout << "An account with this username already exists. Please choose a new username." << endl << endl;
				titleInp = "";
			}
		}
	} while (titleInp == "");

	cout << endl << "Please enter the author of the book you would like to add: ";
	cin >> authorInp;

	cout << endl << "Please confirm the following information:" << endl;
	cout << "This Book's Title is: " << titleInp << endl;
	cout << "This Book's Author is: " << authorInp << endl;

	char confirmationInp = ' ';

	while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
	{
		cout << endl << "Is this information correct? (Y/N): ";
		cin >> confirmationInp;
	}

	if (confirmationInp == 'N' || confirmationInp == 'n')
	{
		cout << endl << "Creation cancelled." << endl;
		return;
	}

	Book* newBook = new Book(titleInp, authorInp);
	mainSystem.GetListOfBooks().push_back(newBook);
}

void Librarian::RemoveBook()
{
}

void Librarian::UpdateBook()
{
}

void Librarian::GenerateDataReport()
{
}

void Librarian::PrintDataReport()
{
}

void Librarian::HandleRequest()
{
}
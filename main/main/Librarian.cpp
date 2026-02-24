#include <iostream>
#include "Librarian.h"

using namespace std;

Librarian::Librarian(string username, string password, int id) : User(username, password, id)
{
}

Librarian::~Librarian()
{
}

void Librarian::AddBook()
{
	cout << "~~~~~~~~~~~~~~~ ADD NEW BOOK ~~~~~~~~~~~~~~~" << endl;

	string titleInp = "";
	string authorInp = "";

	System* tempSystem = new System;

	do
	{
		cout << "Please enter the title of the book you would like to add: ";
		cin >> titleInp;

		for (Book* book : tempSystem->GetListOfBooks())
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
		cout << endl << "Creation cancelled. Please start again." << endl;
		return;
	}

	Book* newBook = new Book(titleInp, authorInp); //Will need to change this whole part below here to create the book in the main system, and then add it to the list of books in the system, instead of creating a new system here and adding it to that one, which will just be deleted immediately after this function ends, meaning the book will be lost.
	tempSystem->GetListOfBooks().push_back(newBook);
	delete tempSystem;
	tempSystem = nullptr;
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
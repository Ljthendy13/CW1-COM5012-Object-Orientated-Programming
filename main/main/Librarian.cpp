#include <iostream>
#include <string>
#include <limits>
#include "Librarian.h"
#include "System.h"

using namespace std;

Librarian::Librarian(string username, string password, int id) : User(username, password, id, 1)
{
}

Librarian::~Librarian()
{
}

void Librarian::AddBook(System& mainSystem)
{
	cout << "~~~~~~~~~~~~~~~ ADD NEW BOOK ~~~~~~~~~~~~~~~" << endl;

	string titleInp = "";
	string authorInp = "";

	do
	{
		cout << "Please enter the title of the book you would like to add: ";
		getline(cin, titleInp);

		for (Book* book : mainSystem.GetListOfBooks())
		{
			if (book->GetTitle() == titleInp)
			{
				cout << "An book with this title already exists. Please add a different title." << endl << endl;
				titleInp = "";
			}
		}
	} 
	while (titleInp == "");

	cout << endl << "Please enter the author of the book you would like to add: ";
	getline(cin, authorInp);

	cout << endl << "Please confirm the following information:" << endl;
	cout << "This Book's Title is: " << titleInp << endl;
	cout << "This Book's Author is: " << authorInp << endl;

	char confirmationInp = ' ';

	while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
	{
		cout << endl << "Is this information correct? (Y/N): ";
		cin >> confirmationInp;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	if (confirmationInp == 'N' || confirmationInp == 'n')
	{
		cout << endl << "Creation cancelled." << endl;
		return;
	}
	
	mainSystem.GetListOfBooks().push_back(new Book(titleInp, authorInp));
}

void Librarian::RemoveBook(Book* selectedBook, System& mainSystem)
{
	mainSystem.GetListOfBooks().remove(selectedBook);
}

void Librarian::UpdateBook(Book* selectedBook, System& mainSystem)
{
	int choiceInput;
	string titleInput, authorInput;

	cout << "Would you like to change the title or author of this book? (1/2): ";
	cin >> choiceInput;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (choiceInput == 1)
	{
		cout << "What would you like to change the title to? ";
		getline(cin, titleInput);
		for (Book* book : mainSystem.GetListOfBooks())
		{
			if (book->GetTitle() == selectedBook->GetTitle())
			{
				book->SetTitle(titleInput);
			}
		}
	}
	else if (choiceInput == 2)
	{
		cout << "What would you like to change the author to? ";
		getline(cin, authorInput);
		for (Book* book : mainSystem.GetListOfBooks())
		{
			if (book->GetTitle() == selectedBook->GetTitle())
			{
				book->SetAuthor(authorInput);
			}
		}
	}
	else
	{
		cout << "Invalid input. Please try again." << endl;
		return;
	}
}

void Librarian::GenerateDataReport(System& mainSystem)
{
	dataReport.clear();

	for (Book* book : mainSystem.GetListOfBooks())
	{
		if (book->GetDueDate() <= 0)
		{
			dataReport.push_back(book);
		}
	}
}

void Librarian::PrintDataReport()
{
	for (Book* book : dataReport)
	{
		cout << "Title: " << book->GetTitle() << ", Author: " << book->GetAuthor() << ", Status: Overdue.";
	}
}

void Librarian::ViewRequests(System& mainSystem)
{
	for (Request* request : mainSystem.GetListOfRequests())
	{
		cout << "Requestee: " << request->GetRequestee() << endl;
		cout << "Related Book: " << request->GetRelatedBook() << endl;
		cout << "Type of Request: " << request->GetType() << endl;
	}
}

void Librarian::HandleRequest(Request* selectedRequest)
{
	selectedRequest->SetHandled(true);
}
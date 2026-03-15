#include <iostream>
#include <string>
#include "Member.h"

using namespace std;

Member::Member(string username, string password, int id) : User(username, password, id, 0)
{
	this->username = username;
	this->password = password;
	this->id = id;
	numberOfBorrowedBooks = 0;
}

Member::~Member()
{
}

int Member::GetNumberOfBorrowedBooks()
{
	return numberOfBorrowedBooks;
}

list<Book*> Member::GetBorrowedBooks()
{
	return borrowedBooks;
}

void Member::ViewBorrowedBooks()
{
	for (Book* book : borrowedBooks)
	{
		cout << "Title: " << book->GetTitle() << ", Author: " << book->GetAuthor() << ", Due Date: " << book->GetDueDate() << endl;
	}
}

void Member::SearchForBookTitle(System mainSystem)
{
	string titleInput;

	cout << "Enter the title of the book you want to search for: ";
	getline(cin, titleInput);

    for (Book* book : mainSystem.GetListOfBooks())
    {
        if (book->GetTitle() == titleInput)
        {
            cout << "Title: " << book->GetTitle() << ", Author: " << book->GetAuthor() << ", Availability: " << (book->GetAvailability() ? "Available" : "Unavailable") << endl;
            if (!book->GetAvailability())
            {
                cout << "Due Date: " << book->GetDueDate() << endl;
            }
            return;
        }
	}
}

void Member::SearchForBookAuthor(System mainSystem)
{
	string authorInput;
	bool foundAny = false;

	cout << "Enter the author of the book you want to search for: ";
	getline(cin, authorInput);

    for (Book* book : mainSystem.GetListOfBooks())
    {
        if (book->GetAuthor() == authorInput)
        {
            cout << "Title: " << book->GetTitle() << ", Author: " << book->GetAuthor() << ", Availability: " << (book->GetAvailability() ? "Available" : "Unavailable") << endl;
            if (!book->GetAvailability())
            {
                cout << "Due Date: " << book->GetDueDate() << endl;
            }
            if (!foundAny)
            {
                foundAny = true;
			}
        }
	}

    if (!foundAny)
    {
        cout << "Could not find books by that author." << endl;
	}
}

void Member::RequestBorrowBook(Book* selectedBook)
{
    if (numberOfBorrowedBooks >= 5) //will need to be updated to be the rule for max borrowed books
    {
        cout << "You have reached the maximum number of borrowed books. Please return a book before borrowing another." << endl;
        return;
    }

	numberOfBorrowedBooks++;

	selectedBook->SetAvailability(false);
	selectedBook->SetDueDate(7); //will need to be updated to be the rule for borrowing duration
}

void Member::ReturnBook(Book* selectedBook)
{
    for (Book* book : borrowedBooks)
    {
        if (book == selectedBook)
        {
            borrowedBooks.remove(book);
            numberOfBorrowedBooks--;
            break;
        }
	}

	selectedBook->SetAvailability(true);
}

void Member::RequestReserveBook(Book* selectedBook, System mainSystem)
{
	mainSystem.GetListOfRequests().push_back(new Request("Reserve", GetUsername(), selectedBook->GetTitle()));
}
#include <iostream>
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

void Member::RequestBorrowBook()
{
}

void Member::ViewBorrowedBooks()
{
}

void Member::SearchForBookTitle()
{
}

void Member::SearchForBookAuthor()
{
}

void Member::ReturnBook()
{
}

void Member::RequestReserveBook()
{
}
#include <iostream>
#include "Member.h"

using namespace std;

Member::Member(string username, string password, int id) : User(username, password, id)
{
	this->username = username;
	this->password = password;
	this->id = id;
	numberOfBorrowedBooks = 0;
}

Member::~Member()
{
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
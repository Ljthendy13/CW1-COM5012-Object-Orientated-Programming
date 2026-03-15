#include <iostream>
#include "Book.h"

using namespace std;

Book::Book(string title, string author)
{
	this->title = title;
	this->author = author;
	available = true;
	dueDate;
}

Book::~Book()
{
}

string Book::GetTitle()
{
	return title;
}

void Book::SetTitle(string titleInp)
{
	title = titleInp;
}

string Book::GetAuthor()
{
	return author;
}

void Book::SetAuthor(string authorInp)
{
	author = authorInp;
}

void Book::SetAvailability(bool availCheck)
{
	available = availCheck;
}

bool Book::GetAvailability()
{
	return available;
}

void Book::SetDueDate(int days)
{
	auto now = system_clock::now();
	dueDate = now + hours{ days * 24 };
}

double Book::GetDueDate()
{
	auto now = system_clock::now();
	
	auto trueDue = dueDate - now;

	return static_cast<double>(duration_cast<hours>(trueDue).count());
}
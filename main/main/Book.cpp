#include <iostream>
#include "Book.h"

using namespace std;

Book::Book(string title, string author)
{
	this->title = title;
	this->author = author;
	available = true;
}

string Book::GetTitle()
{
	return title;
}

string Book::GetAuthor()
{
	return author;
}

void Book::SetAvailability(bool availCheck)
{
	available = availCheck;
}

bool Book::GetAvailability()
{
	return available;
}
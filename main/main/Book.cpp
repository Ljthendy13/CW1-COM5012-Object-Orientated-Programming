#include <iostream>
#include "Book.h"

using namespace std;

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
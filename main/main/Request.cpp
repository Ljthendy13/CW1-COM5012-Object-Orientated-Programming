#include <iostream>
#include "Request.h"

using namespace std;

string Request::GetType()
{
	return type;
}

string Request::GetRequestee()
{
	return requestee;
}

Book* Request::GetRelatedBook()
{
	return relatedBook;
}

void Request::SetHandled(bool handledCheck)
{
	handled = handledCheck;
}

bool Request::GetHandled()
{
	return handled;
}
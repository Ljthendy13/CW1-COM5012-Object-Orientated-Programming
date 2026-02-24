#include <iostream>
#include "Request.h"

using namespace std;

Request::Request(string type, string requestee, Book* relatedBoo)
{
	this->type = type;
	this->requestee = requestee;
	this->relatedBook = relatedBoo;
	handled = false;
}

Request::~Request()
{
}

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
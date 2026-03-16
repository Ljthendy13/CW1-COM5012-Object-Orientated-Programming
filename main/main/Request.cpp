#include <iostream>
#include "Request.h"
#include "System.h"

using namespace std;

Request::Request(string type, string requestee, string relatedBook)
{
	this->type = type;
	this->requestee = requestee;
	this->relatedBook = relatedBook;
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

string Request::GetRelatedBook()
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
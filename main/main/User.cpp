#include <iostream>
#include "User.h"

using namespace std;

User::User(string username, string password, int id)
{
	this->username = username;
	this->password = password;
	this->id = id;
}

User::~User()
{
}

string User::GetUsername()
{
    return username;
}

void User::SetPassword(string passIn)
{
    password = passIn;
}

string User::GetPassword()
{
    return password;
}

int User::GetID()
{
    return id;
}

void User::ChangePassword()
{
}

void User::ViewAllBooks()
{
}
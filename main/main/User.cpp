#include <iostream>
#include "User.h"

using namespace std;

User::User(string username, string password, int id, int typeOfUser)
{
	this->username = username;
	this->password = password;
	this->id = id;
    this->typeOfUser = typeOfUser;
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

int User::GetTypeOfUser()
{
	return typeOfUser;
}

void User::ChangePassword()
{
}
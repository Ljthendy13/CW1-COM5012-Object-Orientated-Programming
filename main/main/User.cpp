#include <iostream>
#include "User.h"

using namespace std;

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
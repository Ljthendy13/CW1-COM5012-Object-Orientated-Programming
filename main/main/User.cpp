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
	string newPass, oldPass;

    cout << "Enter old password: ";
    cin >> oldPass;

    if (oldPass != GetPassword())
    {
        cout << "Incorrect password." << endl;
        return;
    }

    cout << "Enter new password: ";
    cin >> newPass;

    char confirmation;

    do
    {
        cout << "Are you sure you want to change your password? (Y/N): ";
        cin >> confirmation;
        confirmation = toupper(confirmation);
    } 
    while (confirmation != 'Y' && confirmation != 'N');

    if (confirmation == 'N')
    {
        cout << "Password change cancelled." << endl;
        return;
    }

    SetPassword(newPass);
	cout << "Password changed successfully." << endl;
}
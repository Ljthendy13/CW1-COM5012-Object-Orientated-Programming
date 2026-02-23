#include <iostream>
#include <random>
#include "System.h"

using namespace std;

System::System()
{
}

System::~System()
{
}

void System::Initialise()
{
	Member* defaultUser1 = new Member("Steve", "Password1", 1234);
	Member* defaultUser2 = new Member("John", "Password2", 5678);

	nonPrivateInformation.push_back(defaultUser1);
	nonPrivateInformation.push_back(defaultUser2);
}

void System::Register()
{
	string usernameInp = "";
	string passwordInp = "";
	int createdID = 0;

	do
	{
		cout << "Please enter your username: ";
		cin >> usernameInp;

		for (User* user : nonPrivateInformation)
		{
			if (user->GetUsername() == usernameInp)
			{
				cout << "An account with this username already exists. Please choose a new username." << endl << endl;
				usernameInp = "";
			}
		}
	} 
	while (usernameInp == "");

	cout << endl << "Please enter your password: ";
	cin >> passwordInp;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(0, 9999);

	createdID = distrib(gen);

	cout << endl << "Please confirm the following information:" << endl; 
	cout << "Your username will be: " << usernameInp << endl;
	cout << "Your password will be: " << passwordInp << endl;

	char confirmationInp = ' ';

	while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
	{
		cout << endl << "Is this information correct? (Y/N): ";
		cin >> confirmationInp;
	}

	if (confirmationInp == 'N' || confirmationInp == 'n')
	{
		cout << endl << "Registration cancelled. Please start again." << endl;
		Register();
		return;
	}

	cout << endl << "Your account has been created. Your ID is: " << createdID << endl;

	Member* newUser = new Member(usernameInp, passwordInp, createdID);
	nonPrivateInformation.push_back(newUser);
}

void System::Login()
{
	
}

void System::HidePrivateData()
{
}

void System::SendDueAlert()
{
}

void System::SendOverdueAlert()
{
}

void System::SendReserveAlert()
{
}
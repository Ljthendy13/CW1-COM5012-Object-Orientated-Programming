#include <iostream>
#include <string>
#include <random>
#include <limits>
#include "Administrator.h"

using namespace std;

Administrator::Administrator(string name, string pass, int id) : User(name, pass, id, 2)
{
}

Administrator::~Administrator()
{
}

void Administrator::SetRule(System& mainSystem)
{
	string newDescription;

	cout << "Please enter the description for this new rule: ";
	getline(cin, newDescription);

    char confirmationInp = ' ';

    while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
    {
        cout << "Does this rule have any associated values? (Y/N): ";
        cin >> confirmationInp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

    if (confirmationInp == 'N' || confirmationInp == 'n')
    {
        confirmationInp = ' ';

        while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
        {
            cout << "Is this information correct? (Y/N): ";
			cout << newDescription << endl;
            cin >> confirmationInp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        mainSystem.GetListOfRules().push_back(new Rule(newDescription, 0));
        return;
	}

	int newValue;

	cout << "Please enter the associated value for this rule: ";
	cin >> newValue;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    confirmationInp = ' ';
    while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
    {
        cout << "Is this information correct? (Y/N): ";
        cout << newDescription << endl;
        cout << newValue << endl;
        cin >> confirmationInp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

    if (confirmationInp == 'N' || confirmationInp == 'n')
    {
        cout << "Creation cancelled." << endl;
        return;
	}

    mainSystem.GetListOfRules().push_back(new Rule(newDescription, newValue));
}

void Administrator::ViewRules(System& mainSystem)
{
    for (Rule* rule : mainSystem.GetListOfRules())
    {
        cout << "Description: " << rule->GetDescription();
        if (rule->GetAssociatedValue() != NULL)
        {
            cout << ", Associated Value: " << rule->GetAssociatedValue() << endl;
        }
	}
}

void Administrator::EditRule(Rule* selectedRule, System& mainSystem)
{
	int choiceInput;
	string descriptionInput;
	int valueInput;

	cout << "Would you like to edit the description or associated value of this rule? (1/2): ";
	cin >> choiceInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choiceInput == 1)
    {
        cout << "What would you like to change the description to? ";
        getline(cin, descriptionInput);
        for (Rule* rule : mainSystem.GetListOfRules())
        {
            if (rule->GetDescription() == selectedRule->GetDescription())
            {
                rule->SetDescription(descriptionInput);
            }
        }
    }
    else if (choiceInput == 2)
    {
        cout << "What would you like to change the associated value to? ";
        cin >> valueInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (Rule* rule : mainSystem.GetListOfRules())
        {
            if (rule->GetDescription() == selectedRule->GetDescription())
            {
                rule->SetAssociatedValue(valueInput);
            }
        }
    }
    else
    {
        cout << "Invalid input. Please try again." << endl;
        return;
	}
}

void Administrator::RemoveRule(Rule* selectedRule, System& mainSystem)
{
    mainSystem.GetListOfRules().remove(selectedRule);
}

void Administrator::ManageMemberData(System& mainSystem)
{
	int choiceInput;

	cout << "Would you like to view members or remove members? (1/2): ";
	cin >> choiceInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (User* user : mainSystem.GetListOfUsers())
    {
        if (user->GetTypeOfUser() == 0)
        {
            cout << "Username: " << user->GetUsername() << " ID: " << user->GetID() << endl;
        }
	}

    if (choiceInput == 2)
    {
		int selectedID;

        cout << "Please enter the ID of the member you would like to remove: ";
        cin >> selectedID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (User* user : mainSystem.GetListOfUsers())
        {
            if (user->GetID() == selectedID)
            {
				cout << "Username: " << user->GetUsername() << " ID: " << user->GetID() << " selected." << endl;
            }
		}

        char confirmationInp = ' ';

        while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
        {
            cout << "Are you sure you want to remove this member? (Y/N): ";
            cin >> confirmationInp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (confirmationInp == 'N' || confirmationInp == 'n')
        {
            cout << "Deletion cancelled." << endl;
            return;
		}

        for (User* user : mainSystem.GetListOfUsers())
        {
            if (user->GetID() == selectedID)
            {
                mainSystem.GetListOfUsers().remove(user);
            }
        }
    }
}

void Administrator::ManageLibrarianData(System& mainSystem)
{
	int choiceInput;

	cout << "Would you like to view librarians, add librarians or remove librarians? (1/2/3): ";
	cin >> choiceInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choiceInput == 1)
    {
        for (User* user : mainSystem.GetListOfUsers())
        {
            if (user->GetTypeOfUser() == 1)
            {
                cout << "Username: " << user->GetUsername() << ", ID: " << user->GetID() << endl;
            }
        }
    }
    else if (choiceInput == 2)
    {
        string usernameInput;
        string passwordInput;
        int id;

        cout << "Please enter the username for this new librarian: ";
        getline(cin, usernameInput);

        do
        {
            for (User* user : mainSystem.GetListOfUsers())
            {
                if (user->GetUsername() == usernameInput)
                {
                    cout << "A user with this name already exists. Please choose a new username." << endl << endl;
                    usernameInput = "";
                }
            }
        } 
        while (usernameInput == "");

        cout << endl << "Please enter the password for this new librarian: ";
        getline(cin, passwordInput);

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 9999);

        id = distrib(gen);
        cout << endl << "Please confirm the following information:" << endl;
        cout << "The librarian's username will be: " << usernameInput << endl;
        cout << "The librarian's password will be: " << passwordInput << endl;

        char confirmationInp = ' ';

        while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
        {
            cout << endl << "Is this information correct? (Y/N): ";
            cin >> confirmationInp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (confirmationInp == 'N' || confirmationInp == 'n')
        {
            cout << endl << "Registration cancelled." << endl;
            return;
        }

        mainSystem.GetListOfUsers().push_back(new Librarian(usernameInput, passwordInput, id));
	}
    else if (choiceInput == 3)
    {
        for (User* user : mainSystem.GetListOfUsers())
        {
            if (user->GetTypeOfUser() == 1)
            {
                cout << "Username: " << user->GetUsername() << ", ID: " << user->GetID() << endl;
            }
        }

        int selectedID;
        cout << "Please enter the ID of the librarian you would like to remove: ";
        cin >> selectedID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (User* user : mainSystem.GetListOfUsers())
        {
            if (user->GetID() == selectedID)
            {
                cout << "Username: " << user->GetUsername() << ", ID: " << user->GetID() << " selected." << endl;
            }
        }
        char confirmationInp = ' ';
        while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
        {
            cout << "Are you sure you want to remove this librarian? (Y/N): ";
            cin >> confirmationInp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (confirmationInp == 'N' || confirmationInp == 'n')
        {
            cout << "Deletion cancelled." << endl;
            return;
        }

        for (User* user : mainSystem.GetListOfUsers())
        {
            if (user->GetID() == selectedID)
            {
                mainSystem.GetListOfUsers().remove(user);
            }
		}
    }
}
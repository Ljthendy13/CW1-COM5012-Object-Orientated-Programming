#pragma once

#include <iostream>
#include <list>
#include "Book.h"
#include "Request.h"
#include "Rule.h"
#include "Member.h"
#include "Librarian.h"
#include "Administrator.h"

using namespace std;

class System
{
private:
    list<Book*> listOfBooks;
    list<User*> nonPrivateInformation;
    list<Request*> listOfRequests;
    list<Rule*> listOfRules;
    User* currentUser;
public:
    System();
    ~System();
    void SendDueAlert();
    void SendOverdueAlert();
    void SendReserveAlert();
    void Login();
    void Initialise();
    void Register();
	list<Book*> GetListOfBooks();
};
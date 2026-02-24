#pragma once

#include <iostream>
#include <list>
#include "User.h"
#include "System.h"

using namespace std;

class Librarian : public User
{
private:
    list<Request*> unhandledRequests;
    string dataReport;
public:
    Librarian();
    ~Librarian();
    void AddBook();
    void RemoveBook();
    void UpdateBook();
    void GenerateDataReport();
    void PrintDataReport();
    void HandleRequest();
};
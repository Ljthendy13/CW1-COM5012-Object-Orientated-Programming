#pragma once

#include <iostream>
#include <list>
#include "User.h"
#include "System.h"

using namespace std;

class Librarian : public User
{
private:
    string dataReport;
public:
	Librarian(string username, string password, int id);
    ~Librarian();
    void AddBook();
    void RemoveBook();
    void UpdateBook();
    void GenerateDataReport();
    void PrintDataReport();
    void HandleRequest();
};
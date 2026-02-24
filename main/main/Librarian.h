#pragma once

#include <iostream>
#include <list>
#include "User.h"

class System;

using namespace std;

class Librarian : public User
{
private:
    string dataReport;
public:
	Librarian(string username, string password, int id);
    ~Librarian();
    void AddBook(System mainSystem);
    void RemoveBook();
    void UpdateBook();
    void GenerateDataReport();
    void PrintDataReport();
    void HandleRequest();
};
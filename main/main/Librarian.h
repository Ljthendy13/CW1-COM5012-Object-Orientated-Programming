#pragma once

#include <iostream>
#include <list>
#include "User.h"
#include "System.h"

class System;

using namespace std;

class Librarian : public User
{
private:
    list<Book*> dataReport;
public:
	Librarian(string username, string password, int id);
    ~Librarian();
    void AddBook(System mainSystem);
    void RemoveBook(Book* selectedBook, System mainSystem);
    void UpdateBook(Book* selectedBook, System mainSystem);
    void GenerateDataReport(System mainSystem);
    void PrintDataReport();
	void ViewRequests(System mainSystem);
    void HandleRequest(Request* selectedRequest);
};
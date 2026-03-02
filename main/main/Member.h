#pragma once

#include <iostream>
#include <list>
#include "User.h"
#include "System.h"

using namespace std;

class Member : public User
{
private:
    int numberOfBorrowedBooks;
    list<Book*> borrowedBooks;
public:
    Member(string username, string password, int id);
    ~Member();
    int GetNumberOfBorrowedBooks();
    list<Book*> GetBorrowedBooks();
    void RequestBorrowBook();
    void ViewBorrowedBooks();
    void SearchForBookTitle();
    void SearchForBookAuthor();
    void ReturnBook();
    void RequestReserveBook();
};
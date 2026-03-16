#pragma once

#include <iostream>
#include <list>
#include "User.h"
#include "System.h"

class System;

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
    void BorrowBook(Book* selectedBook, System& mainSystem);
    void ViewBorrowedBooks();
    void SearchForBookTitle(System& mainSystem);
    void SearchForBookAuthor(System& mainSystem);
    void ReturnBook(Book* selectedBook);
    void RequestReserveBook(Book* selectedBook, System& mainSystem);
};
#include <iostream>
#include <list>
#include "User.h"
#include "Book.h"

using namespace std;

class Member : public User
{
private:
    int numberOfBorrowedBooks;
    list<Book*> borrowedBooks;
public:
    Member();
    ~Member();
    void RequestBorrowBook();
    void ViewBorrowedBooks();
    void SearchForBookTitle();
    void SearchForBookAuthor();
    void ReturnBook();
    void RequestReserveBook();
};
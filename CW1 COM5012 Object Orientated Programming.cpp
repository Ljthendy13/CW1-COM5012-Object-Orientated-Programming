#include <iostream>
#include <list>

using namespace std;

class Book
{
private:
    string title;
    string author;
    bool available;
public:
    Book(string title, string author);
    ~Book();
    string GetTitle();
    string GetAuthor();
    void SetAvailability(bool);
    bool GetAvailability();
};

class Request
{
private:
    string type;
    string requestee;
    Book* relatedBook;
    bool handled;
public:
    Request();
    ~Request();
    string GetType();
    string GetRequestee();
    string GetRelatedBook();
    void SetHandled(bool);
    bool GetHandled();
};

class Rule
{
private:
    string description;
public:
    Rule(string description);
    ~Rule();
    string GetDescription();
};

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

class Administrator : public User
{
private:
    list<Rule*> currentRules;
    list<User*> systemUsers;
public:
    Administrator();
    ~Administrator();
    void SetRule();
    void EditRule();
    void RemoveRule();
    void ManageMemberData();
    void ManageLibrarianData();
};

class System
{
private:
    list<Book*> listOfBooks;
    list<User*> nonPrivateInformation;
public:
    System();
    ~System();
    void HidePrivateData();
    void SendDueAlert();
    void SendOverdueAlert();
    void SendReserveAlert();
};

int main()
{
    cout << "hello";

    return 0;
}
#include <iostream>

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
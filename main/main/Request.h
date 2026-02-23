#include <iostream>
#include "Book.h"

using namespace std;

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
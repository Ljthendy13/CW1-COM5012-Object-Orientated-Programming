#pragma once

#include <iostream>

using namespace std;

class Request
{
private:
    string type;
    string requestee;
    string relatedBook;
    bool handled;
public:
    Request(string type, string requestee, string relatedBook);
    ~Request();
    string GetType();
    string GetRequestee();
    string GetRelatedBook();
    void SetHandled(bool);
    bool GetHandled();
};
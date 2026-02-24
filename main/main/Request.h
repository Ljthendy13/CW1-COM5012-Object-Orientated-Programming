#pragma once

#include <iostream>
#include "System.h"

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
    Book* GetRelatedBook();
    void SetHandled(bool);
    bool GetHandled();
};
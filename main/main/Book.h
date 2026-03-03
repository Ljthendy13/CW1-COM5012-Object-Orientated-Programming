#pragma once

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Book
{
private:
    string title;
    string author;
    bool available;
    system_clock::time_point dueDate;
public:
    Book(string title, string author);
    ~Book();
    string GetTitle();
    string GetAuthor();
    void SetAvailability(bool);
    bool GetAvailability();
    void SetDueDate(int);
    double GetDueDate();
};
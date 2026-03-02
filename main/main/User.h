#pragma once

#include <iostream>

using namespace std;

class User
{
protected:
    string username;
    string password;
    int id;
    int typeOfUser; // 0 for member, 1 for librarian, 2 for admin
public:
    User(string username, string password, int id, int typeOfUser);
    virtual ~User();
    string GetUsername();
    void SetPassword(string);
    string GetPassword();
    int GetID();
    int GetTypeOfUser();
    void ChangePassword();
    void ViewAllBooks();
};
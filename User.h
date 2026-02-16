#include <iostream>

using namespace std;

class User
{
protected:
    string username;
    string password;
    int id;
public:
    User(string username, string password, int id);
    virtual ~User();
    string GetUsername();
    void SetPassword(string);
    string GetPassword();
    int GetID();
    void Login();
    void ChangePassword();
    void ViewAllBooks();
};
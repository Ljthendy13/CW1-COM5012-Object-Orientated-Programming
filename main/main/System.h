#include <iostream>
#include <list>
#include "User.h"
#include "Book.h"

using namespace std;

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
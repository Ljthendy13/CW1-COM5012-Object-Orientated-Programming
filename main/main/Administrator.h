#pragma once

#include <iostream>
#include <list>
#include "User.h"
#include "System.h"

using namespace std;

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
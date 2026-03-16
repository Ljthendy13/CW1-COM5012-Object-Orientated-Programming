#pragma once

#include <iostream>
#include <list>
#include "User.h"
#include "System.h"

class System;

using namespace std;

class Administrator : public User
{
private:
public:
    Administrator(string username, string password, int id);
    ~Administrator();
    void SetRule(System& mainSystem);
	void ViewRules(System& mainSystem);
    void EditRule(Rule* selectedRule, System& mainSystem);
    void RemoveRule(Rule* selectedRule, System& mainSystem);
    void ManageMemberData(System& mainSystem);
    void ManageLibrarianData(System& mainSystem);
};
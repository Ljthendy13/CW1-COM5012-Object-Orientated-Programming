#pragma once

#include <iostream>

using namespace std;

class Rule
{
private:
    string description;
public:
    Rule(string description);
    ~Rule();
    string GetDescription();
};
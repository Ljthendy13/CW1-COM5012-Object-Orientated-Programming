#pragma once

#include <iostream>

using namespace std;

class Rule
{
private:
    string description;
    int associatedValue;
public:
    Rule(string description);
    ~Rule();
    string GetDescription();
	void SetDescription(string newDescription);
	int GetAssociatedValue();
	void SetAssociatedValue(int newValue);
};
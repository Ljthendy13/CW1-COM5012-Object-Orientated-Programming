#pragma once

#include <iostream>

using namespace std;

class Rule
{
private:
    string description;
    int associatedValue;
public:
    Rule(string description, int associatedValue); //0 for null
    ~Rule();
    string GetDescription();
	void SetDescription(string newDescription);
	int GetAssociatedValue();
	void SetAssociatedValue(int newValue);
};
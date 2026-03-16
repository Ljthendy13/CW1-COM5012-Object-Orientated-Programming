#include <iostream>
#include "Rule.h"

using namespace std;

Rule::Rule(string description, int associatedValue)
{
	this->description = description;
	this->associatedValue = associatedValue;
}

Rule::~Rule()
{
}

string Rule::GetDescription()
{
	return description;
}

void Rule::SetDescription(string newDescription)
{
	description = newDescription;
}

int Rule::GetAssociatedValue()
{
	return associatedValue;
}

void Rule::SetAssociatedValue(int newValue)
{
	associatedValue = newValue;
}
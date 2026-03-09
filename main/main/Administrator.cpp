#include <iostream>
#include "Administrator.h"

using namespace std;

Administrator::Administrator(string name, string pass, int id) : User(name, pass, id, 2)
{
}

Administrator::~Administrator()
{
}

void Administrator::SetRule()
{
}

void Administrator::EditRule()
{
}

void Administrator::RemoveRule()
{
}

void Administrator::ManageMemberData()
{
}

void Administrator::ManageLibrarianData()
{
}
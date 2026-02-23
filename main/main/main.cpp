#include <iostream>
#include "System.h"

using namespace std;

int main() 
{
	System system;
	system.Initialise();

	system.Register(); // will be in menu
	system.Login(); //will be too

	return 0;
}
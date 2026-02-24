#include <iostream>
#include "System.h"

using namespace std;

int main() 
{
	System system;
	system.Initialise();

	system.Register(); // will be in menu
	system.Login(); //will be too

	Librarian* librarian1 = new Librarian("Librarian1", "LibPass1", 4321); //for testing

	librarian1->AddBook(); //only available to logged in librarians, will be in a menu

	return 0;
}
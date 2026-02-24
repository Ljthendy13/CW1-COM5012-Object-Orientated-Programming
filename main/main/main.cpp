#include <iostream>
#include "System.h"

using namespace std;

int main() 
{
	System mainSystem;
	mainSystem.Initialise();

	mainSystem.Register(); // will be in menu
	mainSystem.Login(); //will be too

	Librarian* librarian1 = new Librarian("Librarian1", "LibPass1", 4321); //for testing

	librarian1->AddBook(mainSystem); //only available to logged in librarians, will be in a menu

	return 0;
}
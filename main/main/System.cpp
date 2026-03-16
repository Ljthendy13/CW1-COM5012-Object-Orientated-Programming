#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <string>
#include <limits>
#include "System.h"

using namespace std;

System::System()
{
	currentUser = nullptr;
}

System::~System()
{
}

void System::Initialise()
{
	delete currentUser;
	currentUser = nullptr;

	listOfUsers.push_back(new Member("Steve", "Password1", 1234));
	listOfUsers.push_back(new Member("John", "Password2", 5678));
	listOfUsers.push_back(new Librarian("Lucy", "Password3", 9012));
	listOfUsers.push_back(new Administrator("Luke", "Password4", 3456));

	listOfBooks.push_back(new Book("The Great Gatsby", "F. Scott Fitzgerald"));
	listOfBooks.push_back(new Book("To Kill a Mockingbird", "Harper Lee"));
	listOfBooks.push_back(new Book("1984", "George Orwell"));
	listOfBooks.push_back(new Book("Pride and Prejudice", "Jane Austen"));
	listOfBooks.push_back(new Book("The Catcher in the Rye", "J.D. Salinger"));
	listOfBooks.push_back(new Book("The Lord of the Rings", "J.R.R. Tolkien"));
	listOfBooks.push_back(new Book("The Hobbit", "J.R.R. Tolkien"));
	listOfBooks.push_back(new Book("The King In Yellow", "Robert W. Chambers"));

	listOfRules.push_back(new Rule("Borrow Limit", 5));
	listOfRules.push_back(new Rule("Borrow Duration", 7));

	/* store user steve in a temp variable, then assign a few books to him, at least two should be overdue*/

	Member* temp = dynamic_cast<Member*>(listOfUsers.front());

	temp->BorrowBook(listOfBooks.front(), *this);
	temp->BorrowBook(listOfBooks.back(), *this); //make this book overdue by setting its due date to a past time

	listOfBooks.back()->SetDueDate(-1);
}

void System::Register()
{
	cout << "~~~~~~~~~~~~~~~ REGISTER ~~~~~~~~~~~~~~~" << endl;

	string usernameInp = "";
	string passwordInp = "";
	int createdID = 0;

	cout << "Please enter your username: ";

	do
	{
		getline(cin, usernameInp);

		for (User* user : listOfUsers)
		{
			if (user->GetUsername() == usernameInp)
			{
				cout << "An account with this username already exists. Please choose a new username." << endl << endl;
				usernameInp = "";
			}
		}
	} 
	while (usernameInp == "");

	cout << "Please enter your password: ";
	getline(cin, passwordInp);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(0, 9999);

	createdID = distrib(gen);

	cout << endl << "Please confirm the following information:" << endl; 
	cout << "Your username will be: " << usernameInp << endl;
	cout << "Your password will be: " << passwordInp << endl;

	char confirmationInp = ' ';

	while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
	{
		cout << endl << "Is this information correct? (Y/N): ";
		cin >> confirmationInp;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	if (confirmationInp == 'N' || confirmationInp == 'n')
	{
		cout << endl << "Registration cancelled. Please start again." << endl;
		Register();
	}

	cout << endl << "Your account has been created. Your ID is: " << createdID << endl;

	listOfUsers.push_back(new Member(usernameInp, passwordInp, createdID));

	for (User* user : listOfUsers)
	{
		if (user->GetUsername() == usernameInp)
		{
			currentUser = user;
		}
	}
}

void System::Login()
{
	cout << "~~~~~~~~~~~~~~~ LOG IN ~~~~~~~~~~~~~~~" << endl;

	string usernameInp;
	string passwordInp;
	bool loggedIn = false;
	int passTries = 0;

	cout << "Please enter your username: ";
	getline(cin, usernameInp);

	for (User* user : listOfUsers)
	{
		if (user->GetUsername() == usernameInp)
		{
			currentUser = user;
		}
	}

	if (currentUser == NULL)
	{
		cout << "Account not found. Please try again.";
		Menus();
	}

	while (!loggedIn && passTries < 3)
	{
		cout << "Please enter your password: ";
		getline(cin, passwordInp);

		if (currentUser->GetPassword() == passwordInp)
		{
			loggedIn = true;
		}
		else 
		{
			passTries++;
			cout << "Incorrect password entered." << endl;
		}

		if (passTries == 3)
		{
			cout << "Too many incorrect password attempts. Please try again later.";
			delete currentUser;
			currentUser = nullptr;
			Menus();
		}
	}

	cout << "Login Validated.";
}

void System::SendDueAlert()
{
	Member* temp = dynamic_cast<Member*>(currentUser);

	if (temp == nullptr)
	{
		Menus();
	}

	if (temp->GetNumberOfBorrowedBooks() != 0)
	{
		for (Book* book : temp->GetBorrowedBooks())
		{
			if (book->GetDueDate() > 0)
			{
				cout << book->GetTitle() << " is due in " << book->GetDueDate() << " hours." << endl << endl;
			}
		}

		char confirmationInp = ' ';

		do
		{
			cout << "Please confirm your acknowledgement (Y): ";
			cin >> confirmationInp;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} 
		while (confirmationInp != 'Y' && confirmationInp != 'y');
	}
}

void System::SendOverdueAlert()
{
	Member* temp = dynamic_cast<Member*>(currentUser);

	bool hasOverdueBooks = false;

	if (temp == nullptr)
	{
		Menus();
	}

	if (temp->GetNumberOfBorrowedBooks() != 0)
	{
		for (Book* book : temp->GetBorrowedBooks())
		{
			if (book->GetDueDate() <= 0)
			{
				cout << book->GetTitle() << " is overdue. You will not be able to borrow another book until it is returned." << endl << endl;
				if (hasOverdueBooks == false)
				{
					hasOverdueBooks = true;
				}
			}
		}

		if (hasOverdueBooks == true)
		{
			char confirmationInp = ' ';

			do
			{
				cout << "Please confirm your acknowledgement (Y): ";
				cin >> confirmationInp;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (confirmationInp != 'Y' && confirmationInp != 'y');
		}
	}
}

void System::SendReserveAlert()
{
	Member* temp = dynamic_cast<Member*>(currentUser);

	if (temp == nullptr)
	{
		Menus();
	}

	for (Request* request : listOfRequests)
	{
		if (request->GetRequestee() == temp->GetUsername())
		{
			for (Book* book : listOfBooks)
			{
				if (request->GetRelatedBook() == book->GetTitle())
				{
					if (book->GetAvailability() == true)
					{
						dynamic_cast<Member*>(currentUser)->BorrowBook(book, *this);
						cout << "Your Reserved Book: " << book->GetTitle() << " was returned, and is now borrowed by you. It will be due for return on " << book->GetDueDate() << endl << endl;

						char confirmationInp = ' ';

						do
						{
							cout << "Please confirm your acknowledgement (Y): ";
							cin >> confirmationInp;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						} while (confirmationInp != 'Y' && confirmationInp != 'y');
					}
				}
			}
		}
	}
}

list<User*>& System::GetListOfUsers()
{
	return listOfUsers;
}

list<Book*>& System::GetListOfBooks()
{
	return listOfBooks;
}

list<Request*>& System::GetListOfRequests()
{
	return listOfRequests;
}

list<Rule*>& System::GetListOfRules()
{
	return listOfRules;
}

void System::ViewAllBooks()
{
	for (Book* book : listOfBooks)
	{
		cout << "Title: " << book->GetTitle() << " | Author: " << book->GetAuthor() << " | Available: " << book->GetAvailability() << endl;
	}
}

void System::Menus()
{
	system("CLS");
	int choice = NULL;
	bool loggedIn = (currentUser != nullptr);

	if (loggedIn == false)
	{
		cout << "~~~~~~~~~~~~~~~ Welcome to the BNU Smart Library ~~~~~~~~~~~~~~~" << endl << endl;
		cout << "Please select an option from the menu below:" << endl;
		cout << "1. Register" << endl;
		cout << "2. Log In" << endl;

		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if (choice == 1)
		{
			system("CLS");
			Register();
		}
		else if (choice == 2)
		{
			system("CLS");
			Login();
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			Menus();
		}

		if (currentUser->GetTypeOfUser() == 0)
		{
			system("CLS");
			SendDueAlert();
			system("CLS");
			SendOverdueAlert();
			system("CLS");
			SendReserveAlert();
		}
	}

	system("CLS");

	if (currentUser->GetTypeOfUser() == 0)
	{
		cout << "~~~~~~~~~~~~~~~ Member Menu ~~~~~~~~~~~~~~~" << endl << endl;

		cout << "Please select an option from the menu below:" << endl;
		cout << "1. View All Books" << endl;
		cout << "2. Search For Book By Title" << endl;
		cout << "3. Search For Book By Author" << endl;
		cout << "4. View Borrowed Books" << endl;
		cout << "5. Borrow Book" << endl;
		cout << "6. Return Book" << endl;
		cout << "7. Log Out" << endl;
		cout << "8. Change Password" << endl;

		choice = NULL;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choice == 1)
		{
			system("CLS");
			ViewAllBooks();

			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Menus();
		}
		else if (choice == 2)
		{
			system("CLS");
			dynamic_cast<Member*>(currentUser)->SearchForBookTitle(*this);

			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Menus();
		}
		else if (choice == 3)
		{
			system("CLS");
			dynamic_cast<Member*>(currentUser)->SearchForBookAuthor(*this);

			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Menus();
		}
		else if (choice == 4)
		{
			system("CLS");
			dynamic_cast<Member*>(currentUser)->ViewBorrowedBooks();

			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			Menus();
		}
		else if (choice == 5)
		{
			system("CLS");
			choice = NULL;
			cout << "~~~~~~~~~~~~~~~ Borrowing a Book ~~~~~~~~~~~~~~~" << endl << endl;

			cout << "How would you like to search for the book you want to borrow?" << endl;
			cout << "1. Search by Title" << endl;
			cout << "2. Search by Author" << endl;
			cout << "3. View All Books" << endl;

			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (choice == 1)
			{
				system("CLS");
				dynamic_cast<Member*>(currentUser)->SearchForBookTitle(*this);
			}
			else if (choice == 2)
			{
				system("CLS");
				dynamic_cast<Member*>(currentUser)->SearchForBookAuthor(*this);
			}
			else if (choice == 3)
			{
				system("CLS");
				ViewAllBooks();
			}
			else
			{
				cout << "Invalid input. Please try again." << endl;
				system("CLS");
				Menus();
			}

			string titleInput;

			cout << endl << "Enter the title of the book you want to borrow: ";
			getline(cin, titleInput);

			Book* selectedBook = nullptr;

			for (Book* book : listOfBooks)
			{
				if (book->GetTitle() == titleInput)
				{
					selectedBook = book;
				}
			}

			if (selectedBook->GetAvailability() == false)
			{
				for (Request* request : listOfRequests)
				{
					if (request->GetRelatedBook() == selectedBook->GetTitle())
					{
						if (request->GetHandled() == false)
						{
							cout << "This book is currently borrowed by another user and has a pending reservation." << endl;
							cout << "Enter any input to return to the menu." << endl;
							cin >> choice;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							Menus();
						}
						char confirmationInp = ' ';

						while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
						{
							cout << "This book is currently borrowed by another user. Would you like to reserve it? (Y/N): ";
							cin >> confirmationInp;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						if (confirmationInp == 'N' || confirmationInp == 'n')
						{
							cout << endl << "Reservation creation cancelled." << endl;
							cout << "Enter any input to return to the menu." << endl;
							cin >> choice;
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							Menus();
						}

						dynamic_cast<Member*>(currentUser)->RequestReserveBook(selectedBook, *this);
						cout << "Reservation created. When this book is returned and a Librarian has handled your request, it will be added to your account and you will be notified." << endl;
						cout << "Enter any input to return to the menu." << endl;
						cin >> choice;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						Menus();
					}
				}

				char confirmationInp = ' ';

				while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
				{
					cout << "This book is currently borrowed by another user. Would you like to reserve it? (Y/N): ";
					cin >> confirmationInp;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (confirmationInp == 'N' || confirmationInp == 'n')
				{
					cout << endl << "Reservation creation cancelled." << endl;
					cout << "Enter any input to return to the menu." << endl;
					cin >> choice;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					Menus();
				}

				dynamic_cast<Member*>(currentUser)->RequestReserveBook(selectedBook, *this);
				cout << "Reservation created. When this book is returned and a Librarian has handled your request, it will be added to your account and you will be notified." << endl;
				cout << "Enter any input to return to the menu." << endl;
				cin >> choice;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				Menus();
			}

			dynamic_cast<Member*>(currentUser)->BorrowBook(selectedBook, *this);
			cout << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 6)
		{
			system("CLS");
			system("CLS");
			choice = 0;
			string titleInput;
			cout << "~~~~~~~~~~~~~~~ Returning a Book ~~~~~~~~~~~~~~~" << endl << endl;
			cout << "Here are the books you have currently borrowed:" << endl;
			dynamic_cast<Member*>(currentUser)->ViewBorrowedBooks();
			cout << endl << endl << "Enter the title of the book you want to return: ";
			getline(cin, titleInput);

			Book* selectedBook = nullptr;

			for (Book* book : listOfBooks)
			{
				if (book->GetTitle() == titleInput)
				{
					selectedBook = book;
				}
			}

			dynamic_cast<Member*>(currentUser)->ReturnBook(selectedBook);

			cout << selectedBook->GetTitle() << " has been returned." << endl;
			cout << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();

			dynamic_cast<Member*>(currentUser)->ReturnBook(nullptr);
		}
		else if (choice == 7)
		{
			currentUser = nullptr;
			system("CLS");
			Menus();
		}
		else if (choice == 8)
		{
			system("CLS");
			currentUser->ChangePassword();
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			Menus();
		}
	}
	else if (currentUser->GetTypeOfUser() == 1)
	{
		cout << "~~~~~~~~~~~~~~~ Librarian Menu ~~~~~~~~~~~~~~~" << endl << endl;

		cout << "Please select an option from the menu below:" << endl;
		cout << "1. View All Books" << endl;
		cout << "2. Add Book" << endl;
		cout << "3. Update Book" << endl;
		cout << "4. Remove Book" << endl;
		cout << "5. Print Data Report" << endl;
		cout << "6. View Requests" << endl;
		cout << "7. Handle Requests" << endl;
		cout << "8. Log Out" << endl;
		cout << "9. Change Password" << endl;

		choice = NULL;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choice == 1)
		{
			system("CLS");
			ViewAllBooks();
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 2)
		{
			system("CLS");
			dynamic_cast<Librarian*>(currentUser)->AddBook(*this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 3)
		{
			system("CLS");
			string titleInput;
			ViewAllBooks();
			cout << "Enter the title of the book you want to update: ";
			getline(cin, titleInput);
			Book* selectedBook = nullptr;
			for (Book* book : listOfBooks)
			{
				if (book->GetTitle() == titleInput)
				{
					selectedBook = book;
				}
			}
			if (selectedBook == nullptr)
			{
				cout << "Book not found. Please try again." << endl;
				Menus();
			}
			dynamic_cast<Librarian*>(currentUser)->UpdateBook(selectedBook, *this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 4)
		{
			system("CLS");
			string titleInput;
			ViewAllBooks();
			cout << "Enter the title of the book you want to remove: ";
			getline(cin, titleInput);
			Book* selectedBook = nullptr;
			for (Book* book : listOfBooks)
			{
				if (book->GetTitle() == titleInput)
				{
					selectedBook = book;
				}
			}
			if (selectedBook == nullptr)
			{
				cout << "Book not found. Please try again." << endl;
				return;
			}
			dynamic_cast<Librarian*>(currentUser)->RemoveBook(selectedBook, *this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 5)
		{
			system("CLS");
			dynamic_cast<Librarian*>(currentUser)->GenerateDataReport(*this);
			dynamic_cast<Librarian*>(currentUser)->PrintDataReport();
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 6)
		{
			system("CLS");
			dynamic_cast<Librarian*>(currentUser)->ViewRequests(*this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 7)
		{
			system("CLS");
			string titleInput;
			dynamic_cast<Librarian*>(currentUser)->ViewRequests(*this);
			cout << "Enter the title of the book for the request you want to handle: ";
			getline(cin, titleInput);
			Request* selectedRequest = nullptr;
			for (Request* request : listOfRequests)
			{
				if (request->GetRelatedBook() == titleInput)
				{
					selectedRequest = request;
				}
			}
			if (selectedRequest == nullptr)
			{
				cout << "Request not found. Please try again." << endl;
				Menus();
			}
			dynamic_cast<Librarian*>(currentUser)->HandleRequest(selectedRequest);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 8)
		{
			currentUser = nullptr;
			system("CLS");
			Menus();
		}
		else if (choice == 9)
		{
			system("CLS");
			currentUser->ChangePassword();
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			Menus();
		}
	}
	else if (currentUser->GetTypeOfUser() == 2)
	{
		cout << "~~~~~~~~~~~~~~~ Administrator Menu ~~~~~~~~~~~~~~~" << endl << endl;

		cout << "Please select an option from the menu below:" << endl;
		cout << "1. View All Books" << endl;
		cout << "2. Set Rule" << endl;
		cout << "3. Update Rule" << endl;
		cout << "4. Remove Rule" << endl;
		cout << "5. Manage Member Data" << endl;
		cout << "6. Manage Librarian Data" << endl;
		cout << "7. Log Out" << endl;
		cout << "8. Change Password" << endl;

		choice = NULL;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (choice == 1)
		{
			system("CLS");
			ViewAllBooks();
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 2)
		{
			system("CLS");
			dynamic_cast<Administrator*>(currentUser)->SetRule(*this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 3)
		{
			system("CLS");
			string descriptionInput;
			dynamic_cast<Administrator*>(currentUser)->ViewRules(*this);
			cout << "Enter the description of the rule you want to update: ";
			getline(cin, descriptionInput);
			Rule* selectedRule = nullptr;
			for (Rule* rule : listOfRules)
			{
				if (rule->GetDescription() == descriptionInput)
				{
					selectedRule = rule;
				}
			}
			if (selectedRule == nullptr)
			{
				cout << "Rule not found. Please try again." << endl;
				return;
			}
			dynamic_cast<Administrator*>(currentUser)->EditRule(selectedRule, *this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 4)
		{
			system("CLS");
			string descriptionInput;
			dynamic_cast<Administrator*>(currentUser)->ViewRules(*this);
			cout << "Enter the description of the rule you want to remove: ";
			getline(cin, descriptionInput);
			Rule* selectedRule = nullptr;
			for (Rule* rule : listOfRules)
			{
				if (rule->GetDescription() == descriptionInput)
				{
					selectedRule = rule;
				}
			}
			if (selectedRule == nullptr)
			{
				cout << "Rule not found. Please try again." << endl;
				return;
			}

			char confirmationInp = ' ';

			while (confirmationInp != 'Y' && confirmationInp != 'N' && confirmationInp != 'y' && confirmationInp != 'n')
			{
				cout << "Are you sure you want to remove this rule? (Y/N): ";
				cin >> confirmationInp;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			if (confirmationInp == 'N' || confirmationInp == 'n')
			{
				cout << endl << "Rule removal cancelled." << endl;
				cout << "Enter any input to return to the menu." << endl;
				cin >> choice;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				Menus();
			}

			dynamic_cast<Administrator*>(currentUser)->RemoveRule(selectedRule, *this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 5)
		{
			system("CLS");
			dynamic_cast<Administrator*>(currentUser)->ManageMemberData(*this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 6)
		{
			system("CLS");
			dynamic_cast<Administrator*>(currentUser)->ManageLibrarianData(*this);
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else if (choice == 7)
		{
			currentUser = nullptr;
			system("CLS");
			Menus();
		}
		else if (choice == 8)
		{
			system("CLS");
			currentUser->ChangePassword();
			cout << endl << "Enter any input to return to the menu." << endl;
			cin >> choice;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Menus();
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			Menus();
			}
	}

	delete currentUser;
	currentUser = nullptr;
}
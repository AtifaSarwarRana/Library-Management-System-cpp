#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    bool issued;
};
void addBook(Book books[], int &totalBooks);
void displayBooks(Book books[], int totalBooks);
void searchBook(Book books[], int totalBooks);
void issueBook(Book books[], int totalBooks);
void returnBook(Book books[], int totalBooks);
void deleteBook(Book books[], int &totalBooks);
void updateBook(Book books[], int totalBooks);

void saveBooks(Book books[], int totalBooks)
{
    cout << "\nsaveBooks() function called!\n";
   ofstream file("books.txt");

    for(int i = 0; i < totalBooks; i++)
    {
        file << books[i].id << endl;
        file << books[i].title << endl;
        file << books[i].author << endl;
        file << books[i].issued << endl;
    }

    file.close();
}
void loadBooks(Book books[], int &totalBooks)
{
    ifstream file("books.txt");

    if(!file)
    {
        return;
    }

    totalBooks = 0;

    while(file >> books[totalBooks].id)
    {
        file.ignore();

        getline(file, books[totalBooks].title);
        getline(file, books[totalBooks].author);

        file >> books[totalBooks].issued;
        file.ignore();

        totalBooks++;
    }

    file.close();
}

void addBook(Book books[], int &totalBooks)
{
    int newID;

    cout << "\nEnter Book ID: ";
    cin >> newID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == newID)
        {
            cout << "\nBook ID already exists!\n";
            return;
        }
    }

    books[totalBooks].id = newID;

    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, books[totalBooks].title);

    cout << "Enter Author Name: ";
    getline(cin, books[totalBooks].author);

    books[totalBooks].issued = false;

    totalBooks++;

    saveBooks(books, totalBooks);

    cout << "\nBook Added Successfully!\n";
}

void displayBooks(Book books[], int totalBooks)
{
    if(totalBooks == 0)
    {
        cout << "\nNo books available.\n";
    }
    else
    {
        cout << "\n========== BOOK RECORDS ==========\n";

        for(int i = 0; i < totalBooks; i++)
        {
            cout << "\nBook " << i + 1 << endl;
            cout << "ID     : " << books[i].id << endl;
            cout << "Title  : " << books[i].title << endl;
            cout << "Author : " << books[i].author << endl;

            cout << "Status : ";

            if(books[i].issued)
            {
                cout << "Issued" << endl;
            }
            else
            {
                cout << "Available" << endl;
            }
        }
    }
}
void searchBook(Book books[], int totalBooks)
{
    int searchID;
    bool found = false;

    cout << "\nEnter Book ID to Search: ";
    cin >> searchID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == searchID)
        {
            cout << "\n===== BOOK FOUND =====\n";
            cout << "ID     : " << books[i].id << endl;
            cout << "Title  : " << books[i].title << endl;
            cout << "Author : " << books[i].author << endl;

            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }
}
void issueBook(Book books[], int totalBooks)
{
    int bookID;
    bool found = false;

    cout << "\nEnter Book ID to Issue: ";
    cin >> bookID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == bookID)
        {
            found = true;

            if(books[i].issued)
            {
                cout << "\nBook is already issued.\n";
            }
            else
            {
                books[i].issued = true;

                saveBooks(books, totalBooks);

                cout << "\nBook issued successfully.\n";
            }

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook not found.\n";
    }
}
void returnBook(Book books[], int totalBooks)
{
    int bookID;
    bool found = false;

    cout << "\nEnter Book ID to Return: ";
    cin >> bookID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == bookID)
        {
            found = true;

            if(!books[i].issued)
            {
                cout << "\nBook is already available.\n";
            }
            else
            {
                books[i].issued = false;

                saveBooks(books, totalBooks);

                cout << "\nBook returned successfully.\n";
            }

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook not found.\n";
    }
}
void deleteBook(Book books[], int &totalBooks)
{
    int deleteID;
    bool found = false;

    cout << "\nEnter Book ID to Delete: ";
    cin >> deleteID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == deleteID)
        {
            found = true;

            for(int j = i; j < totalBooks - 1; j++)
            {
                books[j] = books[j + 1];
            }

            totalBooks--;

            saveBooks(books, totalBooks);

            cout << "\nBook Deleted Successfully!\n";

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }
}
void updateBook(Book books[], int totalBooks)
{
    int updateID;
    bool found = false;

    cout << "\nEnter Book ID to Update: ";
    cin >> updateID;

    cin.ignore();

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == updateID)
        {
            found = true;

            cout << "\nEnter New Title: ";
            getline(cin, books[i].title);

            cout << "Enter New Author: ";
            getline(cin, books[i].author);

            saveBooks(books, totalBooks);

            cout << "\nBook Updated Successfully!\n";

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }
}


int main()
{
    Book books[100];
    int totalBooks = 0;
    int choice;
    loadBooks(books, totalBooks);

    do
    {
        cout << "\n=================================";
        cout << "\n   LIBRARY MANAGEMENT SYSTEM";
        cout << "\n=================================";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Delete Book";
        cout << "\n7. Update Book";
        cout << "\n8. Exit";
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
        addBook(books, totalBooks);
        /*  cout << "\nEnter Book ID: ";
            cin >> books[totalBooks].id;

            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, books[totalBooks].title);

            cout << "Enter Author Name: ";
            getline(cin, books[totalBooks].author);
            books[totalBooks].issued = false;

            totalBooks++;
            saveBooks(books, totalBooks);
            cout << "\nBook Added Successfully!\n";*/
            break;

        case 2:
        displayBooks(books, totalBooks);
         /*  if(totalBooks == 0)
            {
                cout << "\nNo books available.\n";
            }
            else
            {
                cout << "\n========== BOOK RECORDS ==========\n";

                for(int i = 0; i < totalBooks; i++)
                {
                    cout << "\nBook " << i + 1 << endl;
                    cout << "ID     : " << books[i].id << endl;
                    cout << "Title  : " << books[i].title << endl;
                    cout << "Author : " << books[i].author << endl;
                    cout << "Status : ";

if(books[i].issued)
{
    cout << "Issued" << endl;
}
else
{
    cout << "Available" << endl;
}
                }
            } */
            break;

        case 3:
         searchBook(books, totalBooks);
    /*  {
    int searchID;
    bool found = false;

    cout << "\nEnter Book ID to Search: ";
    cin >> searchID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == searchID)
        {
            cout << "\n===== BOOK FOUND =====\n";
            cout << "ID     : " << books[i].id << endl;
            cout << "Title  : " << books[i].title << endl;
            cout << "Author : " << books[i].author << endl;

            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    } */

    break;
// }
        case 4:
        issueBook(books, totalBooks);
        /*{
    int bookID;
    bool found = false;

    cout << "\nEnter Book ID to Issue: ";
    cin >> bookID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == bookID)
        {
            found = true;

            if(books[i].issued)
            {
                cout << "\nBook is already issued.\n";
            }
            else
            {
                books[i].issued = true;
                cout << "\nBook issued successfully.\n";
            }

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook not found.\n";
    }

    break;
} */
        case 5:
        returnBook(books, totalBooks);
        /*{
    int bookID;
    bool found = false;

    cout << "\nEnter Book ID to Return: ";
    cin >> bookID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == bookID)
        {
            found = true;

            if(!books[i].issued)
            {
                cout << "\nBook is already available.\n";
            }
            else
            {
                books[i].issued = false;
                saveBooks(books, totalBooks);
                cout << "\nBook returned successfully.\n";
            }

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook not found.\n";
    }

    break;
} */
        case 6:
        deleteBook(books, totalBooks);
        /*
{
    int deleteID;
    bool found = false;

    cout << "\nEnter Book ID to Delete: ";
    cin >> deleteID;

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == deleteID)
        {
            found = true;

            for(int j = i; j < totalBooks - 1; j++)
            {
                books[j] = books[j + 1];
            }

            totalBooks--;

            saveBooks(books, totalBooks);

            cout << "\nBook Deleted Successfully!\n";

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }

    break;
} */
        case 7:
        updateBook(books, totalBooks);
        /*{
    int updateID;
    bool found = false;

    cout << "\nEnter Book ID to Update: ";
    cin >> updateID;

    cin.ignore();

    for(int i = 0; i < totalBooks; i++)
    {
        if(books[i].id == updateID)
        {
            found = true;

            cout << "\nEnter New Title: ";
            getline(cin, books[i].title);

            cout << "Enter New Author: ";
            getline(cin, books[i].author);

            saveBooks(books, totalBooks);

            cout << "\nBook Updated Successfully!\n";

            break;
        }
    }

    if(!found)
    {
        cout << "\nBook Not Found!\n";
    }

    break;
} */

        case 8:
            cout << "\nThank you for using the Library Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    }
    while(choice != 8);

    return 0;
}
#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;
const int MAX = 10;

struct User
{
    string userName;
    string borrowedBookName;
    string borrwedBookNames[MAX];
    int borrwedBookId[MAX];
    int borrwedBooksCount;
    int borrowedBookid;
    int userId;
    User()
    {
        userName = "";
        borrowedBookName = "";
        for (int i = 0; i < MAX; ++i)
        {
            borrwedBookNames[i] = "";
        }

        userId = 0;
        borrwedBooksCount = 0;
    }
};

struct library
{
    User users[MAX];
    int Userlen;

    int BookId[MAX];
    string BookName[MAX];
    int quantity[MAX];
    int borrowquantity[MAX] = {0};
    int Booklen;

    library()
    {
        Booklen = 0;
        Userlen = 0;
    }

    int LibraryMenu()
    {
        int choice = -1;
        while (choice == -1)
        {
            cout << "1) add book \n";
            cout << "2) search books by prefix \n";
            cout << "3) print who borrwed book by name \n";
            cout << "4) print library by id \n";
            cout << "5)  print library by name \n";
            cout << "6) add users \n";
            cout << "7) users borrow book \n";
            cout << "8) users return book \n";
            cout << "9) print users \n";
            cout << "10) Exit \n";

            cout << "Enter your menu choice [1 - 10] : ";
            cin >> choice;
            if (!(1 <= choice && choice <= 9))
            {
                cout << "valid choice . try again \n";
                choice = -1;
            }
        }
        return choice;
    }
    void addBook()
    {
        int id;
        string name;
        int quant;
        cout << "Enter book info : id , book name ,total quantity: ";
        cin >> id >> name >> quant;

        BookName[Booklen] = name;
        BookId[Booklen] = id;
        quantity[Booklen] = quant;
        Booklen++;
    }

    void SearchByPrefix()
    {
        string prefix;
        cout << "Enter book nama prefix : ";
        cin >> prefix;

        for (int i = 0; i < Booklen; i++)
        {
            bool trueBook = 0;
            string s = BookName[i];
            for (int i = 0; i < prefix.size(); i++)
            {
                if (s.size() < prefix.size())
                {
                    trueBook = 0;
                    break;
                }
                else if (s[i] != prefix[i])
                {
                    trueBook = 0;
                    break;
                }
                else if (s[i] == prefix[i])
                {
                    trueBook = 1;
                }
            }
            if (trueBook)
            {
                cout << BookName[i] << endl;
            }
            else
                cout << "No book with such prefix";
        }
    }
    void addUser()
    {
        string userName;
        int id;

        cout << "Enter User name & id :";
        cin >> userName >> id;

        users[Userlen].userName = userName;
        users[Userlen].userId = id;
        users[Userlen].borrowedBookName = "";

        Userlen++;
    }

    bool AddBookToUserBorrwedBooks(int userIdx, string bookName)
    {

        int bookCount = users[userIdx].borrwedBooksCount;
        if (bookCount == MAX - 1)
        {
            cout << "user reach the limet of borrwed books\n";
            return 0;
        }

        users[userIdx].borrwedBookNames[bookCount] = bookName; //[useridx] ya3ni elmkan bta3 "mo"  fe arr el borrowbooks[bc]
        users[userIdx].borrwedBooksCount++;
    }
    bool RemoveBookFromBorrwedBookList(string userName, string bookName)
    {
        int userIdx = GetUserIdxByUserName(userName);
        if (userIdx == -1)
        {
            cout << "this user not found\n";
            return 0;
        }
        int bookIdx = -1;
        for (int i = 0; i < users[userIdx].borrwedBooksCount; ++i)
        {
            if (users[userIdx].borrwedBookNames[i] == bookName)
            {
                bookIdx = i;
                break;
            }
        }
        if (bookIdx == -1)
        {
            cout << "book is not found\n";
            return 0;
        }

        users[userIdx].borrwedBookNames[bookIdx] = "";
        for (int i = bookIdx; i < users[userIdx].borrwedBooksCount - 1; ++i)
        {
            swap(users[userIdx].borrwedBookNames[i], users[userIdx].borrwedBookNames[i + 1]);
        }
        users[userIdx].borrwedBooksCount--;
        return 0;
    }
    /// @brief function that get idx of user in users array
    /// @param userName name of user
    /// @return if user is found it returns value greater than 0 otherwise return -1
    int GetUserIdxByUserName(string userName)
    {
        for (int i = 0; i < Userlen; ++i)
        {
            if (users[i].userName == userName)
            {
                return i;
            }
        }
        return -1;
    }
    void UserBorrowBook()
    {
        string userborrow;
        string bookborrow;
        cout << "Enter User and book name :";
        cin >> userborrow >> bookborrow;
        bool trueQuant = 0;
        int idsearch = 0;
        for (int i = 0; i < Booklen; ++i)
        {
            if (BookName[i] == bookborrow)
            {
                if (quantity[i] == 0)
                {
                    cout << "This book is unavailable\n";
                }
                else
                {
                    trueQuant = 1;
                    quantity[i]--;
                    borrowquantity[i]++;
                    idsearch = BookId[i];
                    break;
                }
            }
        }
        bool userIsFinded = 0;
        int userIdx = GetUserIdxByUserName(userborrow);
        if (userIdx != -1 && trueQuant)
        {
            if (AddBookToUserBorrwedBooks(userIdx, bookborrow))
            {
                cout << "Book Borrwed Successfully\n";
            }
            else
            {
                cout << "Book Borrwed failed\n";
            }
        }
    }
    void UserReturnBook()
    {
        string userName, bookName;
        cin >> userName >> bookName;
        RemoveBookFromBorrwedBookList(userName, bookName);
    }

    void PrintWhoBorrowdByName()
    {
        string book;
        cout << "Enter book name : ";
        cin >> book;

        for (int i = 0; i < Userlen; i++)
        {
            for (int j = 0; j < users[i].borrwedBooksCount; j++)
            {

                if (users[i].borrwedBookNames[j] == book)
                {
                    cout << users[i].userName << "\n";
                    break;
                }
                else
                    cout << "Book Not found\n";
                break;
            }
        }
    }
    void SortBooksById()
    {
        for (int i = 0; i < Booklen - 1; i++)
        {
            for (int j = i + 1; j < Booklen; j++)
            {
                if (BookId[j] < BookId[i])
                {
                    swap(BookId[j], BookId[i]);
                    swap(BookName[j], BookName[i]);
                    swap(quantity[j], quantity[i]);
                }
            }
        }
    }
    void SortBooksByName()
    {
        for (int i = 0; i < Booklen - 1; i++)
        {
            for (int j = i + 1; j < Booklen; j++)
            {
                if (BookName[j] < BookName[i])
                {
                    swap(BookName[j], BookName[i]);
                    swap(BookId[j], BookId[i]);
                    swap(quantity[j], quantity[i]);
                }
            }
        }
    }
    void PrintLibraryById()
    {
        SortBooksById();

        for (int i = 0; i < Booklen; i++)
        {
            cout << "ID = " << BookId[i] << " BookName = " << BookName[i] << " quantity = " << quantity[i] << " borrow = " << *(borrowquantity + i) << endl;
        }
    }
    void PrintLibraryByName()
    {
        SortBooksByName();

        for (int i = 0; i < Booklen; i++)
        {
            cout << "ID = " << BookId[i] << " BookName = " << BookName[i] << " quantity = " << quantity[i] << " borrow = " << *(borrowquantity + i) << endl;
        }
    }
    void PrintUsers()
    {
        for (int i = 0; i < Userlen; i++)
        {
            cout << "Username :" << users[i].userName << " ID : " << users[i].userId << " Borrowed Books { ";
            for (int j = 0; j < users[i].borrwedBooksCount; ++j)
            {
                cout << users[i].borrwedBookNames[j] << " ";
            }
            cout << "}\n";
        }
    }

    void LibrarySystem()
    {

        while (true)
        {
            int choice = LibraryMenu();

            if (choice == 1)
            {
                addBook();
            }
            else if (choice == 2)
            {
                SearchByPrefix();
            }
            else if (choice == 3)
            {
                PrintWhoBorrowdByName();
            }
            else if (choice == 4)
            {
                PrintLibraryById();
            }
            else if (choice == 5)
            {
                PrintLibraryByName();
            }
            else if (choice == 6)
            {
                addUser();
            }
            else if (choice == 7)
            {
                UserBorrowBook();
            }
            else if (choice == 8)
            {
                UserReturnBook();
            }
            else if (choice == 9)
            {
                PrintUsers();
            }

            else
                break;
        }
    }
};

int main()
{
    library newlibrary;
    newlibrary.LibrarySystem();

    return 0;
}

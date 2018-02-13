#include <iostream>
#include "addressbook.h"
#include <windows.h>
#include <conio.h>

using namespace std;


int main()
{
    UsersBook usersBook;
    RecipientsBook recipientsBook;
    char choice;

    while(true)
    {
        if(usersBook.getCurrentUserID() == 0)
        {
            system("cls");
            cout << "\tADDRESS BOOK" << endl;
            cout << "******************************" << endl;
            cout << "1. Login" << endl;
            cout << "2. Registration" << endl;
            cout << "3. Exit" << endl;

            choice = getch();
            cin.sync();
            switch(choice)
            {
            case '1':
                if(usersBook.login())
                {
                    recipientsBook.setUserID(usersBook.getCurrentUserID());
                    recipientsBook.loadingRecipientsFromFile();
                }
                break;
            case '2':
                usersBook.registration();
                break;
            case '3':
                recipientsBook.close();

            default:
                cout << "\n\tNo such option, please press 1-3";
                Sleep(2200);
                break;
            }
        }
        else
        {

            system("cls");
            cout << "\tADDRESS BOOK" << endl;
            cout << "******************************" << endl;
            cout << "1. Add a new recipient" << endl;
            cout << "2. Search by name" << endl;
            cout << "3. Search by surename" << endl;
            cout << "4. Show all recipients" << endl;
            cout << "5. Edit a recipient" << endl;
            cout << "6. Delete a recipient" << endl;
            cout << "7. Change a password" << endl;
            cout << "8. Log off" << endl;
            cout << "9. Exit" << endl;

            choice = getch();
            cin.sync();
            switch(choice)
            {
            case '1':
                recipientsBook.addNewRecipient();
                break;
            case '2':
                recipientsBook.searchByName();
                break;
            case '3':
                recipientsBook.searchBySurname();
                break;
            case '4':
                recipientsBook.showAllRecipients();
                break;
            case '5':
                recipientsBook.editRecipientsData();
                break;
            case '6':
                recipientsBook.recipientDeleting();
                break;
            case '7':
                usersBook.changePassword();
                break;
            case '8':
                if(usersBook.logOff()) recipientsBook.logOff();
                break;
            case '9':
                recipientsBook.close();
            default:
            {
                cout << "\n\tNo such option, please press 1-9";
                Sleep(2200);
                break;
            }
            }
        }
    }
    return 0;
}

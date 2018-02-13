#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include "addressbook.h"

User::User()
{
    ID = 0;
    name = "";
    password = "";
}
int User::getID()
{
    return ID;
}
string User::getName()
{
    return name;
}
string User::getPassword()
{
    return password;
}
void User::setID (int ID)
{
    this->ID = ID;
}
void User::setName(string name)
{
    this->name = name;
}
void User::setPassword(string password)
{
    this->password = password;
}

Recipient::Recipient()
{
    this->ID = 0;
    this->userID = 0;
    this->name = "";
    this->surname = "";
    this->address = "";
    this->telephone = "";
    this->email = "";
}
int Recipient::getID()
{
    return ID;
}
int Recipient::getUserID()
{
    return userID;
}
string Recipient::getName()
{
    return name;
}
string Recipient::getSurname()
{
    return surname;
}
string Recipient::getAddress()
{
    return address;
}
string Recipient::getTelephone()
{
    return telephone;
}
string Recipient::getEmail()
{
    return email;
}
void Recipient::setID(int ID)
{
    this->ID = ID;
}
void Recipient::setUserID(int userID)
{
    this->userID = userID;
}
void Recipient::setName(string name)
{
    this->name = name;
}
void Recipient::setSurname(string surname)
{
    this->surname = surname;
}
void Recipient::setAddress(string address)
{
    this->address = address;
}
void Recipient::setTelephone(string telephone)
{
    this->telephone = telephone;
}
void Recipient::setEmail(string email)
{
    this->email = email;
}

UsersBook::UsersBook()
{
    this->userFileName = "Users.txt";
    this->currentUserID = 0;
    this->loadingUsersFromFile();
}
bool UsersBook::login()
{
    system("cls");
    string username, password;
    bool loggedIn = false;
    cout << "Please enter your username: ";
    cin >> username;
    bool doesTheUsernameAlreadyExist = false;
    int numberOfUsers = users.size();
    int userPosition;

    for(int i = 0; i < numberOfUsers; i++)
    {
        if(username == users[i].getName())
        {
            doesTheUsernameAlreadyExist = true;
            userPosition = i;
            break;
        }
    }
    if(doesTheUsernameAlreadyExist)
    {
        for(int i = 2; i >= 0; i--)
        {
            cout << "Please enter the Password: ";
            cin >> password;
            if(password == users[userPosition].getPassword())
            {
                currentUserID = users[userPosition].getID();
                loggedIn = true;
                system("cls");
                cout << "\n\tLogin has completed successfully" << endl;
                cout << "\n\n\tWelcome " << username << " :)";
                break;
            }
            else cout << "Password is not valid (you have " << i << " attempts left)" << endl;
        }
    }
    else cout << "The username does not exist";
    Sleep(2200);
    return loggedIn;
}
void UsersBook::registration()
{
    system("cls");
    string username, password;
    bool doesTheUsernameAlreadyExist = false;

    cout << "Please enter your username: ";
    cin >> username;

    for(vector <User>::iterator itr = users.begin(), theEnd = users.end(); itr !=theEnd; ++itr)
    {
        if(itr->getName() == username)
        {
            doesTheUsernameAlreadyExist = true;
            break;
        }
    }
    if(doesTheUsernameAlreadyExist) cout << "Unfortunatly, the username already exists...";
    else
    {
        cout << "Set your password: ";
        cin >> password;
        userAdding(username, password);
        system("cls");
        cout << "\tRegistration was successful, you can log in now.";
        Sleep(1800);
    }
}
bool UsersBook::logOff()
{
    bool loggedOut = false;
    char choice;
    cout << "Are you sure to log off? Press 'y' to confirm";
    choice = getch();
    if(choice == 'y')
    {
        currentUserID = 0;
        loggedOut = true;
        cout << "\nYou have been logged out";
    }
    else cout << "\nYou have not been logged off";
    return loggedOut;
}
void UsersBook::changePassword()
{
    system("cls");
    string newPassword;
    cout << "Please enter a new password: ";
    cin >> newPassword;
    int numberOfUsers = users.size();

    for(int i = 0; i < numberOfUsers; i++)
        if(users[i].getID() == currentUserID)
        {
            users[i].setPassword(newPassword);
            break;
        }
    if(saveUserDataToFile())
        cout << endl << "\nPassword has been changed";
    Sleep(1800);
}
int UsersBook::getCurrentUserID()
{
    return currentUserID;
}
void UsersBook::loadingUsersFromFile()
{
    fstream file;
    string line;
    file.open(userFileName, ios::in);
    if(file.good())
    {
        while(getline(file, line))
        {
            users.push_back(loadingUserFromTheLine(line));
        }
        file.close();
    }
}
bool UsersBook::saveUserDataToFile()
{
    fstream file;
    bool saved = false;
    file.open(userFileName, ios::out);
    int numberOfUsers = users.size();
    if(file.good())
    {
        for(int i = 0; i < numberOfUsers; i++)
        {
            file << users[i].getID() << '|';
            file << users[i].getName() << '|';
            file << users[i].getPassword() << '|' << endl;
        }
        file.close();
        saved = true;
    }
    return saved;
}
User UsersBook::loadingUserFromTheLine(string line)
{
    User user;
    string partOfLine = "";
    int lineLength = line.length();
    int wordNumber = 0;

    for(int i = 0; i < lineLength; i++)
        if (line[i] != '|') partOfLine += line[i];
        else
        {
            wordNumber++;
            switch (wordNumber)
            {
            case 1:
                user.setID(atoi(partOfLine.c_str()));
                break;
            case 2:
                user.setName(partOfLine);
                break;
            case 3:
                user.setPassword(partOfLine);
                break;
            }
            partOfLine = "";
        }
    return user;
}
void UsersBook::userAdding(string name, string password)
{
    User newUser;
    if(users.empty())
        newUser.setID(1);
    else newUser.setID(users.back().getID() + 1);
    newUser.setName(name);
    newUser.setPassword(password);
    users.push_back(newUser);
    addingUserDataToFile(newUser);
}
void UsersBook::addingUserDataToFile(User &newUser)
{
    fstream file;
    file.open(userFileName, ios::out | ios::app);

    if(file.good())
    {
        file << newUser.getID() << '|';
        file << newUser.getName() << '|';
        file << newUser.getPassword() << '|' << endl;
        file.close();
    }
}

RecipientsBook::RecipientsBook()
{
    this->recipientFileName = "Recipients.txt";
    this->largestIDInFile = 0;
    this->userID = 0;
}
void RecipientsBook::setUserID(int userID)
{
    this->userID = userID;
}
void RecipientsBook::logOff()
{
    recipients.clear();
    userID = 0;
}
void RecipientsBook::loadingRecipientsFromFile()
{
    fstream file;
    string line;
    file.open(recipientFileName, ios::in);

    if(file.good())
    {
        while(getline(file, line))
            if(isIDCompatible(line))
                recipients.push_back(loadingRecipientFromLine(line));
        file.close();
    }
}
void RecipientsBook::addNewRecipient()
{
    Recipient newRecipient;
    string name, surname, address, email, telephone;
    system("cls");
    cout << "\tNew Recipient" << endl;
    cout << "******************************" << endl;
    cout << "Please enter new recipients name: ";
    cin.sync();
    getline(cin, name);
    newRecipient.setName(swapFirstLettersEachWordToLargeAndRestSwapToLowercase(name));
    cout << "Please enter new recipients surname: ";
    cin.sync();
    getline(cin, surname);
    newRecipient.setSurname(swapFirstLettersEachWordToLargeAndRestSwapToLowercase(surname));
    cout << "Please enter new recipients telephone: ";
    cin.sync();
    getline(cin, telephone);
    newRecipient.setTelephone(telephone);
    cout << "Please enter new recipients email: ";
    cin.sync();
    getline(cin, email);
    newRecipient.setEmail(email);
    cout << "Please enter new recipients address: ";
    cin.sync();
    getline(cin, address);
    newRecipient.setAddress(address);
    newRecipient.setID(++largestIDInFile);
    newRecipient.setUserID(userID);
    recipients.push_back(newRecipient);
    addingRecipientToFile(newRecipient);
    cout << "\nRecipient has been added to contacts" << endl;
    Sleep(1000);
}
void RecipientsBook::searchByName()
{
    string name;
    system("cls");
    bool found = false;
    cout << "Please enter recipients name: " << endl;
    cin >> name;
    name = swapFirstLetterToLargeAndRestToLowercase(name);
    system("cls");
    int numberOfRecipients = recipients.size();
    for(int i = 0, numeration = 1; i < numberOfRecipients; i++)
    {
        if(recipients[i].getName().find(name) != string::npos)
        {
            cout << numeration << ". " << recipients[i].getName() << " " << recipients[i].getSurname()
                 << " ( ID = " << recipients[i].getID() << " )" << endl;
            cout << "   Telephone: " << recipients[i].getTelephone() << endl;
            cout << "   Email: " << recipients[i].getEmail() << endl;
            cout << "   " << recipients[i].getAddress() << endl<< endl;
            found = true;
            numeration++;
        }
    }
    if (found == false) cout << "There is no recipient's name matches" << endl << endl;
    cout << "Press any key to return to the main menu";
    getch();
}
void RecipientsBook::searchBySurname()
{

    string surname;
    system("cls");
    bool found = false;
    cout << "Please enter the recipient's surname: " << endl;
    cin >> surname;
    surname = swapFirstLetterToLargeAndRestToLowercase(surname);
    system("cls");
    int numberOfRecipients = recipients.size();

    for(int i = 0, numeration = 1; i < numberOfRecipients; i++)
    {
        if(recipients[i].getSurname().find(surname) != string::npos)
        {
            cout << numeration << ". " << recipients[i].getName() << " " << recipients[i].getSurname()
                 << " ( ID = " << recipients[i].getID() << " )" << endl;
            cout << "   Telephone: " << recipients[i].getTelephone() << endl;
            cout << "   Email: " << recipients[i].getEmail() << endl;
            cout << "   " << recipients[i].getAddress() << endl<< endl;
            found = true;
            numeration++;
        }
    }
    if (found == false) cout << "\tThere is no recipient's surname matches" << endl << endl;
    cout << "Press any key to return to the main menu";
    getch();
}
void RecipientsBook::showAllRecipients()
{
    system("cls");
    cout << "\tAll contacts" << endl;
    cout << "******************************" << endl;
    int numberOfRecipients = recipients.size();
    if(numberOfRecipients == 0)
        cout << "No recipients to show" << endl << endl;
    else
    {
        for(int i = 0; i < numberOfRecipients; i++)
        {
            cout << i+1 << ". " << recipients[i].getName() << " " << recipients[i].getSurname() << " ( ID = " << recipients[i].getID() << " )" << endl;
            cout << "   Telephone: " << recipients[i].getTelephone()<< endl;
            cout << "   Email: " << recipients[i].getEmail() << endl;
            cout << "   Address: " << recipients[i].getAddress() << endl <<endl;
        }
    }
    cout<<"Press any key to get back to the main menu";
    getch();
}
void RecipientsBook::editRecipientsData()
{
    string recipientsLineBeforeEdition, recipientsLineAfterEdition, newData = "";
    int IDNumber;
    bool found = false;
    bool changed = false;
    char choice;
    system("cls");
    cout << "Please enter recipient's ID whose data you'd like to edit: ";
    cin >> IDNumber;
    vector <Recipient>::iterator itr, theEnd = recipients.end();
    for(itr = recipients.begin(); itr != theEnd; ++itr )
        if (itr->getID() == IDNumber)
        {
            found = true;
            recipientsLineBeforeEdition = returnRecipientsDataLine(itr);
            while(choice != '6')
            {
                system ("cls");
                cout << "The recipient edition:" << endl;
                cout << "   " << itr->getName() << " " << itr->getSurname() << " ( ID = " << itr->getID() << " )" << endl;
                cout << "   " << itr->getAddress() << endl;
                cout << "   Telephone: " << itr->getTelephone() << endl;
                cout << "   Email: " << itr->getEmail() << endl << endl;
                cout << "What data you want to edit? " << endl;
                cout << "1. Name\n2. Surname\n3. Telephone\n4. Email" << endl;
                cout << "5. Address\n6. Return to the main menu\n\nPlease press 1-6: " << endl;
                choice = getch();
                switch(choice)
                {
                case '1':
                    cout << "\nPlease enter a new name: ";
                    cin.sync();
                    getline(cin, newData);
                    itr->setName(swapFirstLettersEachWordToLargeAndRestSwapToLowercase(newData));
                    changed = true;
                    break;
                case '2':
                    cout << "\nPlease enter a new surname: ";
                    cin.sync();
                    getline(cin, newData);
                    itr->setSurname(swapFirstLettersEachWordToLargeAndRestSwapToLowercase(newData));
                    changed = true;
                    break;
                case '3':
                    cout << "\nPlease enter new Telephone: ";
                    cin.sync();
                    getline(cin, newData);
                    itr->setTelephone(newData);
                    changed = true;
                    break;
                case '4':
                    cout << "\nPlease enter address e-mail: ";
                    cin.sync();
                    getline(cin, newData);
                    itr->setEmail(newData);
                    changed = true;
                    break;
                case '5':
                    cout << "\nPlease enter new adres: ";
                    cin.sync();
                    getline(cin, newData);
                    itr->setAddress(newData);
                    changed = true;
                    break;
                case '6':
                    break;
                default :
                    cout << "\nThere's no such option. Press the 1-6 key";
                    Sleep(1800);
                    break;
                }
            }
            break;
        }
    if(!found) cout << "\nNo recipients ID matches" << endl;
    else if (changed)
    {
        recipientsLineAfterEdition = returnRecipientsDataLine(itr);
        if(editRecipientsDataInFile(recipientsLineBeforeEdition, recipientsLineAfterEdition))
            cout << "\nThe data has been changed successfully...";
    }
    else cout << "\nReturning to the main menu without any changes...";
    Sleep(1500);
}
void RecipientsBook::recipientDeleting()
{
    system("cls");
    int IDNumber;
    bool found = false;
    char choice;
    string recipientsDataLine;
    cout << "Please enter recipient's ID whose data you'd like to delete: ";
    cin >> IDNumber;
    vector <Recipient>::iterator itr, theEnd = recipients.end();
    for(itr = recipients.begin(); itr != theEnd; ++itr )
        if (itr->getID() == IDNumber)
        {
            found = true;
            break;
        }
    if(!found) cout << "No recipients ID matches, we return to the main menu";
    else
    {
        cout << "Are you sure to delete the recipient? Press 'y' to confirm: ";
        cin >> choice;
        if(choice == 'y')
        {
            recipientsDataLine = returnRecipientsDataLine(itr);
            recipients.erase(itr);
            if(deleteRecipientFromFile(recipientsDataLine))
                cout << "Recipient has been deleted";
            else
                cout << "Recipient may not have been successfully removed from the file";
            if(IDNumber == largestIDInFile)
                largestIDInFile = findTheLargestIDInFile();
        }
        else cout << "Returning to the main menu with no deleting";
    }
    Sleep(2000);
}
void RecipientsBook::close()
{
    system("cls");
    cout << "\tGood Bye" << endl;
    cout << "*****************************";
    Sleep(1000);
    exit(0);
}
void RecipientsBook::addingRecipientToFile(Recipient &recipient)
{
    fstream file;
    file.open(recipientFileName, ios::out | ios::app);

    if(file.good())
    {
        file << recipient.getID() << "|";
        file << recipient.getUserID() << "|";
        file << recipient.getName() << "|";
        file << recipient.getSurname() << "|";
        file << recipient.getTelephone() << "|";
        file << recipient.getEmail() << "|";
        file << recipient.getAddress() << "|" << endl;
    }
    file.close();
}
bool RecipientsBook::editRecipientsDataInFile(string dataLineBeforeEdition, string dataLineAfterEdition)
{
    bool isRecipientEdited = false;
    fstream file, tempFile;
    string tempLine = "";

    file.open(recipientFileName, ios::in);
    tempFile.open("temp.temp", ios::out);

    if(file.good() && tempFile.good())
    {
        while(getline(file, tempLine))
        {
            if(dataLineBeforeEdition != tempLine)
                tempFile << tempLine << endl;
            else
                tempFile << dataLineAfterEdition << endl;
        }
        file.close();
        tempFile.close();
        isRecipientEdited = true;
    }
    if (remove(recipientFileName) || rename("temp.temp", recipientFileName))
        isRecipientEdited = false;
    return isRecipientEdited;
}
bool RecipientsBook::deleteRecipientFromFile(string dataLineForDelete)
{
    bool isRecipientRemovedFromFile = false;
    fstream file, tempFile;
    string tempLine = "";

    file.open(recipientFileName, ios::in);
    tempFile.open("temp.temp", ios::out);

    if(file.good() && tempFile.good())
    {
        while(getline(file, tempLine))
        {
            if(dataLineForDelete != tempLine)
                tempFile << tempLine << endl;
        }
        file.close();
        tempFile.close();
        isRecipientRemovedFromFile = true;
    }
    if (remove(recipientFileName) || rename("temp.temp", recipientFileName))
        isRecipientRemovedFromFile = false;
    return isRecipientRemovedFromFile;
}
string RecipientsBook::returnRecipientsDataLine(vector <Recipient>::iterator itr)
{
    string line = "";
    line = IntToString(itr->getID()) + "|" + IntToString(itr->getUserID()) + "|" + itr->getName() + "|"
            + itr->getSurname() + "|" + itr->getTelephone() + "|" + itr->getEmail() + "|" + itr->getAddress() + "|";
    return line;
}
int RecipientsBook::findTheLargestIDInFile()
{
    fstream file;
    string line = "";
    string IDInLine = "";
    int largestIDValueInFile = 0;
    file.open(recipientFileName, ios::in);
    if(file.good())
    {
        while(getline(file, line))
        {
            IDInLine = line.substr(0,line.find('|'));
            largestIDValueInFile = atoi(IDInLine.c_str());
        }
        file.close();
    }
    return largestIDValueInFile;
}
string RecipientsBook::IntToString(int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}
string RecipientsBook::swapFirstLetterToLargeAndRestToLowercase(string text)
{
    if (!text.empty())
    {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        text[0] = toupper(text[0]);
    }
    return text;
}
string RecipientsBook::swapFirstLettersEachWordToLargeAndRestSwapToLowercase(string text)
{
    int textLength = text.length();
    string word = "";
    string EachWordBeginsFromLargeLetterText = "";

    for(int i = 0; i < textLength; i++)
    {
        if(text[i] != ' ') word += text[i];
        else
        {
            EachWordBeginsFromLargeLetterText += swapFirstLetterToLargeAndRestToLowercase(word) + " ";
            word = "";
        }
    }
    EachWordBeginsFromLargeLetterText += swapFirstLetterToLargeAndRestToLowercase(word);
    return EachWordBeginsFromLargeLetterText;
}
Recipient RecipientsBook::loadingRecipientFromLine(string line)
{
    Recipient recipient;
    string partOfLine = "";
    int lineLength = line.length();
    int wordNumber = 0;

    for(int i = 0; i < lineLength; i++)
        if (line[i] != '|') partOfLine += line[i];
        else
        {
            wordNumber++;
            switch (wordNumber)
            {
            case 1:
                recipient.setID(atoi(partOfLine.c_str()));
                break;
            case 2:
                recipient.setUserID(atoi(partOfLine.c_str()));
                break;
            case 3:
                recipient.setName(partOfLine);
                break;
            case 4:
                recipient.setSurname(partOfLine);
                break;
            case 5:
                recipient.setTelephone(partOfLine);
                break;
            case 6:
                recipient.setEmail(partOfLine);
                break;
            case 7:
                recipient.setAddress(partOfLine);
                break;
            }
            partOfLine = "";
        }
    return recipient;
}
bool RecipientsBook::isIDCompatible(string line)
{
    string userIDInLine = "";
    string recipientIDInLine = "";
    bool compatibility = false;
    int presentSignPositionInLine = 0;
    while(true)
    {
        recipientIDInLine += line[presentSignPositionInLine];
        presentSignPositionInLine++;
        if(line[presentSignPositionInLine] == '|')
        {
            presentSignPositionInLine++;
            do
            {
                userIDInLine += line[presentSignPositionInLine++];
            }
            while(line[presentSignPositionInLine] != '|');
            if(userID == atoi(userIDInLine.c_str())) compatibility = true;
            break;
        }
    }
    largestIDInFile = atoi(recipientIDInLine.c_str());
    return compatibility;
}

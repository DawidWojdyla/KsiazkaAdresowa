#include <iostream>
#include <vector>

using namespace std;

class User
{
    int ID;
    string name, password;
public:
    User ();
    int getID();
    string getName();
    string getPassword();
    void setID (int ID);
    void setName(string name);
    void setPassword(string password);
};

class Recipient
{
    int ID, userID;
    string name, surname, address, telephone, email;
public:
    Recipient();
    int getID();
    int getUserID();
    string getName();
    string getSurname();
    string getAddress();
    string getTelephone();
    string getEmail();
    void setID(int ID);
    void setUserID(int userID);
    void setName(string name);
    void setSurname(string surname);
    void setAddress(string address);
    void setTelephone(string telephone);
    void setEmail(string email);
};

class UsersBook
{
    vector <User> users;
    char * userFileName;
    int currentUserID;
public:
    UsersBook();
    bool login();
    void registration();
    bool logOff();
    void changePassword();
    int getCurrentUserID();
private:
    void loadingUsersFromFile();
    bool saveUserDataToFile();
    User loadingUserFromTheLine(string linia);
    void userAdding(string nazwa, string haslo);
    void addingUserDataToFile(User &newUser);
};

class RecipientsBook
{
    vector <Recipient> recipients;
    char * recipientFileName;
    int largestIDInFile;
    int userID;
public:
    RecipientsBook();
    void setUserID(int userID);
    void logOff();
    void loadingRecipientsFromFile();
    void addNewRecipient();
    void searchByName();
    void searchBySurname();
    void showAllRecipients();
    void editRecipientsData();
    void recipientDeleting();
    void close();
private:
    void addingRecipientToFile(Recipient &recipient);
    bool editRecipientsDataInFile(string dataLineBeforeEdition, string dataLineAfterEdition);
    bool deleteRecipientFromFile(string dataLineForDelete);
    string returnRecipientsDataLine(vector <Recipient>::iterator itr);
    int findTheLargestIDInFile();
    string IntToString(int number);
    string swapFirstLetterToLargeAndRestToLowercase(string text);
    string swapFirstLettersEachWordToLargeAndRestSwapToLowercase(string text);
    Recipient loadingRecipientFromLine(string line);
    bool isIDCompatible(string line);
};

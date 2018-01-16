#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct Osoba {
    int id;
    string imie, nazwisko, adres, numerTelefonu, adresEmail;
};
vector <Osoba> osoby (1);

void wczytywanieOsobyZLinii(string linia, int indexOsoby) {
    string skladowaLinii = "";
    int dlugoscLinii = linia.length();
    int numerWyrazu = 0;

    for(int i = 0; i < dlugoscLinii; i++)
        if (linia[i] != '|') skladowaLinii += linia[i];
        else {
            numerWyrazu++;
            switch (numerWyrazu) {

            case 1:
                osoby[indexOsoby].id            = atoi(skladowaLinii.c_str());
                break;
            case 2:
                osoby[indexOsoby].imie          = skladowaLinii;
                break;
            case 3:
                osoby[indexOsoby].nazwisko      = skladowaLinii;
                break;
            case 4:
                osoby[indexOsoby].numerTelefonu = skladowaLinii;
                break;
            case 5:
                osoby[indexOsoby].adresEmail    = skladowaLinii;
                break;
            case 6:
                osoby[indexOsoby].adres         = skladowaLinii;
                break;
            }
            skladowaLinii = "";
        }
}
int wczytywanieKontaktowZPliku(int iloscOsob) {
    fstream plik;
    string linia;

    plik.open("ksiazka_adresowa.txt", ios::in);

    if(plik.good()) {
        while(getline(plik, linia)) {
            wczytywanieOsobyZLinii(linia, iloscOsob);
            iloscOsob++;
            osoby.push_back(Osoba());
        }
        plik.close();
        return iloscOsob;
    } else return 0;
}

void zapisywanieKontaktowDoPliku(int iloscOsob) {

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out);

    if(plik.good()) {
        for(int i = 0; i < iloscOsob; i++) {

            plik << osoby[i].id << "|";
            plik << osoby[i].imie << "|";
            plik << osoby[i].nazwisko << "|";
            plik << osoby[i].numerTelefonu << "|";
            plik << osoby[i].adresEmail << "|";
            plik << osoby[i].adres << "|" << endl;
        }
    }
    plik.close();
}

int dodajOsobeDoKontaktow(int iloscOsob) {

    string imie, nazwisko, adres, adresEmail, numerTelefonu;

    system("cls");
    cout << "\tNOWA OSOBA" << endl;
    cout << "******************************" << endl;
    cout << "Podaj imie: ";
    cin.sync();
    getline(cin, imie);
    cout << "Podaj nazwisko: ";
    cin.sync();
    getline(cin, nazwisko);
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj adres e-mail: ";
    cin.sync();
    getline(cin, adresEmail);
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adres);

    osoby.push_back(Osoba());
    osoby[iloscOsob].imie          = imie;
    osoby[iloscOsob].nazwisko      = nazwisko;
    osoby[iloscOsob].adres         = adres;
    osoby[iloscOsob].numerTelefonu = numerTelefonu;
    osoby[iloscOsob].adresEmail    = adresEmail;
    if(iloscOsob>0)
        osoby[iloscOsob].id            = (osoby[iloscOsob-1].id+1);
    else osoby[iloscOsob].id       = iloscOsob+1;

    zapisywanieKontaktowDoPliku(iloscOsob+1);
    cout << "\nOsoba dodana do kontaktow" << endl;
    Sleep(900);
    return iloscOsob+1;
}

void wyszukajPoImieniu(int iloscOsob) {
    string imie;
    system("cls");
    bool znaleziono = false;
    cout << "Podaj imie szukanej osoby: ";
    cin >> imie;
    system("cls");

    for(int i = 0, numeracja = 1; i < iloscOsob; i++) {
        if(osoby[i].imie == imie) {
            cout << numeracja << ". " << osoby[i].imie << " " << osoby[i].nazwisko << " ( ID = " << osoby[i].id << " )" << endl;
            cout << "   Numer telefonu: " << osoby[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << osoby[i].adresEmail << endl;
            cout << "   " << osoby[i].adres << endl<< endl;
            znaleziono = true;
            numeracja++;
        }
    }
    if (znaleziono == false) cout << "Brak osob o takim imieniu" << endl << endl;
    cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

void wyszukajPoNazwisku(int iloscOsob) {

    string nazwisko;
    system("cls");
    bool znaleziono = false;
    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> nazwisko;
    system("cls");

    for(int i = 0, numeracja = 1; i < iloscOsob; i++) {
        if(osoby[i].nazwisko == nazwisko) {
            cout << numeracja << ". " << osoby[i].imie << " " << osoby[i].nazwisko << " ( ID = " << osoby[i].id << " )" << endl;
            cout << "   Numer telefonu: " << osoby[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << osoby[i].adresEmail << endl;
            cout << "   " << osoby[i].adres << endl<< endl;
            znaleziono = true;
            numeracja++;
        }
    }
    if (znaleziono == false) cout << "\tBrak osob o takim nazwisku" << endl << endl;
    cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

void wyswietlWszystkieKontakty(int iloscOsob) {

    system("cls");
    cout << "\tWSZYSTKIE KONTAKTY" << endl;
    cout << "******************************" << endl;
    if(iloscOsob == 0)
        cout << "Brak kontaktow do wyswietlenia" << endl << endl;
    else {
        for(int i = 0; i < iloscOsob; i++) {
            cout << i+1 << ". " << osoby[i].imie << " " << osoby[i].nazwisko << " ( ID = " << osoby[i].id << " )" << endl;
            cout << "   " << osoby[i].adres << endl;
            cout << "   Numer telefonu: " << osoby[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << osoby[i].adresEmail << endl << endl;
        }
    }
    cout<<"Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}
void edytujKontakt(int iloscOsob) {
    system("cls");
    int numerID;
    bool czyZnaleziono = false;
    bool czyZmieniono = false;
    char wybor;
    cout << "Podaj numer ID osoby, ktorej dane chcesz edytowac: ";
    cin >> numerID;

    for(int i = 0; i < iloscOsob; i++) {
        if(numerID == osoby[i].id) {
            czyZnaleziono = true;
            while (true) {
                system ("cls");
                cout << "Edytujesz kontakt:" << endl;
                cout << "   " << osoby[i].imie << " " << osoby[i].nazwisko << " ( ID = " << osoby[i].id << " )" << endl;
                cout << "   " << osoby[i].adres << endl;
                cout << "   Numer telefonu: " << osoby[i].numerTelefonu << endl;
                cout << "   Adres e-mail: " << osoby[i].adresEmail << endl << endl;
                cout << "Co chcesz zmienic? " << endl;
                cout << "1. Imie\n2. Nazwisko\n3. Numer telefonu\n4. Adres e-mail\n5. Adres zamieszkania\n6. Powrot do menu\n\nWcisnij klawisz 1-6: ";
                cin >> wybor;
                if(wybor == '1') {
                    cout << "Podaj imie: ";
                    cin.sync();
                    getline(cin, osoby[i].imie);
                    czyZmieniono = true;
                } else if(wybor == '2') {
                    cout << "Podaj nazwisko: ";
                    cin.sync();
                    getline(cin, osoby[i].nazwisko);
                    czyZmieniono = true;
                } else if(wybor == '3') {
                    cout << "Podaj numer telefonu: ";
                    cin.sync();
                    getline(cin, osoby[i].numerTelefonu);
                    czyZmieniono = true;
                } else if(wybor == '4') {
                    cout << "Podaj adres e-mail: ";
                    cin.sync();
                    getline(cin, osoby[i].adresEmail);
                    czyZmieniono = true;
                } else if(wybor == '5') {
                    cout << "Podaj adres: ";
                    cin.sync();
                    getline(cin, osoby[i].adres);
                    czyZmieniono = true;
                } else if(wybor == '6') break;
            }
        }
        if(czyZnaleziono) break;
    }
    if(!czyZnaleziono) cout << "\nBrak osob o podanym ID";
    else if (czyZmieniono) {
        cout << "\nPomyslnie zmieniono dane";
        zapisywanieKontaktowDoPliku(iloscOsob);
    } else cout << "\nWracamy do menu glownego";

    Sleep(1500);
}

int usunKontakt(int iloscOsob) {

    system("cls");
    int numerID;
    bool czyZnaleziono = false;
    char wybor;
    cout << "Podaj numer ID osoby, ktorej dane chcesz usunac z kontaktow: ";
    cin >> numerID;

    for(int i = 0; i < iloscOsob; i++)
        if (osoby[i].id == numerID) czyZnaleziono = true;

    if(!czyZnaleziono) cout << "Brak osob o podanym ID...";
    else {
        cout << "Jezeli na pewno chcesz usunac kontakt o numerze ID = " << numerID <<" wcisnij 't': ";
        cin >> wybor;
        if(wybor == 't') {
            fstream plik;
            plik.open("ksiazka_adresowa.txt", ios::out);
            if(plik.good()) {
                for(int i = 0; i < iloscOsob; i++) {
                    if(osoby[i].id != numerID) {
                        plik << osoby[i].id << "|";
                        plik << osoby[i].imie << "|";
                        plik << osoby[i].nazwisko << "|";
                        plik << osoby[i].numerTelefonu << "|";
                        plik << osoby[i].adresEmail << "|";
                        plik << osoby[i].adres << "|" << endl;
                    }
                }
            }
            plik.close();
            osoby = vector <Osoba> (1);
            iloscOsob = wczytywanieKontaktowZPliku(0);
            cout << "Osoba zostala usunieta...";
        } else cout << "Wracamy do menu glownego bez usuwania kontaktu...";
    }
    Sleep(2200);
    return iloscOsob;
}

int main() {

    int iloscOsob = 0;
    char wybor;

    iloscOsob = wczytywanieKontaktowZPliku(iloscOsob);

    while(1) {
        system("cls");
        cout << "\tKSIAZKA ADRESOWA" << endl;
        cout << "******************************" << endl;
        cout << "1. Dodaj nowy kontakt" << endl;
        cout << "2. Wyszukaj kontakt" << endl;
        cout << "3. Wyswietl wszystkie kontakty" << endl;
        cout << "4. Edytuj kontakt" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "9. Zakoncz" << endl;
        //cout << "Wielkosc wektora: " << osoby.size() << endl;

        cin >> wybor;

        if(wybor == '1')
            iloscOsob = dodajOsobeDoKontaktow(iloscOsob);
        else if(wybor == '2') {
            system("cls");
            cout << "\tWYSZUKIWANIE" << endl;
            cout << "******************************" << endl;
            cout << "1. Wyszukaj po imieniu" << endl;
            cout << "2. Wyszukaj po nazwisku" << endl;
            cin >> wybor;
            if(wybor == '1')
                wyszukajPoImieniu(iloscOsob);
            else if(wybor == '2')
                wyszukajPoNazwisku(iloscOsob);
        }
        else if (wybor == '3')
            wyswietlWszystkieKontakty(iloscOsob);
        else if (wybor == '4')
            edytujKontakt(iloscOsob);
        else if (wybor == '5')
            iloscOsob = usunKontakt(iloscOsob);
        else if(wybor == '9') {
            system("cls");
            cout << "\tDOWIDZENIA" << endl;
            cout << "*****************************";
            Sleep(1000);
            exit(0);
        }
    }
    return 0;
}

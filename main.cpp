#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct Osoba {
    int id;
    string imie, nazwisko, adres, numerTelefonu, adresEmail;
};

int wczytywanieKontaktowZPliku(Osoba osoby [], int iloscOsob) {
    fstream plik;
    string linia;
    int nr_linii = 1;

    plik.open("ksiazka_adresowa.txt", ios::in);

    if(plik.good()) {
        while(getline(plik, linia)) {
            switch(nr_linii) {
            case 1:
                osoby[iloscOsob].id            = iloscOsob+1;
                osoby[iloscOsob].imie          = linia;
                break;
            case 2:
                osoby[iloscOsob].nazwisko      = linia;
                break;
            case 3:
                osoby[iloscOsob].adres         = linia;
                break;
            case 4:
                osoby[iloscOsob].numerTelefonu = linia;
                break;
            case 5:
                osoby[iloscOsob].adresEmail    = linia;
                break;
            }
            if(nr_linii == 5) {
                nr_linii = 0;
                iloscOsob++;
            }
            nr_linii++;
        }
        plik.close();
        return iloscOsob;
    } else return 0;
}

void zapisywanieKontaktowDoPliku(Osoba osoby [], int iloscOsob) {

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out);

    if(plik.good()) {
        for(int i=0; i<iloscOsob; i++) {
            plik << osoby[i].imie << endl;
            plik << osoby[i].nazwisko << endl;
            plik << osoby[i].adres << endl;
            plik << osoby[i].numerTelefonu << endl;
            plik << osoby[i].adresEmail << endl;
        }
    }
    plik.close();
}

int dodajOsobeDoKontaktow(Osoba osoby [], int iloscOsob) {

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
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adres);
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj adres e-mail: ";
    cin.sync();
    getline(cin, adresEmail);

    osoby[iloscOsob].imie          = imie;
    osoby[iloscOsob].nazwisko      = nazwisko;
    osoby[iloscOsob].adres         = adres;
    osoby[iloscOsob].numerTelefonu = numerTelefonu;
    osoby[iloscOsob].adresEmail    = adresEmail;
    osoby[iloscOsob].id            = iloscOsob+1;

    cout << "\nOsoba dodana do kontaktow" << endl;
    Sleep(900);
    return iloscOsob+1;
}

void wyszukajPoImieniu(Osoba osoby [], int iloscOsob) {

    string imie;
    system("cls");
    bool znaleziono = false;
    cout << "Podaj imie szukanej osoby: ";
    cin >> imie;
    system("cls");

    for(int i = 0, numeracja = 1; i < iloscOsob; i++) {
        if(osoby[i].imie == imie) {
            cout << numeracja << ". " << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "   " << osoby[i].adres << endl;
            cout << "   Numer telefonu: " << osoby[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << osoby[i].adresEmail << endl << endl;
            znaleziono = true;
            numeracja++;
        }
    }
    if (znaleziono == false) cout << "Brak osob o takim imieniu" << endl << endl;
    cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

void wyszukajPoNazwisku(Osoba osoby [], int iloscOsob) {

    string nazwisko;
    system("cls");
    bool znaleziono = false;
    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> nazwisko;
    system("cls");

    for(int i = 0; i < iloscOsob; i++) {
        if(osoby[i].nazwisko == nazwisko) {
            cout << i+1 << ". " << osoby[i].imie << " " << osoby[i].nazwisko<<endl;
            cout << "   " << osoby[i].adres << endl;
            cout << "   Numer telefonu: " << osoby[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << osoby[i].adresEmail << endl << endl;
            znaleziono = true;
        }
    }
    if (znaleziono == false) cout << "\tBrak osob o takim nazwisku" << endl << endl;
    cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

wyswietlWszystkieKontakty(Osoba osoby [], int iloscOsob) {

    system("cls");
    cout << "\tWSZYSTKIE KONTAKTY" << endl;
    cout << "******************************" << endl;
    if(iloscOsob == 0)
        cout << "Brak kontaktow do wyswietlenia" << endl << endl;
    else {
        for(int i = 0; i < iloscOsob; i++) {
            cout << osoby[i].id << ". " << osoby[i].imie << " " << osoby[i].nazwisko << endl;
            cout << "   " << osoby[i].adres << endl;
            cout << "   Numer telefonu: " << osoby[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << osoby[i].adresEmail << endl << endl;
        }
    }
    cout<<"Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

int main() {

    Osoba osoby[1000];
    int iloscOsob = 0;
    char wybor;

    iloscOsob = wczytywanieKontaktowZPliku(osoby, iloscOsob);

    while(1) {
        system("cls");
        cout << "\tKSIAZKA ADRESOWA" << endl;
        cout << "******************************" << endl;
        cout << "1. Dodaj nowa osobe" << endl;
        cout << "2. Wyszukaj osobe" << endl;
        cout << "3. Wyswietl wszystkie kontakty" << endl;
        cout << "9. Zakoncz" << endl;

        cin >> wybor;

        if(wybor == '1') {
            iloscOsob = dodajOsobeDoKontaktow(osoby, iloscOsob);

        } else if(wybor == '2') {
            system("cls");

            cout << "\tWYSZUKIWANIE" << endl;
            cout << "******************************" << endl;
            cout << "1. Wyszukaj po imieniu" << endl;
            cout << "2. Wyszukaj po nazwisku" << endl;
            cin >> wybor;

            if(wybor == '1') {
                wyszukajPoImieniu(osoby, iloscOsob);
            } else if(wybor == '2') {
                wyszukajPoNazwisku(osoby, iloscOsob);
            }

        } else if (wybor == '3') {
            wyswietlWszystkieKontakty(osoby, iloscOsob);
        } else if(wybor == '9') {
            zapisywanieKontaktowDoPliku(osoby, iloscOsob);
            system("cls");
            cout << "\tDOWIDZENIA" << endl;
            cout << "*****************************";
            Sleep(1100);
            exit(0);
        }
    }
    return 0;
}

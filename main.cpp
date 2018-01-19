#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sstream>

using namespace std;

char nazwaPlikuZUzytkownikami [] = "Uzytkownicy.txt";
char nazwaPlikuZAdresatami []    = "Adresaci.txt";
int NajwyzszaWartoscIdAdresataWPliku = 0;

struct Uzytkownik
{
    int id = 0;
    string nazwa = "", haslo = "";
};

struct Adresat
{
    int id = 0;
    string imie = "", nazwisko = "", adres = "", numerTelefonu = "", adresEmail = "";
};
string konwerjsaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

Uzytkownik wczytanieUzytkownikaZLinii(string linia)
{
    Uzytkownik uzytkownik;
    string skladowaLinii = "";
    int dlugoscLinii = linia.length();
    int numerWyrazu = 0;

    for(int i = 0; i < dlugoscLinii; i++)
        if (linia[i] != '|') skladowaLinii += linia[i];
        else
        {
            numerWyrazu++;
            switch (numerWyrazu)
            {

            case 1:
                uzytkownik.id    = atoi(skladowaLinii.c_str());
                break;
            case 2:
                uzytkownik.nazwa = skladowaLinii;
                break;
            case 3:
                uzytkownik.haslo = skladowaLinii;
                break;
            }
            skladowaLinii = "";
        }
    return uzytkownik;
}

void wczytywanieUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string linia;
    plik.open(nazwaPlikuZUzytkownikami, ios::in);
    if(plik.good())
    {
        while(getline(plik, linia))
        {
            uzytkownicy.push_back(wczytanieUzytkownikaZLinii(linia));
        }
        plik.close();
    }
}
Adresat wczytywanieAdresataZLinii(string linia)
{
    Adresat adresat;
    string skladowaLinii = "";
    int dlugoscLinii = linia.length();
    int numerWyrazu = 0;

    for(int i = 0; i < dlugoscLinii; i++)
        if (linia[i] != '|') skladowaLinii += linia[i];
        else
        {
            numerWyrazu++;
            switch (numerWyrazu)
            {

            case 1:
                adresat.id            = atoi(skladowaLinii.c_str());
                break;
            case 3:
                adresat.imie          = skladowaLinii;
                break;
            case 4:
                adresat.nazwisko      = skladowaLinii;
                break;
            case 5:
                adresat.numerTelefonu = skladowaLinii;
                break;
            case 6:
                adresat.adresEmail    = skladowaLinii;
                break;
            case 7:
                adresat.adres         = skladowaLinii;
                break;
            }
            skladowaLinii = "";
        }
    return adresat;
}
bool czyIdJestZgodne(string linia, int idUzytkownika)
{
    string idUzytkownikaWLinii = "";
    string idAdresataWLinii = "";
    bool zgodnosc = false;
    int pozycjaSprawdzanegoZnakuWLinii = 0;
    while(true)
    {
        idAdresataWLinii += linia[pozycjaSprawdzanegoZnakuWLinii];
        pozycjaSprawdzanegoZnakuWLinii++;
        if(linia[pozycjaSprawdzanegoZnakuWLinii] == '|')
        {
            pozycjaSprawdzanegoZnakuWLinii++;
            do
            {
                idUzytkownikaWLinii += linia[pozycjaSprawdzanegoZnakuWLinii++];
            }
            while(linia[pozycjaSprawdzanegoZnakuWLinii] != '|');
            if(idUzytkownika == atoi(idUzytkownikaWLinii.c_str())) zgodnosc = true;
            else zgodnosc = false;
            break;
        }
    }
    NajwyzszaWartoscIdAdresataWPliku = atoi(idAdresataWLinii.c_str());
    return zgodnosc;
}
int wczytywanieAdresatowZPliku(vector <Adresat> &adresaci, int idUzytkownika)
{
    fstream plik;
    string linia;

    plik.open(nazwaPlikuZAdresatami, ios::in);

    if(plik.good())
    {
        while(getline(plik, linia))
            if(czyIdJestZgodne(linia, idUzytkownika))
                adresaci.push_back(wczytywanieAdresataZLinii(linia));
        plik.close();
    }
}
int logowanie(vector <Uzytkownik> &uzytkownicy, vector <Adresat> &adresaci)
{
    system("cls");
    string nazwaUzytkownika, haslo;
    int idUzytkownika = 0;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;

    bool czyIstniejeUzytkownikOPodanejNazwie = false;
    int iloscUzytkownikow = uzytkownicy.size();
    int pozycjaUzytkownika;

    for(int i = 0; i < iloscUzytkownikow; i++)
    {
        if(nazwaUzytkownika == uzytkownicy[i].nazwa)
        {
            czyIstniejeUzytkownikOPodanejNazwie = true;
            pozycjaUzytkownika = i;
            break;
        }
    }
    if(czyIstniejeUzytkownikOPodanejNazwie)
    {
        for(int i = 2; i >= 0; i--)
        {
            cout << "Podaj haslo: ";
            cin >> haslo;
            if(haslo == uzytkownicy[pozycjaUzytkownika].haslo)
            {
                idUzytkownika = uzytkownicy[pozycjaUzytkownika].id;
                system("cls");
                cout << "\n\tLogowanie zakonczone pomyslnie" << endl;
                cout << "\n\n\tWitaj " << nazwaUzytkownika << " :)";
                wczytywanieAdresatowZPliku(adresaci, idUzytkownika);
                break;
            }
            else cout << "Haslo jest nieprawidlowe (pozostalo prob: " << i << ")" << endl;
        }
    }
    else cout << "Uzytkownik o podanej nazwie nie istnieje";

    Sleep(2200);
    return idUzytkownika;
}
void dopisywanieUzytkownikaDoPliku(Uzytkownik nowy)
{
    fstream plik;
    plik.open(nazwaPlikuZUzytkownikami, ios::out | ios::app);

    if(plik.good())
    {
        plik << nowy.id << '|';
        plik << nowy.nazwa << '|';
        plik << nowy.haslo << '|' << endl;
        plik.close();
    }
}
void dodawanieUzytkownika(vector <Uzytkownik> &uzytkownicy, string nazwa, string haslo)
{
    Uzytkownik nowy;
    if(uzytkownicy.empty())
        nowy.id = 1;
    else nowy.id = uzytkownicy.back().id + 1;
    nowy.nazwa = nazwa;
    nowy.haslo = haslo;
    uzytkownicy.push_back(nowy);
    dopisywanieUzytkownikaDoPliku(nowy);
}
void rejestracja(vector <Uzytkownik> &uzytkownicy)
{
    system("cls");
    string nazwaUzytkownika, haslo;
    bool czyIstniejeNazwa = false;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;

    for(vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); ++itr)
    {
        if(itr -> nazwa == nazwaUzytkownika)
        {
            czyIstniejeNazwa = true;
            break;
        }
    }
    if(czyIstniejeNazwa) cout << "Niestety podana nazwa juz istnieje";
    else
    {
        cout << "Podaj haslo: ";
        cin >> haslo;
        dodawanieUzytkownika(uzytkownicy, nazwaUzytkownika, haslo);
        system("cls");
        cout << "\tRejestracja przebiegla pomyslnie, mozesz sie zalogowac";
        Sleep(1800);
    }
}


void dopisywanieAdresataDoPliku(Adresat adresat, int idUzytkownika)
{
    fstream plik;
    plik.open(nazwaPlikuZAdresatami, ios::out | ios::app);

    if(plik.good())
    {
        plik << adresat.id << "|";
        plik << idUzytkownika << "|";
        plik << adresat.imie << "|";
        plik << adresat.nazwisko << "|";
        plik << adresat.numerTelefonu << "|";
        plik << adresat.adresEmail << "|";
        plik << adresat.adres << "|" << endl;
    }
    plik.close();
}

void dodajAdresata(vector <Adresat> &adresaci, int idUzytkownika)
{
    Adresat nowyAdresat;
    system("cls");
    cout << "\tNOWY Adresat" << endl;
    cout << "******************************" << endl;
    cout << "Podaj imie: ";
    cin.sync();
    getline(cin, nowyAdresat.imie);
    cout << "Podaj nazwisko: ";
    cin.sync();
    getline(cin, nowyAdresat.nazwisko);
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, nowyAdresat.numerTelefonu);
    cout << "Podaj adres e-mail: ";
    cin.sync();
    getline(cin, nowyAdresat.adresEmail);
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, nowyAdresat.adres);


    nowyAdresat.id = ++NajwyzszaWartoscIdAdresataWPliku;
    adresaci.push_back(nowyAdresat);
    dopisywanieAdresataDoPliku(nowyAdresat, idUzytkownika);
    cout << "\nAdresat dodany do kontaktow" << endl;
    Sleep(1000);
}

void wyszukajPoImieniu(vector <Adresat> &adresaci)
{
    string imie;
    system("cls");
    bool znaleziono = false;
    cout << "Podaj imie szukanej adresaci: ";
    cin >> imie;
    system("cls");
    int iloscAdresatow = adresaci.size();
    for(int i = 0, numeracja = 1; i < iloscAdresatow; i++)
    {
        if(adresaci[i].imie == imie)
        {
            cout << numeracja << ". " << adresaci[i].imie << " " << adresaci[i].nazwisko << " ( ID = " << adresaci[i].id << " )" << endl;
            cout << "   Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << adresaci[i].adresEmail << endl;
            cout << "   " << adresaci[i].adres << endl<< endl;
            znaleziono = true;
            numeracja++;
        }
    }
    if (znaleziono == false) cout << "Brak osob o takim imieniu" << endl << endl;
    cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

void wyszukajPoNazwisku(vector <Adresat> &adresaci)
{

    string nazwisko;
    system("cls");
    bool znaleziono = false;
    cout << "Podaj nazwisko szukanej adresaci: ";
    cin >> nazwisko;
    system("cls");
    int iloscAdresatow = adresaci.size();

    for(int i = 0, numeracja = 1; i < iloscAdresatow; i++)
    {
        if(adresaci[i].nazwisko == nazwisko)
        {
            cout << numeracja << ". " << adresaci[i].imie << " " << adresaci[i].nazwisko << " ( ID = " << adresaci[i].id << " )" << endl;
            cout << "   Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << adresaci[i].adresEmail << endl;
            cout << "   " << adresaci[i].adres << endl<< endl;
            znaleziono = true;
            numeracja++;
        }
    }
    if (znaleziono == false) cout << "\tBrak osob o takim nazwisku" << endl << endl;
    cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{

    system("cls");
    cout << "\tWSZYSTKIE KONTAKTY" << endl;
    cout << "******************************" << endl;
    int iloscAdresatow = adresaci.size();
    if(iloscAdresatow == 0)
        cout << "Brak kontaktow do wyswietlenia" << endl << endl;
    else
    {
        for(int i = 0; i < iloscAdresatow; i++)
        {
            cout << i+1 << ". " << adresaci[i].imie << " " << adresaci[i].nazwisko << " ( ID = " << adresaci[i].id << " )" << endl;
            cout << "   " << adresaci[i].adres << endl;
            cout << "   Numer telefonu: " << adresaci[i].numerTelefonu << endl;
            cout << "   Adres e-mail: " << adresaci[i].adresEmail << endl << endl;
        }
    }
    cout<<"Nacisnij dowolny klawisz, aby wrocic do menu glownego";
    getch();
}

bool usunAdresataZPliku(string liniaZDanymiDoUsuniecia)
{
    bool czyUdaloSieUsunacAdresataZPliku = false;
    fstream plik, plikTemp;
    string liniaTemp = "";

    plik.open(nazwaPlikuZAdresatami, ios::in);
    plikTemp.open("temp.temp", ios::out);

    if(plik.good() && plikTemp.good())
    {
        while(getline(plik, liniaTemp))
        {
            if(liniaZDanymiDoUsuniecia != liniaTemp)
                plikTemp << liniaTemp << endl;
        }
        plik.close();
        plikTemp.close();
        czyUdaloSieUsunacAdresataZPliku = true;
    }
    if (remove(nazwaPlikuZAdresatami) || rename("temp.temp", nazwaPlikuZAdresatami))
        czyUdaloSieUsunacAdresataZPliku = false;
    return czyUdaloSieUsunacAdresataZPliku;
}

string zwrocLinieZDanymiAdresata(vector <Adresat> &adresaci, vector <Adresat>::iterator itr, int idUzytkownika)
{
    string linia = "";
    linia = konwerjsaIntNaString(itr->id) + "|" + konwerjsaIntNaString(idUzytkownika) + "|" + itr->imie + "|"
            + itr->nazwisko + "|" + itr->numerTelefonu + "|" + itr->adresEmail + "|" + itr->adres + "|";
    return linia;
}
void edytujDaneAdresata(vector <Adresat> &adresaci, int idUzytkownika)
{
    Adresat adresatPoEdycji;
    string liniaAdresataPrzedEdycja, liniaAdresataPoEdycji;
    int numerID;
    bool czyZnaleziono = false;
    bool czyZmieniono = false;
    char wybor;
    system("cls");
    cout << "Podaj numer ID adresata, ktorego dane chcesz edytowac: ";
    cin >> numerID;
    vector <Adresat>::iterator itr;

    for(itr = adresaci.begin(); itr != adresaci.end(); ++itr )
        if (itr->id == numerID)
        {
            czyZnaleziono = true;
            liniaAdresataPrzedEdycja = zwrocLinieZDanymiAdresata(adresaci, itr, idUzytkownika);
            while (wybor != '6')
            {
                system ("cls");
                cout << "Edycja adresata:" << endl;
                cout << "   " << itr->imie << " " << itr->nazwisko << " ( ID = " << itr->id << " )" << endl;
                cout << "   " << itr->adres << endl;
                cout << "   Numer telefonu: " << itr->numerTelefonu << endl;
                cout << "   Adres e-mail: " << itr->adresEmail << endl << endl;
                cout << "Co chcesz zmienic? " << endl;
                cout << "1. Imie\n2. Nazwisko\n3. Numer telefonu\n4. Adres e-mail" << endl;
                cout << "5. Adres zamieszkania\n6. Powrot do menu\n\nWcisnij klawisz 1-6: " << endl;
                wybor = getch();
                switch(wybor)
                {
                case '1':
                    cout << "\nPodaj nowe imie: ";
                    cin.sync();
                    getline(cin, itr->imie);
                    czyZmieniono = true;
                    break;

                case '2':

                    cout << "\nPodaj nowe nazwisko: ";
                    cin.sync();
                    getline(cin, itr->nazwisko);
                    czyZmieniono = true;
                    break;

                case '3':
                    cout << "\nPodaj nowy numer telefonu: ";
                    cin.sync();
                    getline(cin, itr->numerTelefonu);
                    czyZmieniono = true;
                    break;

                case '4':
                    cout << "\nPodaj adres e-mail: ";
                    cin.sync();
                    getline(cin, itr->adresEmail);
                    czyZmieniono = true;
                    break;
                case '5':
                    cout << "\nPodaj nowy adres: ";
                    cin.sync();
                    getline(cin, itr->adres);
                    czyZmieniono = true;
                    break;
                case '6':
                    break;
                default :
                    cout << "\nBrak takiego wariantu. Wcisnij klawisz z zakresu 1-6";
                    Sleep(1800);
                    break;
                }
            }
            break;
        }

    if(!czyZnaleziono) cout << "\nBrak adresatow o podanym numerze ID" << endl;
    else if (czyZmieniono)
    {
        adresatPoEdycji.id             = itr ->id;
        adresatPoEdycji.imie           = itr->imie;
        adresatPoEdycji.nazwisko       = itr->nazwisko;
        adresatPoEdycji.adresEmail     = itr->adresEmail;
        adresatPoEdycji.numerTelefonu  = itr->numerTelefonu;
        adresatPoEdycji.adres          = itr->adres;
        liniaAdresataPoEdycji          = zwrocLinieZDanymiAdresata(adresaci, itr, idUzytkownika);
        adresaci.erase(itr);
        if(usunAdresataZPliku(liniaAdresataPrzedEdycja))
        adresaci.push_back(adresatPoEdycji);
        dopisywanieAdresataDoPliku(adresatPoEdycji, idUzytkownika);
        cout << "\nPomyslnie zmieniono dane";
    }
    else cout << "\nWracamy do menu glownego, bez zadnych zmian";

    Sleep(1500);
}
int znajdzNajwyzszaWartoscIdAdresataWPliku()
{
    fstream plik;
    string linia = "";
    string idWLinii = "";
    int idWLiniiInt = 0;
    int najwiekszaWartoscIdWPliku = 0;
    plik.open(nazwaPlikuZAdresatami, ios::in);

    if(plik.good())
    {
        while(getline(plik, linia))
        {
            idWLinii = linia.substr(0,linia.find('|'));
            idWLiniiInt = atoi(idWLinii.c_str());
            if(najwiekszaWartoscIdWPliku < idWLiniiInt)
                najwiekszaWartoscIdWPliku = idWLiniiInt;
        }

     plik.close();
    }
return najwiekszaWartoscIdWPliku;

}

void usunAdresata(vector <Adresat> &adresaci, int numerIdUzytkownika)
{
    system("cls");
    int numerID;
    bool czyZnaleziono = false;
    char wybor;
    string liniaZDanymiAdresata;
    cout << "Podaj numer ID adresata, ktorego dane chcesz usunac: ";
    cin >> numerID;
    vector <Adresat>::iterator itr;
    for(itr = adresaci.begin(); itr != adresaci.end(); ++itr )
        if (itr->id == numerID)
        {
            czyZnaleziono = true;
            break;
        }

    if(!czyZnaleziono) cout << "Brak osob o podanym ID, wracamy do menu glownego";
    else
    {
        cout << "Jezeli na pewno chcesz usunac kontakt o numerze ID = " << numerID <<" wcisnij 't': ";
        cin >> wybor;
        if(wybor == 't')
        {
            liniaZDanymiAdresata = zwrocLinieZDanymiAdresata(adresaci, itr, numerIdUzytkownika );
            adresaci.erase(itr);
            if(numerID == NajwyzszaWartoscIdAdresataWPliku)
                NajwyzszaWartoscIdAdresataWPliku = znajdzNajwyzszaWartoscIdAdresataWPliku();
            if(usunAdresataZPliku(liniaZDanymiAdresata))
            {
                cout << "Adresat zostal pomyslnie usuniety";

            }
            else
                cout << "Adresat mogl nie zostac pomyslnie usuniety z pliku";
        }
        else cout << "Wracamy do menu glownego bez usuwania adresata";
    }
    Sleep(2000);
}

void zakonczProgram()
{
    system("cls");
    cout << "\tDOWIDZENIA" << endl;
    cout << "*****************************";
    Sleep(1000);
    exit(0);
}
int wyloguj(vector <Adresat> &adresaci, int numerId)
{
    char wybor;
    cout << "Czy na pewno wylogowac ? Wcisnij 't' zeby potwierdzic: ";
    wybor = getch();
    if(wybor == 't')
    {
        adresaci.clear();
        numerId = 0;
        cout << "\nZostales wylogowany";
    }
    else cout << "\nNie zostales wylogowany";
    return numerId;
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

    wczytywanieUzytkownikowZPliku(uzytkownicy);
    int numerIdZalogowanegoUzytkownika = 0;
    char wybor;

    while(true)
    {
        if(numerIdZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "\tKSIAZKA ADRESOWA" << endl;
            cout << "******************************" << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "3. Zamknij program" << endl;

            wybor = getch();
            cin.sync();
            switch(wybor)
            {
            case '1':
                numerIdZalogowanegoUzytkownika = logowanie(uzytkownicy, adresaci);
                break;
            case '2':
                rejestracja(uzytkownicy);
                break;
            case '3':
                zakonczProgram();

            default:
                cout << "\n\tBrak takiego wariantu, wcisnij klawisz z zakresu 1-3";
                Sleep(2200);
                break;
            }
        }
        else
        {
            system("cls");
            cout << "\tKSIAZKA ADRESOWA" << endl;
            cout << "******************************" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Edytuj adresata" << endl;
            cout << "6. Usun adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj" << endl;
            cout << "9. Zakoncz" << endl;

            wybor = getch();
            cin.sync();
            switch(wybor)
            {
            case '1':
                dodajAdresata(adresaci, numerIdZalogowanegoUzytkownika);
                break;
            case '2':
                wyszukajPoImieniu(adresaci);
                break;
            case '3':
                wyszukajPoNazwisku(adresaci);
                break;
            case '4':
                wyswietlWszystkichAdresatow(adresaci);
                break;
            case '5':
                edytujDaneAdresata(adresaci, numerIdZalogowanegoUzytkownika);
                break;
            case '6':
                usunAdresata(adresaci, numerIdZalogowanegoUzytkownika);
                break;
            case '7':

                break;
            case '8':
                numerIdZalogowanegoUzytkownika = wyloguj(adresaci, numerIdZalogowanegoUzytkownika);

                break;
            case '9':
                zakonczProgram();
            default:
            {
                cout << "\n\tBrak takiego wariantu, wcisnij klawisz z zakresu 1-9";
                Sleep(2200);
                break;
            }
            }
        }
    }
    return 0;
}

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <algorithm>

using namespace std;

class Uzytkownik
{
    int id;
    string nazwa, haslo;

public:
    Uzytkownik ()
    {
        id = 0;
        nazwa = "";
        haslo = "";
    }
    int pobierzId()
    {
        return id;
    }
    string pobierzNazwe()
    {
        return nazwa;
    }
    string pobierzHaslo()
    {
        return haslo;
    }
    int ustawId (int idNowe)
    {
        id = idNowe;
    }
    void ustawNazwe(string nazwaNowa)
    {
        nazwa = nazwaNowa;
    }
    void ustawHaslo(string hasloNowe)
    {
        haslo = hasloNowe;
    }
};

class Adresat
{
    int id, idUzytkownika;
    string imie, nazwisko, adres, numerTelefonu, adresEmail;

public:
    Adresat()
    {
        this->id = 0;
        this->idUzytkownika = 0;
        this->imie = "";
        this->nazwisko = "";
        this->adres = "";
        this->numerTelefonu = "";
        this->adresEmail = "";
    }

    int pobierzId()
    {
        return id;
    }
     int pobierzIdUzytkownika()
    {
        return idUzytkownika;
    }
    string pobierzImie()
    {
        return imie;
    }
    string pobierzNazwisko()
    {
        return nazwisko;
    }
    string pobierzAdres()
    {
        return adres;
    }
    string pobierzNumerTelefonu()
    {
        return numerTelefonu;
    }
    string pobierzAdresEmail()
    {
        return adresEmail;
    }
    void ustawId(int id)
    {
        this->id = id;
    }
    void ustawIdUzytkownika(int idUzytkownika)
    {
        this->idUzytkownika = idUzytkownika;
    }
    void ustawImie(string imie)
    {
        this->imie = imie;
    }
    void ustawNazwisko(string nazwisko)
    {
        this->nazwisko = nazwisko;
    }
    void ustawAdres(string adres)
    {
        this->adres = adres;
    }
    void ustawNumerTelefonu(string numerTelefonu)
    {
        this->numerTelefonu = numerTelefonu;
    }
    void ustawAdresEmail(string adresEmail)
    {
        this->adresEmail = adresEmail;
    }
};

class KsiazkaUzytkownikow
{
    vector <Uzytkownik> uzytkownicy;
    char * nazwaPlikuZUzytkownikami;
    int numerIdZalogowanegoUzytkownika;
public:
    KsiazkaUzytkownikow()
    {
        this->nazwaPlikuZUzytkownikami = "Uzytkownicy.txt";
        this->numerIdZalogowanegoUzytkownika = 0;
        this->wczytywanieUzytkownikowZPliku();
    }

    bool logowanie()
    {
        system("cls");
        string nazwaUzytkownika, haslo;
        bool czyZalogowano = false;
        cout << "Podaj nazwe uzytkownika: ";
        cin >> nazwaUzytkownika;
        bool czyIstniejeUzytkownikOPodanejNazwie = false;
        int iloscUzytkownikow = uzytkownicy.size();
        int pozycjaUzytkownika;

        for(int i = 0; i < iloscUzytkownikow; i++)
        {
            if(nazwaUzytkownika == uzytkownicy[i].pobierzNazwe())
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
                if(haslo == uzytkownicy[pozycjaUzytkownika].pobierzHaslo())
                {
                    numerIdZalogowanegoUzytkownika = uzytkownicy[pozycjaUzytkownika].pobierzId();
                    czyZalogowano = true;
                    system("cls");
                    cout << "\n\tLogowanie zakonczone pomyslnie" << endl;
                    cout << "\n\n\tWitaj " << nazwaUzytkownika << " :)";
                    break;
                }
                else cout << "Haslo jest nieprawidlowe (pozostalo prob: " << i << ")" << endl;
            }
        }
        else cout << "Uzytkownik o podanej nazwie nie istnieje";
        Sleep(2200);
        return czyZalogowano;
    }
    void rejestracja()
    {
        system("cls");
        string nazwaUzytkownika, haslo;
        bool czyIstniejeNazwa = false;

        cout << "Podaj nazwe uzytkownika: ";
        cin >> nazwaUzytkownika;

        for(vector <Uzytkownik>::iterator itr = uzytkownicy.begin(), koniec = uzytkownicy.end(); itr !=koniec; ++itr)
        {
            if(itr->pobierzNazwe() == nazwaUzytkownika)
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
            dodawanieUzytkownika(nazwaUzytkownika, haslo);
            system("cls");
            cout << "\tRejestracja przebiegla pomyslnie, mozesz sie zalogowac";
            Sleep(1800);
        }
    }
    bool wyloguj()
    {
        bool czyWylogowano = false;
        char wybor;
        cout << "Czy na pewno wylogowac ? Wcisnij 't' zeby potwierdzic: ";
        wybor = getch();
        if(wybor == 't')
        {
            numerIdZalogowanegoUzytkownika = 0;
            czyWylogowano = true;
            cout << "\nZostales wylogowany";
        }
        else cout << "\nNie zostales wylogowany";
        return czyWylogowano;
    }
    void zmienHaslo()
    {
        system("cls");
        string noweHaslo;
        cout << "Podaj nowe haslo: ";
        cin >> noweHaslo;
        int iloscUzytkownikow = uzytkownicy.size();

        for(int i = 0; i < iloscUzytkownikow; i++)
            if(uzytkownicy[i].pobierzId() == numerIdZalogowanegoUzytkownika)
            {
                uzytkownicy[i].ustawHaslo(noweHaslo);
                break;
            }
        if(zapiszDaneUzytkownikowDoPliku())
            cout << endl << "\n Haslo zostalo zmienione";
        Sleep(1800);
    }
    int pobierzNumerIdZalogowanegoUzytkownika()
    {
        return numerIdZalogowanegoUzytkownika;
    }
private:
    void wczytywanieUzytkownikowZPliku()
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
    bool zapiszDaneUzytkownikowDoPliku()
    {
        fstream plik;
        bool czyZapisano = false;
        plik.open(nazwaPlikuZUzytkownikami, ios::out);
        int iloscUzytkownikow = uzytkownicy.size();
        if(plik.good())
        {
            for(int i = 0; i < iloscUzytkownikow; i++)
            {
                plik << uzytkownicy[i].pobierzId() << '|';
                plik << uzytkownicy[i].pobierzNazwe() << '|';
                plik << uzytkownicy[i].pobierzHaslo() << '|' << endl;
            }
            plik.close();
            czyZapisano = true;
        }
        return czyZapisano;
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
                    uzytkownik.ustawId(atoi(skladowaLinii.c_str()));
                    break;
                case 2:
                    uzytkownik.ustawNazwe(skladowaLinii);
                    break;
                case 3:
                    uzytkownik.ustawHaslo(skladowaLinii);
                    break;
                }
                skladowaLinii = "";
            }
        return uzytkownik;
    }

    void dodawanieUzytkownika(string nazwa, string haslo)
    {
        Uzytkownik nowy;
        if(uzytkownicy.empty())
            nowy.ustawId(1);
        else nowy.ustawId(uzytkownicy.back().pobierzId() + 1);
        nowy.ustawNazwe(nazwa);
        nowy.ustawHaslo(haslo);
        uzytkownicy.push_back(nowy);
        dopisywanieUzytkownikaDoPliku(nowy);
    }
    void dopisywanieUzytkownikaDoPliku(Uzytkownik &nowy)
    {
        fstream plik;
        plik.open(nazwaPlikuZUzytkownikami, ios::out | ios::app);

        if(plik.good())
        {
            plik << nowy.pobierzId() << '|';
            plik << nowy.pobierzNazwe() << '|';
            plik << nowy.pobierzHaslo() << '|' << endl;
            plik.close();
        }
    }
};

class KsiazkaAdresatow
{
    vector <Adresat> adresaci;
    char * nazwaPlikuZAdresatami;
    int najwyzszaWartoscIdAdresataWPliku;
    int idUzytkownika;
public:
    KsiazkaAdresatow()
    {
        this->nazwaPlikuZAdresatami = "Adresaci.txt";
        this->najwyzszaWartoscIdAdresataWPliku = 0;
        this->idUzytkownika = 0;
    }
    void ustawIdUzytkownika(int idUzytkownika)
    {
        this->idUzytkownika = idUzytkownika;
    }
    void wyloguj()
    {
     adresaci.clear();
     idUzytkownika = 0;
    }
    void wczytywanieAdresatowZPliku()
    {
        fstream plik;
        string linia;
        plik.open(nazwaPlikuZAdresatami, ios::in);

        if(plik.good())
        {
            while(getline(plik, linia))
                if(czyIdJestZgodne(linia))
                    adresaci.push_back(wczytywanieAdresataZLinii(linia));
            plik.close();
        }
    }
    void dodajAdresata()
    {
        Adresat nowyAdresat;
        string imie, nazwisko, adres, adresEmail, numerTelefonu;
        system("cls");
        cout << "\tNOWY Adresat" << endl;
        cout << "******************************" << endl;
        cout << "Podaj imie: ";
        cin.sync();
        getline(cin, imie);
        nowyAdresat.ustawImie(zamienPierwszeLiteryKazdegoWyrazuNaDuzePozostaleNaMale(imie));
        cout << "Podaj nazwisko: ";
        cin.sync();
        getline(cin, nazwisko);
        nowyAdresat.ustawNazwisko(zamienPierwszeLiteryKazdegoWyrazuNaDuzePozostaleNaMale(nazwisko));
        cout << "Podaj numer telefonu: ";
        cin.sync();
        getline(cin, numerTelefonu);
        nowyAdresat.ustawNumerTelefonu(numerTelefonu);
        cout << "Podaj adres e-mail: ";
        cin.sync();
        getline(cin, adresEmail);
        nowyAdresat.ustawAdresEmail(adresEmail);
        cout << "Podaj adres: ";
        cin.sync();
        getline(cin, adres);
        nowyAdresat.ustawAdres(adres);
        nowyAdresat.ustawId(++najwyzszaWartoscIdAdresataWPliku);
        nowyAdresat.ustawIdUzytkownika(idUzytkownika);
        adresaci.push_back(nowyAdresat);
        dopisywanieAdresataDoPliku(nowyAdresat);
        cout << "\nAdresat dodany do kontaktow" << endl;
        Sleep(1000);
    }
    void wyszukajPoImieniu()
    {
        string imie;
        system("cls");
        bool znaleziono = false;
        cout << "Podaj imie szukanego adresata\n(mozesz podac fraze - im wiecej znakow podasz tym wynik bedzie dokladniejszy): " << endl;
        cin >> imie;
        imie = zamienPierwszaLitereNaDuzaPozostaleNaMale(imie);
        system("cls");
        int iloscAdresatow = adresaci.size();
        for(int i = 0, numeracja = 1; i < iloscAdresatow; i++)
        {
            if(adresaci[i].pobierzImie().find(imie) != string::npos)
            {
                cout << numeracja << ". " << adresaci[i].pobierzImie() << " " << adresaci[i].pobierzNazwisko()
                << " ( ID = " << adresaci[i].pobierzId() << " )" << endl;
                cout << "   Numer telefonu: " << adresaci[i].pobierzNumerTelefonu() << endl;
                cout << "   Adres e-mail: " << adresaci[i].pobierzAdresEmail() << endl;
                cout << "   " << adresaci[i].pobierzAdres() << endl<< endl;
                znaleziono = true;
                numeracja++;
            }
        }
        if (znaleziono == false) cout << "Brak osob o takim imieniu" << endl << endl;
        cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
        getch();
    }
    void wyszukajPoNazwisku()
    {

        string nazwisko;
        system("cls");
        bool znaleziono = false;
        cout << "Podaj nazwisko szukanego adresata \n(mozesz podac tylko poczatkawa fraze - im wiecej znakow podasz tym wynik bedzie dokladniejszy): " << endl;
        cin >> nazwisko;
        nazwisko = zamienPierwszaLitereNaDuzaPozostaleNaMale(nazwisko);
        system("cls");
        int iloscAdresatow = adresaci.size();

        for(int i = 0, numeracja = 1; i < iloscAdresatow; i++)
        {
            if(adresaci[i].pobierzNazwisko().find(nazwisko) != string::npos)
            {
                cout << numeracja << ". " << adresaci[i].pobierzImie() << " " << adresaci[i].pobierzNazwisko()
                << " ( ID = " << adresaci[i].pobierzId() << " )" << endl;
                cout << "   Numer telefonu: " << adresaci[i].pobierzNumerTelefonu() << endl;
                cout << "   Adres e-mail: " << adresaci[i].pobierzAdresEmail() << endl;
                cout << "   " << adresaci[i].pobierzAdres() << endl<< endl;
                znaleziono = true;
                numeracja++;
            }
        }
        if (znaleziono == false) cout << "\tBrak osob o takim nazwisku" << endl << endl;
        cout << "Nacisnij dowolny klawisz, aby wrocic do menu glownego";
        getch();
    }
    void wyswietlWszystkichAdresatow()
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
                cout << i+1 << ". " << adresaci[i].pobierzImie() << " " << adresaci[i].pobierzNazwisko() << " ( ID = " << adresaci[i].pobierzId() << " )" << endl;
                cout << "   Numer telefonu: " << adresaci[i].pobierzNumerTelefonu() << endl;
                cout << "   Adres e-mail: " << adresaci[i].pobierzAdresEmail() << endl;
                cout << "   Adres: " << adresaci[i].pobierzAdres() << endl <<endl;
            }
        }
        cout<<"Nacisnij dowolny klawisz, aby wrocic do menu glownego";
        getch();
    }
    void edytujDaneAdresata()
    {
        string liniaAdresataPrzedEdycja, liniaAdresataPoEdycji, noweDane = "";
        int numerID;
        bool czyZnaleziono = false;
        bool czyZmieniono = false;
        char wybor;
        system("cls");
        cout << "Podaj numer ID adresata, ktorego dane chcesz edytowac: ";
        cin >> numerID;
        vector <Adresat>::iterator itr , koniec = adresaci.end();
        for(itr = adresaci.begin(); itr != koniec; ++itr )
            if (itr->pobierzId() == numerID)
            {
                czyZnaleziono = true;
                liniaAdresataPrzedEdycja = zwrocLinieZDanymiAdresata(itr);
                while(wybor != '6')
                {
                    system ("cls");
                    cout << "Edycja adresata:" << endl;
                    cout << "   " << itr->pobierzImie() << " " << itr->pobierzNazwisko() << " ( ID = " << itr->pobierzId() << " )" << endl;
                    cout << "   " << itr->pobierzAdres() << endl;
                    cout << "   Numer telefonu: " << itr->pobierzNumerTelefonu() << endl;
                    cout << "   Adres e-mail: " << itr->pobierzAdresEmail() << endl << endl;
                    cout << "Co chcesz zmienic? " << endl;
                    cout << "1. Imie\n2. Nazwisko\n3. Numer telefonu\n4. Adres e-mail" << endl;
                    cout << "5. Adres zamieszkania\n6. Powrot do menu\n\nWcisnij klawisz 1-6: " << endl;
                    wybor = getch();
                    switch(wybor)
                    {
                    case '1':
                        cout << "\nPodaj nowe imie: ";
                        cin.sync();
                        getline(cin, noweDane);
                        itr->ustawImie(zamienPierwszeLiteryKazdegoWyrazuNaDuzePozostaleNaMale(noweDane));
                        czyZmieniono = true;
                        break;
                    case '2':
                        cout << "\nPodaj nowe nazwisko: ";
                        cin.sync();
                        getline(cin, noweDane);
                        itr->ustawNazwisko(zamienPierwszeLiteryKazdegoWyrazuNaDuzePozostaleNaMale(noweDane));
                        czyZmieniono = true;
                        break;
                    case '3':
                        cout << "\nPodaj nowy numer telefonu: ";
                        cin.sync();
                        getline(cin, noweDane);
                        itr->ustawNumerTelefonu(noweDane);
                        czyZmieniono = true;
                        break;
                    case '4':
                        cout << "\nPodaj adres e-mail: ";
                        cin.sync();
                        getline(cin, noweDane);
                        itr->ustawAdresEmail(noweDane);
                        czyZmieniono = true;
                        break;
                    case '5':
                        cout << "\nPodaj nowy adres: ";
                        cin.sync();
                        getline(cin, noweDane);
                        itr->ustawAdres(noweDane);
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
            liniaAdresataPoEdycji = zwrocLinieZDanymiAdresata(itr);
            if(edytujaDaneAdresataWPliku(liniaAdresataPrzedEdycja, liniaAdresataPoEdycji))
                cout << "\nPomyslnie zmieniono dane";
        }
        else cout << "\nWracamy do menu glownego, bez zadnych zmian";
        Sleep(1500);
    }
    void usunAdresata()
    {
        system("cls");
        int numerID;
        bool czyZnaleziono = false;
        char wybor;
        string liniaZDanymiAdresata;
        cout << "Podaj numer ID adresata, ktorego dane chcesz usunac: ";
        cin >> numerID;
        vector <Adresat>::iterator itr, koniec = adresaci.end();
        for(itr = adresaci.begin(); itr != koniec; ++itr )
            if (itr->pobierzId() == numerID)
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
                liniaZDanymiAdresata = zwrocLinieZDanymiAdresata(itr);
                adresaci.erase(itr);
                if(usunAdresataZPliku(liniaZDanymiAdresata))
                    cout << "Adresat zostal pomyslnie usuniety";
                else
                    cout << "Adresat mogl nie zostac pomyslnie usuniety z pliku";
                if(numerID == najwyzszaWartoscIdAdresataWPliku)
                    najwyzszaWartoscIdAdresataWPliku = znajdzNajwyzszaWartoscIdAdresataWPliku();
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
private:
    void dopisywanieAdresataDoPliku(Adresat &adresat)
    {
        fstream plik;
        plik.open(nazwaPlikuZAdresatami, ios::out | ios::app);

        if(plik.good())
        {
            plik << adresat.pobierzId() << "|";
            plik << adresat.pobierzIdUzytkownika() << "|";
            plik << adresat.pobierzImie() << "|";
            plik << adresat.pobierzNazwisko() << "|";
            plik << adresat.pobierzNumerTelefonu() << "|";
            plik << adresat.pobierzAdresEmail() << "|";
            plik << adresat.pobierzAdres() << "|" << endl;
        }
        plik.close();
    }
    bool edytujaDaneAdresataWPliku(string liniaZDanymiPrzedEdycja, string liniaZDanymiPoEdycji)
    {
        bool czyUdaloSieEdytowacAdresataWPliku = false;
        fstream plik, plikTemp;
        string liniaTemp = "";

        plik.open(nazwaPlikuZAdresatami, ios::in);
        plikTemp.open("temp.temp", ios::out);

        if(plik.good() && plikTemp.good())
        {
            while(getline(plik, liniaTemp))
            {
                if(liniaZDanymiPrzedEdycja != liniaTemp)
                    plikTemp << liniaTemp << endl;
                else
                    plikTemp << liniaZDanymiPoEdycji << endl;
            }
            plik.close();
            plikTemp.close();
            czyUdaloSieEdytowacAdresataWPliku = true;
        }
        if (remove(nazwaPlikuZAdresatami) || rename("temp.temp", nazwaPlikuZAdresatami))
            czyUdaloSieEdytowacAdresataWPliku = false;
        return czyUdaloSieEdytowacAdresataWPliku;
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
    string zwrocLinieZDanymiAdresata(vector <Adresat>::iterator itr)
    {
        string linia = "";
        linia = konwerjsaIntNaString(itr->pobierzId()) + "|" + konwerjsaIntNaString(itr->pobierzIdUzytkownika()) + "|" + itr->pobierzImie() + "|"
                + itr->pobierzNazwisko() + "|" + itr->pobierzNumerTelefonu() + "|" + itr->pobierzAdresEmail() + "|" + itr->pobierzAdres() + "|";
        return linia;
    }
    int znajdzNajwyzszaWartoscIdAdresataWPliku()
    {
        fstream plik;
        string linia = "";
        string idWLinii = "";
        int najwiekszaWartoscIdWPliku = 0;
        plik.open(nazwaPlikuZAdresatami, ios::in);
        if(plik.good())
        {
            while(getline(plik, linia))
            {
                idWLinii = linia.substr(0,linia.find('|'));
                najwiekszaWartoscIdWPliku = atoi(idWLinii.c_str());
            }
            plik.close();
        }
        return najwiekszaWartoscIdWPliku;
    }
    string konwerjsaIntNaString(int liczba)
    {
        ostringstream ss;
        ss << liczba;
        string str = ss.str();
        return str;
    }
    string zamienPierwszaLitereNaDuzaPozostaleNaMale(string tekst)
    {
        if (!tekst.empty())
        {
            transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
            tekst[0] = toupper(tekst[0]);
        }
        return tekst;
    }
    string zamienPierwszeLiteryKazdegoWyrazuNaDuzePozostaleNaMale(string tekst)
    {
        int dlugoscTekstu = tekst.length();
        string wyraz = "";
        string tekstGdzieKazdyWyrazZDuzejLitery = "";

        for(int i = 0; i < dlugoscTekstu; i++)
        {
            if(tekst[i] != ' ') wyraz += tekst[i];
            else
            {
                tekstGdzieKazdyWyrazZDuzejLitery += zamienPierwszaLitereNaDuzaPozostaleNaMale(wyraz) + " ";
                wyraz = "";
            }
        }
        tekstGdzieKazdyWyrazZDuzejLitery += zamienPierwszaLitereNaDuzaPozostaleNaMale(wyraz);
        return tekstGdzieKazdyWyrazZDuzejLitery;
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
                    adresat.ustawId(atoi(skladowaLinii.c_str()));
                    break;
                case 2:
                    adresat.ustawIdUzytkownika(atoi(skladowaLinii.c_str()));
                    break;
                case 3:
                    adresat.ustawImie(skladowaLinii);
                    break;
                case 4:
                    adresat.ustawNazwisko(skladowaLinii);
                    break;
                case 5:
                    adresat.ustawNumerTelefonu(skladowaLinii);
                    break;
                case 6:
                    adresat.ustawAdresEmail(skladowaLinii);
                    break;
                case 7:
                    adresat.ustawAdres(skladowaLinii);
                    break;
                }
                skladowaLinii = "";
            }
        return adresat;
    }
    bool czyIdJestZgodne(string linia)
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
                break;
            }
        }
        najwyzszaWartoscIdAdresataWPliku = atoi(idAdresataWLinii.c_str());
        return zgodnosc;
    }
};

int main()
{
    KsiazkaUzytkownikow ksiazkaUzytkownikow;
    KsiazkaAdresatow ksiazkaAdresatow;
    char wybor;

    while(true)
    {
        if(ksiazkaUzytkownikow.pobierzNumerIdZalogowanegoUzytkownika() == 0)
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
                if(ksiazkaUzytkownikow.logowanie())
                {
                    ksiazkaAdresatow.ustawIdUzytkownika(ksiazkaUzytkownikow.pobierzNumerIdZalogowanegoUzytkownika());
                    ksiazkaAdresatow.wczytywanieAdresatowZPliku();
                }
                break;
            case '2':
                ksiazkaUzytkownikow.rejestracja();
                break;
            case '3':
                ksiazkaAdresatow.zakonczProgram();

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
                ksiazkaAdresatow.dodajAdresata();
                break;
            case '2':
                ksiazkaAdresatow.wyszukajPoImieniu();
                break;
            case '3':
                ksiazkaAdresatow.wyszukajPoNazwisku();
                break;
            case '4':
                ksiazkaAdresatow.wyswietlWszystkichAdresatow();
                break;
            case '5':
                ksiazkaAdresatow.edytujDaneAdresata();
                break;
            case '6':
                ksiazkaAdresatow.usunAdresata();
                break;
            case '7':
                ksiazkaUzytkownikow.zmienHaslo();
                break;
            case '8':
                if(ksiazkaUzytkownikow.wyloguj()) ksiazkaAdresatow.wyloguj();
                break;
            case '9':
                ksiazkaAdresatow.zakonczProgram();
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

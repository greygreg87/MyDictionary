#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct Slownik
{
    string wyraz, tlumaczenie;
}; // Struktura

int zaladujSlownik (Slownik l[]);
int dodajSlowo(Slownik l[], int n, string s);
int znajdzSlowo(Slownik l[], int n, string s);
void wyswietlSlownik(Slownik l[], int n);
void zmienNumeracje (Slownik l[], int i, int n);
void zapiszSlownik (Slownik l[], int n);
void exportujSlownik (Slownik l[], int n);

int main()
{
    Slownik lista [100];
    int iloscSlow = zaladujSlownik(lista);
    string slowo;
    char wybor;
    for (;;)
    {
        cout << "Witaj uzytkowniku slownika! Wybierz opcje:" << endl;
        cout << "1. Dodaj slowo" << endl;
        cout << "2. Znajdz slowo" << endl;
        cout << "3. Wyswietl caly slownik" << endl;
        cout << "4. Export slownika do notatnika" << endl;
        cout << "8. Wyjscie z programu z bez zapisu danych" << endl;
        cout << "9. Wyjscie z programu z zapisem danych" << endl;
        cout << "Ilosc slow w slowniku wynosi: " << iloscSlow << endl;
        cin >> wybor;

        switch (wybor)
        {
            case '1':
                cout << "Podaj slowo do dodania: " << endl;
                cin >> slowo;
                iloscSlow = dodajSlowo(lista, iloscSlow, slowo);
            break;

            case '2':
                cout << "Podaj szukane slowo: " << endl;
                cin >> slowo;
                if (znajdzSlowo(lista, iloscSlow, slowo) == 0)
                {
                    cout << "Brak slowa w slowniku" << endl;
                } // if
                cout << "Aby kontynuowac wcisnij enter...";
                cin.sync ();
                getchar();
            break;

            case '3':
                wyswietlSlownik (lista, iloscSlow);
            break;

            case '4':
                exportujSlownik (lista, iloscSlow);
            break;

            case '8':
                exit(0);
            break;

            case '9':
                zapiszSlownik (lista, iloscSlow);
                exit(0);
            break;

            default: cout << "Nie ma takiej opcji!" ;
        } // switch case

        Sleep (1000);
        system ("cls");

    } // for
    return 0;
} // main

int zaladujSlownik (Slownik l[])
{
    int nr_linii = 1;
    int j = 0;
    string linia;
    fstream plik ;
    plik.open ("Slownik.txt" , ios::in) ;

    while (getline (plik , linia))
    {
       switch (nr_linii)
       {
           case 1: l[j].wyraz = linia;          break;
           case 2: l[j].tlumaczenie = linia ;   break;
       };    // switch case

       if (nr_linii == 2) {nr_linii = 0; j++;} // Cala petla wykonuje sie prawidlowoa ilosc razy

       nr_linii++ ;
    } // while

    plik.close () ;
    return j;
} // zaladujSlownik

int dodajSlowo(Slownik l[], int n, string s)
{
    if (znajdzSlowo(l,n,s) != 0)
    {
        cout << "Podane slowo znajduje sie juz w slowniku!" << endl;
        Sleep (1500);
    } // if
    else
    {
        string tlumaczenieSlowa;
        cout << "Podaj tlumaczenie slowa: " << endl;
        cin >> tlumaczenieSlowa;

        if(n==0)
        {
            l[n].wyraz = s;
            l[n].tlumaczenie = tlumaczenieSlowa;
        } // if
        else
        {
            int j = 0;
            for (int i = 0; i<n; i++)
            {
                if (l[i].wyraz[j]>s[j])
                {
                    zmienNumeracje(l,i,n);
                    l[i].wyraz = s;
                    l[i].tlumaczenie = tlumaczenieSlowa;
                    i=n+1;
                } // if
                else if (l[i].wyraz[j]==s[j])
                {
                    j++;
                    if (j>=l[i].wyraz.length())
                    {
                        zmienNumeracje(l,i+1,n);
                        l[i+1].wyraz = s;
                        l[i+1].tlumaczenie = tlumaczenieSlowa;
                        i=n+1;
                    } // if
                    if (j>=s.length())
                    {
                        zmienNumeracje(l,i,n);
                        l[i].wyraz = s;
                        l[i].tlumaczenie = tlumaczenieSlowa;
                        i=n+1;
                    } // if
                    i--;
                } // else if
                else if (i == n-1)
                {
                    l[i+1].wyraz = s;
                    l[i+1].tlumaczenie = tlumaczenieSlowa;
                } // else if
            } // for
        } // else
        n++;
    } // else
    return n;
} // dodajSlowo

int znajdzSlowo(Slownik l[], int n, string s)
{
    int iloscTrafien = 0;
    for (int i = 0; i<n; i++)
    {
        if (l[i].wyraz == s)
        {
            cout << s << " - " << l[i].tlumaczenie << endl;
            iloscTrafien ++;
        } // if
    } //for
    return iloscTrafien;

} // znajdzSlowo

void wyswietlSlownik(Slownik l[], int n)
{
    for (int i = 0; i<n; i++)
    {
        cout << l[i].wyraz << " - ";
        cout << l[i].tlumaczenie << endl;
    } // for
    cout << "Aby kontynuowac wcisnij enter...";
    cin.sync ();
    getchar();
} // void

void zmienNumeracje (Slownik l[], int i, int n)
{
    for (int j = n-1; j>=i; j--)
    {
        l[j+1].wyraz = l[j].wyraz;
        l[j+1].tlumaczenie = l[j].tlumaczenie;
    } // for
} // zmienNumeracje

void zapiszSlownik (Slownik l[], int n)
{
    fstream notatnik;
    notatnik.open("Slownik.txt", ios::out);
    if (notatnik.good())
    {
        for (int i = 0; i<n; i++)
        {
            notatnik << l[i].wyraz << endl ;
            notatnik << l[i].tlumaczenie << endl;
        } // for

        notatnik.close ();
        cout << "Zapis danych do pliku zakonczony powodzeniem!. Do widzenia" << endl;
        Sleep (1500);
    }   // if

    else cout << "Zapis wprowadzonych danych nie powiodl sie!" << endl;
    Sleep(1500);
} // zapiszSlownik

void exportujSlownik (Slownik l[], int n)
{
    fstream notatnik;
    notatnik.open("Moj slownik.txt", ios::out);
    if (notatnik.good())
    {
        for (int i = 0; i<n; i++)
        {
            notatnik << l[i].wyraz << " - " << l[i].tlumaczenie << endl;
        } // for

        notatnik.close ();
        cout << "Zapis danych do pliku zakonczony powodzeniem!" << endl;
        Sleep (1500);
    }   // if

    else cout << "Zapis wprowadzonych danych nie powiodl sie!" << endl;
    Sleep(1500);
} // exportujSlownik

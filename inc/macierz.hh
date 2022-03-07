#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "wektor.hh"
using namespace std;

//klasa macierzy 3x3
class Macierz
{
    Wektor macierz[3]; //macierz 3x3

public:
    // operatory indeksujace (dzieki nim mozna operowac na prywatnej czesci klasy)
    Wektor operator[](int Ind) const { return macierz[Ind]; }
    Wektor &operator[](int Ind) { return macierz[Ind]; }
    // konstruktor macierzowy
    Macierz()
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                macierz[i][j] = 0;
            }
            macierz[i][i] = 1;
        }
    }
    //METODA kopiowania macierzy
    void copy(Macierz from)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                macierz[i][j] = from[i][j];
            }
        }
    }
};
//przeciazenie operatora mnozenia macierz * macierz
Macierz operator*(Macierz pom, Macierz tmp)
{
    Macierz wynik;
    float a, b;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {

                a = pom[i][k] * tmp[k][j];
                b = b + a;
            }
            wynik[i][j] = b;
            a = 0, b = 0;
        }
    }
    return wynik;
}
//przeciazenie operatora dodawania macierzy
Macierz operator+(Macierz pom, Macierz tmp)
{
    Macierz wynik;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
           wynik[i][j] = pom[i][j] + tmp[i][j];
        }
    }
    return wynik;
}
//przeciazenie operatora mnozenia macierz*wektor
Wektor operator*(Macierz macierz, Wektor wektor)
{
    Wektor wynik;
    float b, a;
    b = 0;
    a = 0;
    for (int i = 0; i < 3; i++)
    {
        b = macierz[i] * wektor;
        wynik[i] = b;
    }
    return wynik;
}
//przeciazenie operatora mnozenia macierz*zmienna
Macierz operator*(Macierz macierz, float tmp)
{
    Macierz wynik;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            wynik[i][j] = macierz[i][j] * tmp;
        }
    }
    return wynik;
}

//przeciazenie operatora wyjscia
std::ostream &operator<<(std::ostream &out, const Macierz &macierz)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << macierz[i][j] << " ";
        }
        cout << endl;
    }
    return out;
}

#endif
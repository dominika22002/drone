#ifndef ZAKRES_HH
#define ZAKRES_HH

#include <iostream>
#include <iomanip>
#include "bryla.hh"
#include "przeszkoda.hh"
#include "wektor.hh"
#include "lacze_do_gnuplota.hh"
using namespace std;
/*
klasa sluzaca do stworzenia funkcji uderzen w przeszkody, 
posiada wspolrzedne punktow strategicznych, tzn. najmniejsza i najwieksza wartosc wspolrzednej x, y i z
*/
class Zakres
{
    float x_min; //to te wspolrzedne
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;

    // Wektor wspolrzedne[8];

public:
    //metody slurzace dostaniu sie do prywatnej czesci klasy
    float getx_min() const { return x_min; }
    float &getx_min() { return x_min; }
    float getx_max() const { return x_max; }
    float &getx_max() { return x_max; }
    float gety_min() const { return y_min; }
    float &gety_min() { return y_min; }
    float gety_max() const { return y_max; }
    float &gety_max() { return y_max; }
    float getz_min() const { return z_min; }
    float &getz_min() { return z_min; }
    float getz_max() const { return z_max; }
    float &getz_max() { return z_max; }
    //konstruktor
    Zakres()
    {
        float x_min = 0;
        float x_max = 0;
        float y_min = 0;
        float y_max = 0;
        float z_min = 0;
        float z_max = 0;
    }
};

#endif
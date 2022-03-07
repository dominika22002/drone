#ifndef DRON_HH
#define DRON_HH

#include <iostream>
#include <iomanip>
#include "bryla.hh"
#include "zakres.hh"
#include "przeszkoda.hh"
#include "wektor.hh"
#include "lacze_do_gnuplota.hh"
using namespace std;
//klasa dron
template <int rozmiar1, int rozmiar2>
class Dron : public Bryla<rozmiar1>
{
    Bryla<rozmiar1> dron;    //glowna bryla drona, wierzcholki napisane w formacie "dla gnuplota"
    Bryla<rozmiar2> wirnik1; //silnik 1
    Bryla<rozmiar2> wirnik2; //silnik 2

public:
    Bryla<rozmiar1> getdron() const { return dron; }
    Bryla<rozmiar1> &getdron() { return dron; }
    Bryla<rozmiar2> getwirnik1() const { return wirnik1; }
    Bryla<rozmiar2> &getwirnik1() { return wirnik1; }
    Bryla<rozmiar2> getwirnik2() const { return wirnik2; }
    Bryla<rozmiar2> &getwirnik2() { return wirnik2; }
    //konstruktor
    Dron()
    {
        Wektor obiekt;
        obiekt = 0;
        for (int i = 0; i < rozmiar1; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                dron.getbryla().push_back(obiekt); //funkcja std::vector
            }
        }
        for (int i = 0; i < rozmiar2; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                wirnik1.getbryla().push_back(obiekt); //funkcja std::vector
                wirnik2.getbryla().push_back(obiekt);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            dron.getkaty()[i] = 0;
            wirnik1.getkaty()[i] = 0;
            wirnik2.getkaty()[i] = 0;
        }
    }

    virtual Zakres zakres()
    {
        Zakres tmp;
        tmp.getx_min() = dron.mini('X') + (dron.mini('X') - wirnik1.mini('X'));
        tmp.getx_max() = dron.maxi('X');
        tmp.gety_min() = dron.mini('Y');
        tmp.gety_max() = dron.maxi('Y');
        tmp.getz_min() = dron.mini('Z');
        tmp.getz_max() = dron.maxi('Z');
        return tmp;
    }
};

#endif
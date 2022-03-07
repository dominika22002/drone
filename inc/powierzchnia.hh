#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH

#include <iostream>
#include <iomanip>
#include "bryla.hh"
#include "przeszkoda.hh"

#include "wektor.hh"
#include "lacze_do_gnuplota.hh"
using namespace std;
//klasa przetrzymujaca powierzchnie wody i ziemi, sklada sie z bryly 
template <int rozmiar>
class Powierzchnia : public Bryla<rozmiar>
{
private:
    Bryla<rozmiar> powierzchnia; //skladnik klasy powierzchnia

public:
//metody sluzace do dostania sie do prywatnej czesci klasy
    Bryla<rozmiar> getpowierzchnia() const { return powierzchnia; }
    Bryla<rozmiar> &getpowierzchnia() { return powierzchnia; }
    Powierzchnia() : Bryla<rozmiar>(){};
//metoda wirtualna do liczenia zakresu
    virtual Zakres zakres()//shared_ptr<Zakres> tmp)
    {
        Zakres tmp;
        tmp.getx_min() = powierzchnia.mini('X'); //liczy zakres na podstawie funkcji w bryla.hh
        tmp.getx_max() = powierzchnia.maxi('X');
        tmp.gety_min() = powierzchnia.mini('Y');
        tmp.gety_max() = powierzchnia.maxi('Y');
        tmp.getz_min() = powierzchnia.mini('Z');
        tmp.getz_max() = powierzchnia.maxi('Z');
        return tmp;
    }
};

#endif
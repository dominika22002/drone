
#ifndef PRZESZKODA_HH
#define PRZESZKODA_HH
#include <iostream>
#include <iomanip>
#include "bryla.hh"
#include "wektor.hh"
#include "zakres.hh"
#include "lacze_do_gnuplota.hh"

using namespace std;
//klasa przeszkoda
template <int rozmiar>
class Przeszkoda : public Bryla<rozmiar>
{
    Bryla<rozmiar> przeszkoda; //bryla przechowuje wierzcholki do gnuplota
    string nazwa;// nazwa przeszkody, pomocna przy dynamicznym tworzeniu przeszkod

public:
//metody odwolania sie do prywatnej czesci klasy
    Bryla<rozmiar> getprzeszkoda() const { return przeszkoda; }
    Bryla<rozmiar> &getprzeszkoda() { return przeszkoda; }
    string getnazwa() const { return nazwa; }
    string &getnazwa() { return nazwa; }
//konstruktor
    Przeszkoda()
    {
        Wektor obiekt;
        obiekt = 0;
        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                przeszkoda.getbryla().push_back(obiekt); //funkcja std::vector
            }
        }
    }
    //metoda tworzaca przeszkode, wyglada strasznie, ale dzieki temu mozna stworzyc dowolne wymiary (rownoleglobok)
    void tworzprzeszkode(float x1, float x2, float y1, float y2, float z1, float z2)
    {
        przeszkoda.getbryla()[0].wektorXYZ(x1, y1, z1);
        przeszkoda.getbryla()[1].wektorXYZ(x2, y1, z1);
        przeszkoda.getbryla()[2].wektorXYZ(x2, y2, z1);
        przeszkoda.getbryla()[3].wektorXYZ(x1, y2, z1);
        przeszkoda.getbryla()[4].wektorXYZ(x1, y1, z1);
        przeszkoda.getbryla()[5].wektorXYZ(x1, y1, z2);
        przeszkoda.getbryla()[6].wektorXYZ(x2, y1, z2);
        przeszkoda.getbryla()[7].wektorXYZ(x2, y1, z1);
        przeszkoda.getbryla()[8].wektorXYZ(x2, y1, z2);
        przeszkoda.getbryla()[9].wektorXYZ(x2, y2, z2);
        przeszkoda.getbryla()[10].wektorXYZ(x2, y2, z1);
        przeszkoda.getbryla()[11].wektorXYZ(x2, y2, z2);
        przeszkoda.getbryla()[12].wektorXYZ(x1, y2, z2);
        przeszkoda.getbryla()[13].wektorXYZ(x1, y2, z1);
        przeszkoda.getbryla()[14].wektorXYZ(x1, y2, z2);
        przeszkoda.getbryla()[15].wektorXYZ(x1, y1, z2);
        przeszkoda.getbryla()[16].wektorXYZ(x2, y1, z2);
        przeszkoda.getbryla()[17].wektorXYZ(x2, y2, z1);
        przeszkoda.getbryla()[18].wektorXYZ(x2, y2, z2);
        przeszkoda.getbryla()[19].wektorXYZ(x2, y1, z1);
    }
    //metoda wirtualna liczaca zakres
    virtual Zakres zakres()
    {
        Zakres tmp;
        tmp.getx_min() = przeszkoda.mini('X');
        tmp.getx_max() = przeszkoda.maxi('X');
        tmp.gety_min() = przeszkoda.mini('Y');
        tmp.gety_max() = przeszkoda.maxi('Y');
        tmp.getz_min() = przeszkoda.mini('Z');
        tmp.getz_max() = przeszkoda.maxi('Z');
        return tmp;
    }
};
#endif
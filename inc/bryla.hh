#ifndef BRYLA_HH
#define BRYLA_HH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include "macierz.hh"
#include "zakres.hh"
#include "wektor.hh"
#include "lacze_do_gnuplota.hh"
using namespace std;

template <int rozmiar>
class Bryla
{
protected:
    vector<Wektor> bryla; // bryla jako tablica dynamiczna(kontener) - vector
    Wektor przesuniecie;  // wektor identyfikujacy odleglosc od srodka ukladu wspolrzednych
    Wektor orientacja;    // wektor identyfikujacy kat obrotu drona
    Wektor punktsymetrii; // wektor identyfikujacy punkt ciezkosci drona
    Wektor katy;          // wektor trzymajacy wartosci karow obrotu wokol si x,y i z

public:
    // operatory indeksujace (dzieki nim mozna operowac na prywatnej czesci klasy)
    Wektor operator[](int Ind) const { return bryla[Ind]; }
    Wektor &operator[](int Ind) { return bryla[Ind]; }
    vector<Wektor> getbryla() const { return bryla; }
    vector<Wektor> &getbryla() { return bryla; }
    Wektor getprzesuniecie() const { return przesuniecie; }
    Wektor &getprzesuniecie() { return przesuniecie; }
    Wektor getorientacja() const { return orientacja; }
    Wektor &getorientacja() { return orientacja; }
    Wektor getpunktsymetrii() const { return punktsymetrii; }
    Wektor &getpunktsymetrii() { return punktsymetrii; }
    Wektor getkaty() const { return katy; }
    Wektor &getkaty() { return katy; }
    //konstruktor ktory dodaje nam okreslona przez rozmiar ilosc wektorow (wierzcholkow)
    Bryla()
    {
        Wektor obiekt;
        obiekt = 0;
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                bryla.push_back(obiekt); //funkcja std::vector
            }
        }
    }
    //metoda sluzaca zapisowi wierzcholkow do pliku
    void Importdopliku(string sciezka) //wpisuje sciezke
    {
        ofstream zapis(sciezka); //tworze plik
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                zapis << bryla[i][j] << " "; //zapisuje w pliku
            }
            zapis << endl;
        }
        zapis.close(); //zamykam plik
    }
    //metoda sluzaca pobraniu wierzcholkow z pliku
    void Eksportzpliku(string plik) //wpisuje sciezke
    {
        ifstream file;
        file.open(plik.c_str()); //otwieram plik
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                file >> bryla[i][j]; //zczytuje z pliku do programu
            }
        }
    }
    //metoda aktualizujaca zorientowanie bryly w osiach XY
    void zorientowanie()
    {
        orientacja = (bryla[1]) - (bryla[0]); //wzgledem dwoch wierzcholkow
        orientacja = orientacja / 20;         //bo bok ma 20
    }
    //metoda zczytujaca najmniejsza wartosc polozenia bryly
    float mini(char tmp)
    {
        float a = 100;
        if (tmp == 'X') //w zaleznoci od X
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = min(bryla[i][0], a); //funkcja <cmath> porownuje dwa obiekty, zwraca mniejszy
            }
        }
        if (tmp == 'Y') //w zaleznoci od Y
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = min(bryla[i][1], a); //funkcja <cmath> porownuje dwa obiekty, zwraca mniejszy
            }
        }

        if (tmp == 'Z') //w zaleznoci od Z
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = min(bryla[i][2], a); //funkcja <cmath> porownuje dwa obiekty, zwraca mniejszy
            }
        }
        return a;
    }
    //metoda zczytujaca najwieksza wartosc polozenia bryly
    float maxi(char tmp)
    {
        float a = -100;
        if (tmp == 'X') //w zaleznoci od X
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = max(bryla[i][0], a); //funkcja <cmath> porownuje dwa obiekty, zwraca wiekszy
            }
        }
        if (tmp == 'Y') //w zaleznoci od Y
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = max(bryla[i][1], a); //funkcja <cmath> porownuje dwa obiekty, zwraca wiekszy
            }
        }
        if (tmp == 'Z') //w zaleznoci od Z
        {
            for (int i = 0; i < rozmiar; i++)
            {
                a = max(bryla[i][2], a); //funkcja <cmath> porownuje dwa obiekty, zwraca wiekszy
            }
        }
        return a;
    }
    //metoda sluzaca do wyznaczenia aktualnego polozenia punktu ciezkosci bryly
    void wyznaczenie_punktu_symetrii()
    {
        punktsymetrii[0] = (mini('X') + maxi('X')) / 2; //srednia najmniejszej i najwiekszej wartosci
        punktsymetrii[1] = (mini('Y') + maxi('Y')) / 2; //srednia najmniejszej i najwiekszej wartosci
        punktsymetrii[2] = (mini('Z') + maxi('Z')) / 2; //srednia najmniejszej i najwiekszej wartosci
    }
    //tworzenie macierzy obrotu wzgledem osi X
    Macierz os_obrotuX(double radian)
    {
        Macierz pom;
        pom[0][0] = 1;
        pom[1][1] = cos(radian);
        pom[1][2] = -1 * sin(radian);
        pom[2][1] = sin(radian);
        pom[2][2] = pom[1][1];

        return pom;
    }
    //tworzenie macierzy obrotu wzgledem osi Y
    Macierz os_obrotuY(double radian)
    {
        Macierz pom;
        pom[0][0] = cos(radian);
        pom[1][1] = 1;
        pom[0][2] = sin(radian);
        pom[2][0] = -1 * sin(radian);
        pom[2][2] = pom[0][0];

        return pom;
    }
    //tworzenie macierzy obrotu wzgledem osi Z
    Macierz os_obrotuZ(double radian)
    {
        Macierz pom;
        pom[0][1] = -1 * sin(radian);
        pom[1][0] = sin(radian);
        pom[1][1] = cos(radian);
        pom[0][0] = pom[1][1];
        pom[2][2] = 1;

        return pom;
    }
    // metoda przesuwajaca bryle (wierzcholki o zadany wektor)
    void przesun(Wektor wektor)
    {
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                bryla[i][j] += wektor[j];
            }
        }
    }
    // metoda obracajaca obryle w zadanym kierunku o zadany kat
    void obrot(Wektor wek, double radian, char os)
    {
        Macierz pom; //tworzenie macierzy z katami
        if (os == 'X')
            pom = os_obrotuX(radian);
        if (os == 'Y')
            pom = os_obrotuY(radian);
        if (os == 'Z')
            pom = os_obrotuZ(radian);

        for (int i = 0; i < 3; i++)
        {
            wek[i] = -1 * wek[i]; //zmiana okrientacji wektora przesuniecia
        }

        przesun(wek); //powrot do (0,0,0)
        for (int i = 0; i < rozmiar; i++)
        {
            bryla[i] = pom * bryla[i]; //zmiana kata
        }

        for (int i = 0; i < 3; i++)
        {
            wek[i] = -1 * wek[i]; //zmiana okrientacji wektora przesuniecia
        }
        przesun(wek);    //powrot do wczesniejszej lokalizacji
        zorientowanie(); //aktualizacja orientacji
    }
    //obrot wirniczkow wokol wlasniej osi, "animacja silnikow"
    void obrotwir()
    {
        Macierz pom; // macierz pomocnicza
        for (int i = 0; i < 3; i++)
        {
            punktsymetrii[i] = -1 * punktsymetrii[i]; //zmiana okrientacji wektora przesuniecia
        }

        przesun(punktsymetrii); //powrot do (0,0,0)
        // pom = os_obrotuZ(-1 * radian);
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
                pom = os_obrotuX(-1 * katy[0]); //powrot do ustawienia pierwotnego wg osi X
            if (i == 1)
                pom = os_obrotuY(-1 * katy[1]); //powrot do ustawienia pierwotnego wg osi Y
            if (i == 2)
                pom = os_obrotuZ(-1 * katy[2]); //powrot do ustawienia pierwotnego wg osi Z
            for (int j = 0; j < rozmiar; j++)
            {
                bryla[j] = pom * bryla[j]; //zmiana kata
            }
        }

        pom = os_obrotuX(katy[0] + 2);
        for (int i = 0; i < rozmiar; i++)
        {
            bryla[i] = pom * bryla[i]; //zmiana kata (animacja)
        }
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
                pom = os_obrotuX(katy[0]); //powrot do ustawienia pierwotnego wg osi X
            if (i == 1)
                pom = os_obrotuY(katy[1]); //powrot do ustawienia pierwotnego wg osi Y
            if (i == 2)
                pom = os_obrotuZ(katy[2]); //powrot do ustawienia pierwotnego wg osi Z
            for (int j = 0; j < rozmiar; j++)
            {
                bryla[j] = pom * bryla[j]; //zmiana kata (animacja)
            }
        }
        for (int i = 0; i < 3; i++)
        {
            punktsymetrii[i] = -1 * punktsymetrii[i]; //zmiana okrientacji wektora przesuniecia
        }
        przesun(punktsymetrii); //powrot do wczesniejszej lokalizacji
        zorientowanie();        //aktualizacja orientacji
    }

    // //funkcja pomagajaca utrzymac porzadek w mainie :)
    Wektor ruch(float odl, double kat)
    {
        Wektor wek_ruchu;           //wektor ruchu, glowny wektor
        Wektor osZ, osY;            //wektor pomocnik, wektor osi Z i XY
        osZ.wektorXYZ(0, 0, 1);     //ustawienie wektora Z = (0,0,0)
        osY = orientacja;           //ustawienie doberj orientacji XY
        kat = (3.14 * kat) / (180); //zmiana na radiany
        float poZ = sin(kat);       //sinus kata, potrzebny do wyliczenia wysokosci wzniosu
        float poY = cos(kat);       //cosinus kata, potrzebny do wyliczenia odleglosci ruchu
        poZ = poZ * odl;            //wyznaczenie dlugosci
        poY = poY * odl;            //wyznaczenie dlugosci

        osZ = osZ * poZ;       //aktualizacja osi Z , pomnozenie razy dlugosc wzniosu
        osY = osY * poY;       //aktualizacja osi XY , pomnozenie razy dlugosc ruchu
        wek_ruchu = osZ + osY; //skladowa osi Z i XY

        return wek_ruchu;
    }
    //metoda "naprawiajaca wspolrzedne po uderzeniu w przeszkode, wazne zeby dron "nie wbił" się
    void napraw()
    {
        Bryla<rozmiar> tmp = Bryla<rozmiar>();
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tmp[i][j] = round(bryla[i][j]); //funkcja <cmath> do zaokraglania
                bryla[i][j] = tmp[i][j];
            }
        }
    }
};

#endif
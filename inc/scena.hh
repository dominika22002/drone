#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "bryla.hh"
#include "zakres.hh"
#include "przeszkoda.hh"
#include "powierzchnia.hh"
#include "dron.hh"
#include "lacze_do_gnuplota.hh"

template <int rozmiar1, int rozmiar2, int rozmiar3, int rozmiar4>
class Scena : public Bryla<rozmiar1 || rozmiar2 || rozmiar3 || rozmiar4>
{
    Dron<rozmiar1, rozmiar4> dron;
    Powierzchnia<rozmiar2> woda;    //bryla wody (statyczna)
    Powierzchnia<rozmiar3> podloze; //bryla podloze (statyczna)
    vector<Przeszkoda<rozmiar1>> przeszkoda;
    PzG::LaczeDoGNUPlota Lacze; //gnuplot

public:
    //metody pozwalajace dostac sie do pliku
    Dron<rozmiar1, rozmiar4> getdron() const { return dron; }
    Dron<rozmiar1, rozmiar4> &getdron() { return dron; }
    Powierzchnia<rozmiar2> getwoda() const { return woda; }
    Powierzchnia<rozmiar2> &getwoda() { return woda; }
    Powierzchnia<rozmiar3> getpodloze() const { return podloze; }
    Powierzchnia<rozmiar3> &getpodloze() { return podloze; }
    vector<Przeszkoda<rozmiar1>> getprzeszkoda() const { return przeszkoda; }
    vector<Przeszkoda<rozmiar1>> &getprzeszkoda() { return przeszkoda; }
    //metoda rysujaca z plikow w gnuplocie
    void rysuj()
    {
        Lacze.Rysuj();
    }

    //konstruktor wywolywany na poczatku programu
    Scena()
    {
        Lacze.ZmienTrybRys(PzG::TR_3D); // Tutaj ustawiany jest tryb 3D
        Lacze.UstawZakresX(-100, 100);  // Tutaj ustawiany jest zakres X
        Lacze.UstawZakresY(-100, 100);  // Tutaj ustawiany jest zakres Y
        Lacze.UstawZakresZ(-30, 100);   // Tutaj ustawiany jest zakres Z
        Lacze.UstawRotacjeXZ(60, 40);   // Tutaj ustawiany jest widok
        Lacze.UsunWszystkieNazwyPlikow();
        Lacze.DodajNazwePliku("bryly/wirnikk1.dat");
        Lacze.DodajNazwePliku("bryly/wirnikk2.dat");
        Lacze.DodajNazwePliku("bryly/powierzchnia.dat");
        Lacze.DodajNazwePliku("bryly/woda.dat");
        Lacze.DodajNazwePliku("bryly/dron1.dat");
    }
    // metoda porowujaca zakresy dwoch dowlonych rzeczy na scenie np. dron i przeszkoda
    int porownajzakresy(Zakres tmp, Zakres pom)
    {
        int a = 0;
        if (((tmp.getx_min() <= pom.getx_min()) &&
             (tmp.getx_max() >= pom.getx_min())) ||
            ((tmp.getx_min() <= pom.getx_max()) &&
             (tmp.getx_max() >= pom.getx_max()))) //jesli wierzcholek jednego mieci się pomiedzy oboma drugiego, to dodaj 1 do a,
        {
            a++;
        }

        if (((tmp.gety_min() <= pom.gety_min()) &&
             (tmp.gety_max() >= pom.gety_min())) ||
            ((tmp.gety_min() <= pom.gety_max()) &&
             (tmp.gety_max() >= pom.gety_max()))) //jesli wierzcholek jednego mieci się pomiedzy oboma drugiego, to dodaj 1 do a,
        {
            a++;
        }
        if (((tmp.getz_min() <= pom.getz_min()) &&
             (tmp.getz_max() >= pom.getz_min())) ||
            ((tmp.getz_min() <= pom.getz_max()) &&
             (tmp.getz_max() >= pom.getz_max()))) //jesli wierzcholek jednego mieci się pomiedzy oboma drugiego, to dodaj 1 do a,
        {
            a++;
        }
        if (a == 3) // jesli a=3 , znaczy ze bylo zderzenie
            return 1;
        return 0;
    }
    //metoda porownujaca zakresy drona i (tu wstaw co chcesz sprawdzic)
    int czykolizja()
    {
        int czykolizja = 0;
        czykolizja = porownajzakresy(podloze.zakres(), dron.zakres()); //kolizyjnosc podloze - dron
        if (czykolizja == 1)
            return 1;
        czykolizja = porownajzakresy(woda.zakres(), dron.zakres()); //kolizyjnosc woda - dron
        if (czykolizja == 1)
            return 2;
        for (int i = 0; i < przeszkoda.size(); i++)
        {
            czykolizja = porownajzakresy(przeszkoda[i].zakres(), dron.zakres()); //kolizyjnosc kazda przeszkoda - dron
            if (czykolizja == 1)
                return 3;
        }
        return 0;
    }
    // metoda opisujaca wypadek
    void co_sie_stalo(int tmp)
    {
        if (tmp == 1)
            cout << " zderzenie z podlozem " << endl;
        if (tmp == 2)
            cout << " wynurzenie drona " << endl;
        if (tmp == 3)
            cout << " zderzenie z przeszkoda " << endl;
    }
    //metoda slurzaca do obrotu drona wokol osi X,Y,Z
    void obracanie(double kat, char a)
    {
        double radian;                      //zmienna pomocnicza do wyznaczania kata
        float zero, jeden, dwa;             // zmienne zapamietujace kat w stopniach w X,Y,Z
        zero = dron.getdron().getkaty()[0]; // przypisanie
        jeden = dron.getdron().getkaty()[1];
        dwa = dron.getdron().getkaty()[2];
        radian = (3.14 * kat) / (180); //zmiana na radiany
        radian = radian / 200;
        //zmiana kata na radiany, a wlasciwie wszystkich czterech
        if (a == 'X')
        {
            dron.getwirnik1().getkaty()[1] = (3.14 * jeden) / 180;
            dron.getwirnik1().getkaty()[2] = (3.14 * dwa) / 180;
            dron.getwirnik2().getkaty()[1] = (3.14 * jeden) / 180;
            dron.getwirnik2().getkaty()[2] = (3.14 * dwa) / 180;
        }
        if (a == 'Y')
        {
            dron.getwirnik1().getkaty()[0] = (3.14 * zero) / 180;
            dron.getwirnik1().getkaty()[2] = (3.14 * dwa) / 180;
            dron.getwirnik2().getkaty()[0] = (3.14 * zero) / 180;
            dron.getwirnik2().getkaty()[2] = (3.14 * dwa) / 180;
        }

        if (a == 'Z')
        {
            dron.getwirnik1().getkaty()[1] = (3.14 * jeden) / 180;
            dron.getwirnik1().getkaty()[0] = (3.14 * zero) / 180;
            dron.getwirnik2().getkaty()[1] = (3.14 * jeden) / 180;
            dron.getwirnik2().getkaty()[0] = (3.14 * zero) / 180;
        }

        for (int i = 0; i < 200 - 1; i++) //petla tworzaca animacje
        {
            if (a == 'X')
            {
                dron.getwirnik1().getkaty()[0] = (3.14 * zero) / 180 + radian * i; //funkcja dodajaca 1/200 kata
                dron.getwirnik2().getkaty()[0] = (3.14 * zero) / 180 + radian * i; //tak, zeby wirniczki podazaly za dronem
            }
            if (a == 'Y')
            {
                dron.getwirnik1().getkaty()[1] = (3.14 * jeden) / 180 + radian * i;
                dron.getwirnik2().getkaty()[1] = (3.14 * jeden) / 180 + radian * i;
            }
            if (a == 'Z')
            {
                dron.getwirnik1().getkaty()[2] = (3.14 * dwa) / 180 + radian * i;
                dron.getwirnik2().getkaty()[2] = (3.14 * dwa) / 180 + radian * i;
            }

            dron.getdron().obrot(dron.getdron().getprzesuniecie(), radian, a); //obracanie drona (inc/bryla.hh)

            dron.getwirnik1().obrot(dron.getdron().getprzesuniecie(), radian, a); //podarzanie za dronem
            dron.getwirnik1().wyznaczenie_punktu_symetrii();                      // wyznaczanie stalego miejsca srodka ciezkosci drona
            dron.getwirnik1().obrotwir();                                         // animacja obrotu silniczkow

            dron.getwirnik2().obrot(dron.getdron().getprzesuniecie(), radian, a); //podarzanie za dronem
            dron.getwirnik2().wyznaczenie_punktu_symetrii();                      // wyznaczanie stalego miejsca srodka ciezkosci drona
            dron.getwirnik2().obrotwir();                                         // animacja obrotu silniczkow

            dron.getdron().Importdopliku("bryly/dron1.dat");       //importowanie nowych danych do pliku
            dron.getwirnik1().Importdopliku("bryly/wirnikk1.dat"); //importowanie nowych danych do pliku
            dron.getwirnik2().Importdopliku("bryly/wirnikk2.dat"); //importowanie nowych danych do pliku
            rysuj();                                               //wyrysowanie nowej sceny
            int czyblad = 0;
            czyblad = czykolizja(); //sprawdzenie kolizyjnosci
            if (czyblad > 0)
            {
                dron.getdron().napraw();    //naprawianie szkod wyrzadzonych przez przeszkode
                dron.getwirnik1().napraw(); //naprawianie szkod wyrzadzonych przez przeszkode
                dron.getwirnik2().napraw(); //naprawianie szkod wyrzadzonych przez przeszkode
                co_sie_stalo(czyblad);
                break;
            }
            // funkcje z biblioteki "chrono" sluzace do opoznienia programu (plynnego przejscia drona)
            chrono::milliseconds timespan(10); //"100" 100 ms to 0,1sek.
            this_thread::sleep_for(timespan);
        }
        //zmiana z radianow na katy
        if (a == 'X')
        {
            dron.getdron().getkaty()[0] = zero + kat;
            dron.getwirnik1().getkaty()[0] = zero + kat;
            dron.getwirnik2().getkaty()[0] = zero + kat;
        }
        if (a == 'Y')
        {
            dron.getdron().getkaty()[1] = jeden + kat;
            dron.getwirnik1().getkaty()[1] = jeden + kat;
            dron.getwirnik2().getkaty()[1] = jeden + kat;
        }
        if (a == 'Z')
        {
            dron.getdron().getkaty()[2] = dwa + kat;
            dron.getwirnik1().getkaty()[2] = dwa + kat;
            dron.getwirnik2().getkaty()[2] = dwa + kat;
        }
    }
    //metoda slurzaca do przesuwania drona i silniczkow
    void poruszanie(float odl, double kat)
    {
        Wektor wek_ruchu;                          //wektor pomocniczy, gdzie zapisany bedzie skonczony wektor ruchu
        wek_ruchu = dron.getdron().ruch(odl, kat); //funkcja do utrzymania porzadku, wyzaczenia wek_ruchu (inc/bryla.hh)
        float zero, jeden, dwa;                    //zmienne pomocnicze, sluzace do zapisania kata w stopniach
        zero = dron.getdron().getkaty()[0];        //przypisanie katow
        jeden = dron.getdron().getkaty()[1];
        dwa = dron.getdron().getkaty()[2];
        dron.getdron().getprzesuniecie() = dron.getdron().getprzesuniecie() + wek_ruchu; //zaaktualizowanie wek_przesuniecia
        dron.getwirnik1().getkaty()[0] = (3.14 * zero) / 180;                            //zamiana katow na radiany
        dron.getwirnik1().getkaty()[1] = (3.14 * jeden) / 180;
        dron.getwirnik1().getkaty()[2] = (3.14 * dwa) / 180;
        dron.getwirnik2().getkaty()[0] = (3.14 * zero) / 180;
        dron.getwirnik2().getkaty()[1] = (3.14 * jeden) / 180;
        dron.getwirnik2().getkaty()[2] = (3.14 * dwa) / 180;
        for (int i = 0; i < 200; i++)
        {
            dron.getdron().przesun(wek_ruchu / 200); //przesuwanie drona (inc/bryla.hh)

            dron.getwirnik1().przesun(wek_ruchu / 200);      // przesuwanie silnikow
            dron.getwirnik1().wyznaczenie_punktu_symetrii(); // wyznaczanie stalego miejsca srodka ciezkosci drona
            dron.getwirnik1().obrotwir();                    // animacja obrotu silniczkow
            dron.getwirnik2().przesun(wek_ruchu / 200);      // przesuwanie silnikow
            dron.getwirnik2().wyznaczenie_punktu_symetrii(); // wyznaczanie stalego miejsca srodka ciezkosci drona
            dron.getwirnik2().obrotwir();                    // animacja obrotu silniczkow

            dron.getdron().Importdopliku("bryly/dron1.dat");       //importowanie nowych danych do pliku
            dron.getwirnik1().Importdopliku("bryly/wirnikk1.dat"); //importowanie nowych danych do pliku
            dron.getwirnik2().Importdopliku("bryly/wirnikk2.dat"); //importowanie nowych danych do pliku
            rysuj();
            int czyblad = 0;        //wyrysowanie nowej sceny
            czyblad = czykolizja(); //sprawdzenie kolizyjnosci
            if (czyblad > 0)
            {
                co_sie_stalo(czyblad);
                dron.getdron().napraw();    //naprawianie szkod wyrzadzonych przez przeszkode
                dron.getwirnik1().napraw(); //naprawianie szkod wyrzadzonych przez przeszkode
                dron.getwirnik2().napraw(); //naprawianie szkod wyrzadzonych przez przeszkode
                break;
            }

            // funkcje z biblioteki "chrono" sluzace do opoznienia programu (plynnego przejscia drona)
            chrono::milliseconds timespan(10); //"100" 100 ms to 0,1sek.
            this_thread::sleep_for(timespan);
        }
        //zamiana radianow na katy
        dron.getwirnik1().getkaty()[0] = zero;
        dron.getwirnik1().getkaty()[1] = jeden;
        dron.getwirnik1().getkaty()[2] = dwa;
        dron.getwirnik2().getkaty()[0] = zero;
        dron.getwirnik2().getkaty()[1] = jeden;
        dron.getwirnik2().getkaty()[2] = dwa;
    }
    //metoda pomocnicza stworzeniu dynamicznej przeszkody
    void nazwa_przeszkody()
    {
        char *nazwa = nullptr;
        string napis = "bryly/przeszkoda";                                      //rozpoczenie wpisywania katalogu gdzie ma znalezc sie plik
        string liczba_porz = to_string(przeszkoda.size());                      //napisanie "ktora to przeskzoda"
        napis += liczba_porz;                                                   // dodalnie jej do nazwy
        napis += ".dat";                                                        //dodanie rozszerzenia pliku
        przeszkoda[przeszkoda.size() - 1].getnazwa() = napis;                   //przypisanie nazwy do przeszkody
        przeszkoda[przeszkoda.size() - 1].getprzeszkoda().Importdopliku(napis); //import wierzcholkow przeszkody do plikow
        int chars_to_reserve = napis.size() + 1;                                //sprawdzenie ile miejsca potrzebuje "nazwa"
        nazwa = new char[chars_to_reserve];                                     //stworzenie dynamicznej pamieci dla napisu
        strcpy(nazwa, napis.c_str());                                           //zmiana stringa na char* (potrzebne gnuplotowi)
        Lacze.DodajNazwePliku(nazwa);                                           //dodanie nazwy do gnuplota
    }
    //dodawanie nowej przeszkody do programu
    void dodaj_przeszkode()
    {
        float x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0, x = 0, y = 0, z = 0;
        cout << "wpisz dlugosc boku x ,y ,z" << endl;
        cin >> x >> y >> z;
        cout << " wpisz wspolrzedne miejsca rozpoczecia przeszkody " << endl;
        cin >> x1 >> y1 >> z1;
        x2 = x1 + x;
        y2 = y1 + y;
        z2 = z1 + z;

        Przeszkoda<rozmiar1> obiekt = Przeszkoda<rozmiar1>();
        obiekt.tworzprzeszkode(x1, x2, y1, y2, z1, z2); //funkcja tworzaca przeszkode
        przeszkoda.push_back(obiekt);                   //pchniecie jej na wektor przeszkod
        nazwa_przeszkody();                             //stworzenie nazwy i dodanie jej do gnuplota

        rysuj();
    }
};

#endif
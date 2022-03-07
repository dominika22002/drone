#include <iostream>
#include <iomanip>
#include <cmath>

#include <thread>
#include <chrono>

#include "lacze_do_gnuplota.hh"
#include "przeszkoda.hh"
#include "bryla.hh"
#include "scena.hh"
#include "zakres.hh"
#include "powierzchnia.hh"
#include "dron.hh"

using namespace std;

int main()
{
  Dron<20, 33> dron = Dron<20, 33>();
  char wybor = '\0';
  PzG::LaczeDoGNUPlota Lacze;                                        //lacze do gnupolta
  Lacze.Inicjalizuj();                                               //otwieranie gnuplota
  Scena<20, 43, 25, 33> scena = Scena<20, 43, 25, 33>();             //inicjalizowanie sceny (dron, podloze, woda)
  Wektor wek_przesuniecia;                                           //wazny wektor, pozniej scena.getdron().getprzesuniecie()
  scena.getpodloze().Eksportzpliku("bryly/powierzchnia.dat");        //tworzenie podloza
  scena.getwoda().getpowierzchnia().Eksportzpliku("bryly/woda.dat"); //tworzenie wody
  scena.getpodloze().getpowierzchnia().Eksportzpliku("bryly/powierzchnia.dat");
  scena.getdron().getdron().Eksportzpliku("bryly/dron2.dat");
  scena.getdron().getdron().Importdopliku("bryly/dron1.dat"); //tworzenie nowego pliku na ktorym bede dzialac
  scena.getdron().getwirnik1().Eksportzpliku("bryly/wirnik11.dat");
  scena.getdron().getwirnik1().Importdopliku("bryly/wirnikk1.dat");
  scena.getdron().getwirnik2().Eksportzpliku("bryly/wirnik22.dat");
  scena.getdron().getwirnik2().Importdopliku("bryly/wirnikk2.dat");
  scena.getdron().getdron().zorientowanie(); //wazne! natychmiastowe zorientowanie drona w przestrzeni
  scena.getdron().getwirnik1().zorientowanie();
  scena.getdron().getwirnik2().zorientowanie();

  // scena.getdron().ossymm();
  scena.rysuj(); //odpalenie gnuplota na ekranie, wyrysowanie sceny
  //menu wyboru wbudowanej sceny
  cout << "\n\nCzy chcesz wyrysowac przeszkody sam?" << endl;
  cout << "Stworzona zostanie wtedy przykladowa scena" << endl;
  cout << "w przyszlosci bedziesz mogl dodawac przeszkody sam " << endl;
  cout << "s - stworz przeszkody sam" << endl;
  cout << "w - wczytaj przykladowa scena" << endl;
  cin >> wybor;
  while (wybor != 'k')
  {
    if (wybor == 's')
    {
      while (wybor != 't')
      {
        scena.dodaj_przeszkode();
        cout << "\n\nczy skonczyles tworzyc scene?" << endl;
        cout << "t - tak, przechodze do sterowanai dronem" << endl;
        cout << "n - nie, chce dodac nastepna przeszkode " << endl;
        cin >> wybor;
        while (wybor != 't' && wybor != 'n')
        {
          cout << "zla komenda" << endl;
          cin >> wybor;
        }
      }
    }
    if (wybor == 't')
    {
      wybor = 'k';
    }

    if (wybor == 'w')
    {
      Przeszkoda<20> obiekt = Przeszkoda<20>();

      obiekt.tworzprzeszkode(80, 85, -90, 10, 0, 40);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(70, 90, 70, 90, -15, 65);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-90, -40, -90, -40, -20, -10);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-80, 0, 80, 87, 70, 77);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-80, 0, 80, 87, 30, 37);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-80, 0, 80, 87, -10, -3);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      obiekt.tworzprzeszkode(-90, -80, -90, -20, 20, 70);
      scena.getprzeszkoda().push_back(obiekt);
      scena.nazwa_przeszkody();
      scena.rysuj();
      cout << "\n\nprzeszkody zostaly wczytane" << endl;
      wybor = 'k';
    }
    if (wybor != 's' && wybor != 'w' && wybor != 'k' && wybor != 't')
    {
      cout << "zla komenda" << endl;
      cin >> wybor;
    }
  }

  //menu
  cout << "r - zadaj ruch na wprost " << endl;
  cout << "o - zadaj zmiane orientacji " << endl;
  cout << "p - dodaj przeszkode " << endl;
  cout << "m - wyswietl menu" << endl;
  cout << "k - koniec dzialania programu" << endl;
  cin >> wybor;

  while (wybor != 'k') //petla ograniczona literka 'k'
  {
    switch (wybor)
    {
    case 'r': //ruch na wprost (ew. do tylu)
    {
      cout << "Podaj wartosc odleglosci, na ktora ma sie przemiescic dron. \n\tWartosc odleglosci:  ";
      float odl;
      cin >> odl;
      cout << "Podaj wartosc kata (wznoszenia/opadania) w stopniach. \n\tWartosc kata:  ";
      float kat;
      cin >> kat;
      char a = 'Z';
      scena.poruszanie(odl, kat); //funkcja w scena.hh

      break;
    }

    case 'o': //obrot wokol osi Z
    {
      double kat = 0;
      cout << "Wpisz kat obrotu \n";
      cin >> kat;
      char a = '\0';
      cout << "Wpisz os obrotu \n";
      cin >> a;

      scena.obracanie(kat, a); //funkcja w scena.hh

      break;
    }
    case 'm': //menu
      cout << "r - zadaj ruch na wprost " << endl;
      cout << "o - zadaj zmiane orientacji " << endl;
      cout << "p - dodaj przeszkode " << endl;
      cout << "m - wyswietl menu" << endl;
      cout << "k - koniec dzialania programu" << endl;

      break;
    case 'p':
    {
      scena.dodaj_przeszkode();
      break;
    }
    case 'k': //koniec dzialania programu
      return 0;
    default:
      cout << "Zla komenda, wpisz jeszcze raz." << endl;
      break;
    }
    cin >> wybor;
  }
  return 0;
}
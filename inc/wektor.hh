#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
//klasa wektora x3 (x,y,z)
class Wektor
{
  float wektor[3]; //zmienna float

public:
//konstruktor
  Wektor()
  {
    for (int i = 0; i < 3; i++)
      wektor[i] = 0;
  }
  // operatory indeksujace (dzieki nim mozna operowac na prywatnej czesci klasy)
  float operator[](int Ind) const { return wektor[Ind]; }
  float &operator[](int Ind) { return wektor[Ind]; }

  // metoda wpisujaca okreslony wektor
  void wektorXYZ(float x, float y, float z)
  {
    wektor[0] = x;
    wektor[1] = y;
    wektor[2] = z;
  }
//przeciazenie operatora przyrowanania
  void operator=(float tmp)
  {
    for (int i = 0; i < 3; i++)
    {
      wektor[i] = tmp;
    }
  }
};
// przeciazenie operatora wyjscia 
std::ostream &operator<<(std::ostream &strm, const Wektor &wektor)
{
  for (int i = 0; i < 3; i++)
  {
    strm << wektor[i] << " ";
  }
  strm << endl;
  return strm;
}
// przeciazenie operatora wejscia
std::istream &operator>>(std::istream &strm, Wektor &wektor)
{
  for (int i = 0; i < 3; i++)
  {
   cin >> wektor[i];
  }
  return strm;
}
// przeciazenie operatora mnozenia wektor*wektor skalarnie
float operator*(Wektor pom, Wektor tmp)
{
  float k, j;
  k = 0;
  j = 0;
  for (int i = 0; i < 3; i++)
  {
    j = pom[i] * tmp[i];
    k = k + j;
  }
  return k;
}
// przeciazenie operatora dzielenia wektora przez zmienna
Wektor operator/(Wektor tmp, double zmienna)
{
  Wektor wynik;
  for (int i = 0; i < 3; i++)
  {
    wynik[i] = tmp[i] / zmienna;
  }
  return wynik;
}
// przeciazenie operatora dodawania wektorow
Wektor operator+(Wektor pom, Wektor tmp)
{
  Wektor wynik;
  for (int i = 0; i < 3; i++)
  {
    wynik[i] = pom[i] + tmp[i];
  }
  return wynik;
}
// przeciazenie operatora mnozenia wektor*zmienna
Wektor operator*( Wektor tmp, double zmienna)
{
  Wektor wynik;
  for (int i = 0; i < 3; i++)
  {
    wynik[i] = zmienna * tmp[i];
  }
  return wynik;
}
// przeciazenie operatora odejmowania wektorow
Wektor operator-( Wektor tmp, Wektor pom)
{
  Wektor wynik;
  for (int i = 0; i < 3; i++)
  {
    wynik[i] = tmp[i] - pom[i];
  }
  return wynik;
}


#endif
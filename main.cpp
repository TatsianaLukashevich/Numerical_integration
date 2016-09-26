#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <math.h>

using namespace std;

int n;                      /*stopien wielomianu*/
double *tab_a;              /*tablica wspolczynnikow przy wielomianie*/
double k;                   /*poczatek przedzialu calkowania*/
double l;                   /*koniec przedzialu calkowania*/
int s;                      /*liczba podprzedzialow*/
double suma;                /*wynik calkowania*/

/*
 *Funkcja pomagająca sprawdziić wprowadzone dane
 */
bool sprawdz(string, int);

int main()
{

void wpisz_stopien();
void wpisz_wspol();
void wpisz_pocz();
void wpisz_koniec();
void wpisz_liczbprzed();
double oblicz_calke();


wpisz_stopien();
wpisz_wspol();
wpisz_pocz();
wpisz_koniec();
wpisz_liczbprzed();

suma = oblicz_calke();

cout << "Obliczona calka " << suma << endl;

delete [] tab_a;
tab_a = NULL;


    return 0;
}
/*
 *Funkcja obliczjaca calke za pomoca metody Simpsona
 *@return suma wartość obliczonej całki
 */
double oblicz_calke()
{

    int alfa =0;           /*licznik pomagajacy w przesuwaniu po tablice wartości funkcji*/
    double pom;         /*zmienna pomocnicza, pomagająca w zamianie miejscami przedzialow calkowania*/
    double st = 0;      /*stopien przy -1, jesli roznica przedzialow jest dodatnia, to st = 0, jesli nie st=1*/
    double potega = 0;  /*stopien przy wielomianie*/

    double a;           /*wartosc (-1)^st*/
    double h;           /*krok*/
    double sum;         /*suma wszystkich wartosci funkcji ze wzoru Simpsona dla konkretnego wielomianu*/

   if( l < k )          /*sprawdzamy przedzial*/
    {
        pom = k;
        k = l;
        l = pom;
        st = 1;
    }

    h = (l - k)/(2*s);  /*liczymy krok*/

    while(potega <= n)  /*obliczmy calke dla konkretnego wielomianu, nastepnie dodjemy do wspolnej sumy*/
    {
    double *x = new double [2*s];   /*tabela wartosci x*/
    double *fx = new double [2*s];  /*tabela wartosci funkcji fx*/
    double sumparz = 0;             /*suma wartosci funkcji o parzystych indeksach*/
    double sumnieparz = 0;          /*suma wartosci funkcji o nieparzystych indeksach*/

/*obliczmy wartosci x i fx i zapisujemy do tabeli*/
       for(int i = 0; i<= 2*s; i++)
        {
            x[i] = k + i*h;
            fx[i] = pow(x[i], potega);
        }

/*obliczmy sume funkcji o nieparzystych indeksach*/
        for(int i = 1; i <= s; i++)
        {
            alfa = (2*i - 1);
            sumnieparz += fx[alfa];
        }
        alfa = 0;

/*obliczmy sume funkcji o parzystych indeksach*/
        for(int i = 1; i <= (s-1); i++)
        {
            alfa = 2*i;
            sumparz += fx[alfa];
        }

        a = pow(-1,st);     /*wrtosc (-1)^st*/
        alfa = potega;      /*podstawiamy potege wielomiana dla znalezienia wspolczynnika wielomiana w tab_a*/

        /*wzor simpsona*/
        sum = a*(h/3)*(tab_a[alfa])*(fx[0] + 4*sumnieparz + 2*sumparz + fx[2*s]);

        suma+=sum;  /*dodajemy do wspolnej sumy*/


    delete [] x;
    x = NULL;
   delete [] fx;
    fx= NULL;
        potega++;
   }

  return suma;  /*obliczona calka*/
}
/*
 *Funkcja za pomoca ktorej wpisujemy stopien wielomiana
 */

void wpisz_stopien()
{
string str;
bool check = false;


cout << "Wpisz stopien" << endl;
while(1)
{
    getline (cin, str);         /*pobierz string*/
    check = sprawdz(str, 1);    /*sprawdz czy poprawne dane*/
    if(check==true)
        break;
    cout << "Niepoprawny stopien! Wpisz ponownie" << endl;
}

stringstream(str) >> n;         /*przeksztalcamy na liczbe*/
}

/*
 *Funkcja za pomoca ktorej wpisujemy wspolczynniki wielomiana
 */
void wpisz_wspol()
{
tab_a= new double [n];  /*tablica wspolczynnikow przy wielomianach*/
bool check = false;
string str;


    for (int i = 0; i <= n; i++)
    {
        cout<< "Wpisz wspolczynnik przy " << i << " stopniu wielomianu" << endl;
            while(1)
            {
                getline (cin, str);
                check = sprawdz(str, 2);
                if(check==true)
                break;
                cout << "Niepoprawny wspolczynnik! Wpisz ponownie" << endl;
            }
        stringstream(str) >> tab_a[i];
    }
}
/*
 *Funkcja za pomoca ktorej wpisujemy poczatek przedzialu calkowania
 */
void wpisz_pocz()
{

string str;
bool check = false;


cout << "Wpisz poczatek przedzialu" << endl;
while(1)
{
    getline (cin, str);
    check = sprawdz(str, 2);
    if(check==true)
        break;
    cout << "Niepoprawny poczatek przedzialu! Wpisz ponownie" << endl;
}

stringstream(str) >> k;
}
/*
 *Funkcja za pomoca ktorej wpisujemy koniec przedzialu calkowania
 */
void wpisz_koniec()
{

string str;
bool check = false;


cout << "Wpisz koniec przedzialu" << endl;
while(1)
{
    getline (cin, str);
    check = sprawdz(str, 2);
    if(check==true)
        break;
    cout << "Niepoprawny koniec przedzialu! Wpisz ponownie" << endl;
}

stringstream(str) >> l;
}
/*
 *Funkcja za pomoca ktorej wpisujemy liczbe podprzedzialow calkowania
 */
void wpisz_liczbprzed()
{
string str;
bool check = false;


cout << "Wpisz liczbe podprzedzialow" << endl;
while(1)
{
    getline (cin, str);
    check = sprawdz(str, 1);
    if(check==true)
        break;
    cout << "Niepoprawna liczba przedzialow! Wpisz ponownie" << endl;
}

stringstream(str) >> s;
}
/*
 *Funkcja pomagająca sprawdziić wprowadzone dane
 *@param str przyjmuje wprowadzony string z klawiatury
 *       numer wybieramy sposob sprawdzania
 *@return jesli zwroci false,to znaczy, ze wprowadzilismy niepoprawne dane
 *        jesli zwroci true, to poprawne dane
 */
bool sprawdz(string str, int numer)
{
    bool kropka = false; /*zmienna pomocnicza, pozwalajaca wyjawnic czy wystapila kropka czy nie*/

/*jesli sprawdzamy wedlug 1-go sposobu, to sprawdzamy tylko czy jest to liczba*/
    if(numer == 1)
    {
        for (int i = 0; i < str.size() && str[i] != '\n'; i++)
        {
            if(!isdigit(str[i])) /*jesli nie liczba*/
                return false;
        }
        return true;
    }

/*jesli sprawdzamy wedlug 2-go sposobu, to sprawdzamy tylko czy jest to liczba i czy jest, to liczba typu double.
 * Przyjmujemy znaki
 */
    if (numer == 2)
    {
    if( !(str[0] == '-' || isdigit(str[0])) ) /*jesli nie znak i nie liczba*/
        return false;

    for (int i = 1; i < str.size() && str[i] != '\n'; i++)
    {
        if(!isdigit(str[i]))
        {
            if((str[i] == '.') && kropka == false) /*jesli wystapila pierwszy raz kropka*/
                kropka = true;
            else
                return false;
        }
    }
    return true;
    }
}

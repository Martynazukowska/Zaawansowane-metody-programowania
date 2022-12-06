#ifndef TESTY
#define TESTY

#include <map>
#include <memory>
#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <fstream>
#include <vector>
#include "InterfaceVector.hh"
#include "Poczatek.hh"

using namespace std;


class Testy
{
private:
    InterfaceVector Lib;
    Interp4Command *wskazik=nullptr;
    Interp4Command *wskazik1=nullptr;
    Interp4Command *wskazik2=nullptr;
    Interp4Command *wskazik3=nullptr;
public:
    Testy();
    ~Testy();
    void Czytwanie_wartości_wtyczek();
    void Wskazniki_i_wartosci();
    void Czytaj_pierwsze_zpliku(istringstream &file);
    void Cytaj_XML(Poczatek podawany);
    
};

#endif
#include "De.h"
#include <cstdlib>
#include <ctime>
using namespace std;

De::De() { srand(time(nullptr)); }

De::~De() { }

int De::lancer() 
{ 
    valeur = rand()% 12 + 1;
    return valeur;
}

int De::getValeur() const
{
    return valeur;
}
#include "Plateau.h"
#include "Case.h"
#include "Propriete.h"
#include "Joueur.h"
#include "Banque.h"
#include "Carte.h"
#include "JeuTXT.h" 
#include <iostream>

using namespace std;



int main()
{
    /* Case::TestRegression();
    Plateau::TestRegression();
    Propriete::testRegression();
    Joueur::TestRegression();
    Banque::TestRegression();
    Carte::TestRegression();
    Jeu::TestRegression();
    JeuTXT::TestRegression(); */
    JeuTXT jeu;
    jeu.lancerPartie();
    return 0;
}
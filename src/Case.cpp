#include "Case.h"

#include "Banque.h"

#include "Joueur.h"

#include <iostream>
#include <cassert>
using namespace std;

Case::Case() {
    nom = "CaseDefauts";
    positionC = 0;
    Pr = nullptr;
}

Case::Case(string n, int posC) {
    nom = n;
    positionC = posC;
    Pr = nullptr;
}

Case::~Case() { }

void Case::appliquerEffet(Joueur* j, Banque& banque) {

    if (positionC == 30) 
    {
        cout << "Vous êtes tomber sur la case Allez en Rattrapages. Vous allez tout droit sur la case rattrapage." << endl;
        j->allerEnPrison();
    }  

    if (nom == "Partiel Surprise") {
        cout << "Partiel surprise : payez 200£" << endl;
        banque.recevoirJoueur(j, 200);
    }
    else if (nom == "CVEC") {
        cout << "Vous devez payer la CVEC : 150£" << endl;
        banque.recevoirJoueur(j, 150);
    }
}


string Case::getNom() const {
    return nom;
}

int Case::getPos() const {
    return positionC;
}

void Case::setPropriete(Propriete* p) { Pr = p; }
Propriete* Case::getPropriete() const { return Pr; }


void Case::TestRegression() {
    cout << "=== TestRegression Case ===" << endl;

    Case c1;
    cout << "Nom c1: " << c1.getNom() << ", Pos: " << c1.getPos() << endl;
    assert(c1.getNom() == "CaseDefauts"); 
    assert(c1.getPos() == 0);

    Case c2("Cheval", 1);
    cout << "Nom c2: " << c2.getNom() << ", Pos: " << c2.getPos() << endl;
    assert(c2.getNom() == "Cheval"); 
    assert(c2.getPos() == 1);

    Case c3("Prison", 10);
    cout << "Nom c3: " << c3.getNom() << ", Pos: " << c3.getPos() << endl;
    assert(c3.getNom() == "Prison");
    assert(c3.getPos() == 10);

    cout << "Tous les tests de regression Case ont reussi !" << endl;
}
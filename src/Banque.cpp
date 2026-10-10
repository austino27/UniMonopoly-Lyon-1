#include "Banque.h"
#include <iostream>
#include <cassert>

using namespace std;

Banque::Banque() {
    argentBanque = 100000; // banque infinie pour simplifier
}

Banque::~Banque() {}

int Banque::getArgentBanque() const {
    return argentBanque;
}

void Banque::payerJoueur(Joueur* joueur, int montant) {
    if (joueur != nullptr && montant > 0) {
        joueur->recevoir(montant);
        argentBanque -= montant;

        cout << "La banque donne " << montant 
             << " crédits à " << joueur->getNom() << endl;
    }
}

void Banque::recevoirJoueur(Joueur* joueur, int montant) {
    if (joueur != nullptr && montant > 0) {
        joueur->payer(montant);
        argentBanque += montant;

        cout << joueur->getNom() 
             << " paie " << montant << " crédits à la banque" << endl;
    }
}

bool Banque::verifierArgent(Joueur* j, int montant) {
    if (!j) return false; // sécurité si pointeur nul
    return j->getArgent() >= montant;
}

void Banque::TestRegression() {

    cout << "=== TestRegression Banque ===" << endl;

    Joueur j("Zizou");
    Banque b;

    int argentInitial = j.getArgent();

    b.payerJoueur(&j, 200);
    assert(j.getArgent() == argentInitial + 200);

    b.recevoirJoueur(&j, 100);
    assert(j.getArgent() == argentInitial + 100);

    cout << "Tous les tests Banque ont reussi !" << endl;
}
#include "Carte.h"
#include <iostream>
#include <cassert>
using namespace std;

Carte::Carte() : description("CarteDefaut"), effet(0), type(ARGENT) {}
Carte::Carte(string desc, int eff, TypeCarte t) : description(desc), effet(eff), type(t) {}
Carte::~Carte() {}

void Carte::appliquerEffet(Joueur& j, Banque& banque) {
    switch(type) {
        case ARGENT: {
            if(effet >= 0) {
                cout << j.getNom() << " reçoit " << effet << "€." << endl;
                banque.payerJoueur(&j, effet);
            } else {
                cout << j.getNom() << " paie " << -effet << "€." << endl;
                banque.recevoirJoueur(&j, -effet);
            }
            break;
        }

        case DEPLACEMENT: {
            int posAvant = j.getPosition();
            j.deplacer(effet, 40);
            if (effet >= 0)
                cout << j.getNom() << " avance de " << effet 
                 << " cases : " << posAvant << " -> " << j.getPosition() << endl;
            else
                cout << j.getNom() << " recule de " << -effet 
                 << " cases : " << posAvant << " -> " << j.getPosition() << endl;
            break;
        }

        case PRISON: {
            j.allerEnPrison();
            break;
        }

        case LIBERATION: {
            j.setCarteLiberation(true);
            cout << j.getNom() << " reçoit une carte Libération !" << endl;
            break;
        }

        case AVANTAGE: {
            cout << j.getNom() << " bénéficie d'un avantage !" << endl;
            break;
        }

        default:
            cout << "Type de carte inconnu." << endl;
    }
}

const string Carte::getDescription() const { return description; }

const Carte& Carte::getCarte() const { return *this; }

void Carte::TestRegression() {
    cout << "=== TestRegression Carte ===" << endl;
    Banque banque;
    Joueur j("Alice", 1);
    Carte c1("Gain", 200, ARGENT);
    int argentAvant = j.getArgent();
    c1.appliquerEffet(j,banque);
    assert(j.getArgent() == argentAvant + 200);
    Carte c2("Perte", -100, ARGENT);
    argentAvant = j.getArgent();
    c2.appliquerEffet(j,banque);
    assert(j.getArgent() == argentAvant - 100);
    Carte c3("Avance", 5, DEPLACEMENT);
    int posAvant = j.getPosition();
    c3.appliquerEffet(j,banque);
    assert(j.getPosition() == (posAvant + 5) % 40);
    cout << "Tests Carte OK!" << endl;
}
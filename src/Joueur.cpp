#include "Joueur.h"
#include "Propriete.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <limits> 
using namespace std;

// Constructeurs
Joueur::Joueur() 
    : tourJoueur(false), nom("Joueur"), idJoueur(0), argent(1500), position(0), prison(false) , carteLiberation(false), nb_tour_prison(0)
    {
        proprietes = vector<Propriete*>();
    }

Joueur::Joueur(string n) 
    : tourJoueur(false), nom(n), idJoueur(0), argent(1500), position(0), prison(false) , carteLiberation(false), nb_tour_prison(0) {}

Joueur::Joueur(string n,int id) 
    :  tourJoueur(false), nom(n), idJoueur(id), argent(1500), position(0), prison(false) , carteLiberation(false), nb_tour_prison(0) {}

Joueur::~Joueur() { }

void Joueur::deplacer(int nombreCases, int taillePlateau) {
    if (prison) {
        cout << nom << " est en prison et ne peut pas se déplacer." << endl;
        return;
    }
    position = (position + nombreCases + taillePlateau) % taillePlateau;
}

void Joueur::reculer(int nbCases, int taillePlateau) {
    if (prison) {
        cout << nom << " est en prison et ne peut pas se déplacer." << endl;
        return;
    }
    position = (position - nbCases + taillePlateau) % taillePlateau;
}

/*
void Joueur::payer(int montant) {
    argent -= montant;
    if (argent < 0) argent = 0;
}
*/

//Version avec argent négatif
void Joueur::payer(int montant) {
    argent -= montant;

    cout << nom << " paie " << montant << " crédits." << endl;
    cout << "Argent restant: " << argent << endl;

    if (argent < 0) {
        cout << nom << " est en faillite !" << endl;
    }
}


void Joueur::recevoir(int montant) {
    argent += montant;
}

//Gestion de la faillite
bool Joueur::estEnFaillite() const {
    return argent < 0;
}

void Joueur::libererProprietes() {
    for (auto p : proprietes) {
        p->setProprietaire(nullptr);
    }
    proprietes.clear();
}


void Joueur::ajouterPropriete(Propriete* p) {
    proprietes.push_back(p);
}

void Joueur::vendrePropriete(Propriete* p) {
    for(size_t i = 0; i < proprietes.size(); ++i) {
        if(proprietes[i] == p) 
        {
            proprietes.erase(proprietes.begin() + i);
            break;
        }
    }
}

vector<Propriete*> Joueur::getProprietes() const {
    return proprietes;
}

Propriete* Joueur::IemePropriete(int i) {
    if (i < 0 || i >= (int)proprietes.size()) return nullptr;

    Propriete* p = proprietes[i];
    proprietes.erase(proprietes.begin() + i);
    return p;
}

// Gestion Monopole

int Joueur::NbServicesPubliques() const
{
    int nbServicesPubliques = 0;
    for (size_t i = 0; i < proprietes.size(); i++) {
        if (proprietes[i]->getType() == ServicePublique ) {
            nbServicesPubliques ++ ;
        }
    }
    return nbServicesPubliques;
}


int Joueur::NbGarePoceder() const 
{
    int nbgares = 0;
    for (size_t i = 0; i < proprietes.size(); i++) {
        if (proprietes[i]->getType() == Gares) {
            nbgares ++ ;
        }
    }
    return nbgares;
}

bool Joueur::estMonopole() const 
{
    vector<Propriete*> groupes[8];

    for (size_t i = 0; i < proprietes.size(); i++) {
        if (proprietes[i]->getType() == Propr) {
            groupes[proprietes[i]->getCouleur()].push_back(proprietes[i]);
        }
    }

    for (int c = 0; c < 8; c++) {

        int taille_attendue;

        if (c == MARRON || c == BLEUFONCE)
            taille_attendue = 2;
        else
            taille_attendue = 3;

        if ((int)groupes[c].size() == taille_attendue)
            return true;
    }

    return false;
}


vector<Propriete*> Joueur::getMonopole() const 
{
    vector<Propriete*> groupes[8];

    // Remplissage
    for (size_t i = 0; i < proprietes.size(); i++) {
        if (proprietes[i]->getType() == Propr) {
            Couleur c = proprietes[i]->getCouleur();
            groupes[c].push_back(proprietes[i]);
        }
    }

    vector<Propriete*> resultat;

    // Vérification des monopoles
    for (int c = 0; c < 8; c++) {

        int taille_attendue;

        if (c == MARRON || c == BLEUFONCE)
            taille_attendue = 2;
        else
            taille_attendue = 3;

        if ((int)groupes[c].size() == taille_attendue) {
            for (size_t i = 0; i < groupes[c].size(); i++) {
                resultat.push_back(groupes[c][i]);
            }
        }
    }

    return resultat;
}


// Prison
bool Joueur::estEnPrison() const { return prison; }

void Joueur::allerEnPrison() {
    int choix;
    setNbTourPrison(0);

    // Si le joueur a une carte libération
    if (carteLiberation) {
        while (true) {
            cout << "Vous possédez une carte Libération.\n";
            cout << "1. Utiliser la carte pour éviter la prison\n";
            cout << "2. Ne pas utiliser la carte\n";
            cout << "Votre choix : ";

            cin >> choix;

            // Gestion des erreurs de saisie
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Entrée invalide ! Veuillez entrer un nombre.\n";
                continue;
            }

            if (choix == 1) {
                cout << nom << " utilise sa carte Libération et évite la prison !" << endl;
                carteLiberation = false;
                return;
            } 
            else if (choix == 2) {
                cout << nom << " n'utilise pas sa carte." << endl;
                break;
            } 
            else {
                cout << "Choix invalide ! Veuillez choisir 1 ou 2.\n";
            }
        }
    }

    
    cout << nom << " est envoyé en prison !" << endl;
    prison = true;
    position = 10;
}

void Joueur::libererPrison() { prison = false; }

// Accesseurs

void Joueur::setNbTourPrison(int n) { nb_tour_prison = n ;}

void Joueur::setCarteLiberation(bool valeur) {
    carteLiberation = valeur;
}
bool Joueur::getCarteLiberation() const {
    return carteLiberation;
}

const int Joueur::getNbTourPrison() const { return nb_tour_prison; }
int Joueur::getArgent() const { return argent; }
int Joueur::getPosition() const { return position; }
void Joueur::setPosition(int p) { position = p ;}
string Joueur::getNom() const { return nom; }


// Test de régression
void Joueur::TestRegression() {
    cout << "=== TestRegression Joueur ===" << endl;

    Joueur j1("Alice");
    assert(j1.getNom() == "Alice");
    assert(j1.getArgent() == 1500);
    assert(j1.getPosition() == 0);
    assert(!j1.estEnPrison());

    j1.deplacer(5, 40);
    assert(j1.getPosition() == 5);

    j1.reculer(3, 40);
    assert(j1.getPosition() == 2);

    j1.payer(500);
    assert(j1.getArgent() == 1000);

    j1.recevoir(200);
    assert(j1.getArgent() == 1200);

    j1.allerEnPrison();
    assert(j1.estEnPrison());

    j1.libererPrison();
    assert(!j1.estEnPrison());

    Case c1("blabla1",1);
    Case c2("blabla2",1);
    Case c3("blabla3",1);
    Propriete* p1 = new Propriete(&c1, 0, 0, 0, Propr, ROSE);
    Propriete* p2 = new Propriete(&c2, 0, 0, 0, Propr, ROSE);
    Propriete* p3 = new Propriete(&c3, 0, 0, 0, Propr, ROSE);
    
    j1.ajouterPropriete(p1);
    j1.ajouterPropriete(p2);
    j1.ajouterPropriete(p3);

    bool Monop = j1.estMonopole();
    cout << "Alice à un monopole : " << Monop << endl;
    
    vector<Propriete*> monos = j1.getMonopole();
    cout << "Monopoles :" << endl;
    cout << monos << endl;
    cout << "Tous les tests de Joueur ont reussi !" << endl;
}


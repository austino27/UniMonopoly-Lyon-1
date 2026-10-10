#include "Propriete.h"
#include <iostream>
#include <cassert>
using namespace std;

Propriete::Propriete()
{
    prix = 0;
    proprietaire = nullptr;
}

Propriete::Propriete(Case* c, int p, int loy, int niv, TypePropriete typeP, Couleur couleurP)
    : c(c),
      prix(p),
      loyer(loy),
      niveau(niv),
      proprietaire(nullptr),
      TypeP(typeP),
      couleurP(couleurP),
      hypotheque(false)
{
}

Propriete::Propriete(Case* c, int p, int loy, int niv, TypePropriete typeP)
    : c(c),
      prix(p),
      loyer(loy),
      niveau(niv),
      proprietaire(nullptr),
      TypeP(typeP),
      hypotheque(false)
{
}

Propriete::~Propriete() { }


int Propriete::getNiveau() const { return niveau; }
Joueur* Propriete::getProprietaire() const { return proprietaire; }
int Propriete::getPrix() const { return prix; }
Case* Propriete::getCase() const { return c ;}
int Propriete::getLoyer() const { return loyer; }
Couleur Propriete::getCouleur() const { return couleurP ; }
TypePropriete Propriete::getType() const { return TypeP ; }
bool Propriete::estHypotheque() const { return hypotheque; }


//Gestion de la faillite
void Propriete::setProprietaire(Joueur* j) {
    proprietaire = j;
}

void Propriete::hypothequer()
{
    if(niveau>1)
    {
        cout << "Vous ne pouvez pas hypothéquer une propriétée avec des maisons dessus !" << endl;
        return;
    }
    proprietaire->recevoir(prix/2);
    hypotheque=true;
}


void Propriete::leverHypotheque()
{
    if(!hypotheque)
    {
        return;
    }

    int prixLeverHypotheque = (prix / 2) + (prix / 10);
    if (proprietaire->getArgent() < prixLeverHypotheque) {
        cout << "Pas assez d'argent pour lever l'hypothèque." << endl;
        return;
    }
    proprietaire->payer(prixLeverHypotheque);
    hypotheque = false;
    cout << "L'hypothèque sur " << c->getNom() << " est levé." << endl;
}

/*
void Propriete::acheter(Joueur* j) {
    if(!proprietaire) {
        proprietaire = j;
        cout << c->getNom() << " achetée par " << j->getNom() << " pour " << prix << " crédits." << endl;
        j->payer(prix);
        j->ajouterPropriete(this);
    }
}
*/

//Version avec verification argent joueur 
void Propriete::acheter(Joueur* j) {
    if (!proprietaire) {

        if (j->getArgent() < prix) {
            cout << "Pas assez d'argent !" << endl;
            return;
        }

        cout << j->getNom() << " avait " << j->getArgent() << endl;

        proprietaire = j;
        j->payer(prix);
        j->ajouterPropriete(this);

        cout << c->getNom() << " achetée par " << j->getNom() << " pour " << prix << " crédits." << endl;

        cout << j->getNom() << " a maintenant " << j->getArgent() << endl;
    }
}


void Propriete::payerLoyer(Joueur* j) {
    if(proprietaire && j != proprietaire && !hypotheque) {
        if (getType() == Propr) {
            int montant = loyer * (niveau + 1);
            j->payer(montant);
            proprietaire->recevoir(montant);
            cout << j->getNom() << " paie " << montant << " à " << proprietaire->getNom() << endl;
        }
        if (getType() == Gares) {
            int montant = loyer * proprietaire->NbGarePoceder() ;
            j->payer(montant);
            proprietaire->recevoir(montant);
            cout << "Le proprietaire à " << proprietaire->NbGarePoceder() << " Gares " <<endl ;
            cout << j->getNom() << " paie " << montant << " à " << proprietaire->getNom() << endl;
        }
        // montant temporaire je vais changer plus tard
        if (getType() == ServicePublique) 
        {
            if (proprietaire->NbServicesPubliques() == 1){
                
                int montant = loyer ;
                j->payer(montant);
                proprietaire->recevoir(montant);
                cout << j->getNom() << " paie " << montant << " à " << proprietaire->getNom() << endl;
            }
            if (proprietaire->NbServicesPubliques() == 2){
                int montant = loyer * 2 ; 
                j->payer(montant);
                proprietaire->recevoir(montant);
                cout << j->getNom() << " paie " << montant << " à " << proprietaire->getNom() << endl;
            }
            
        }
        }
    }



void Propriete::construire() {
    cout << "Ancien Niveau: " << niveau << endl;
    niveau++;
    cout << "Construction sur " << c->getNom() << ". Nouveau Niveau: " << niveau << endl;
}


void Propriete::action(Joueur* joueur) {
    if (proprietaire == nullptr) {
        acheter(joueur);
        //proprietaire = joueur; Le joueur devient propriétaire
    } else if (proprietaire != joueur) {
        payerLoyer(joueur);
    } else {
        cout << joueur->getNom() << " est déjà propriétaire de " << c->getNom() << endl;
    }
}

string Propriete::couleurToString(Couleur c) const
{
    switch(c) {
        case MARRON: return "Marron";
        case VERT: return "Vert";
        case ROSE: return "Rose";
        case ROUGE: return "Rouge";
        case JAUNE: return "Jaune";
        case ORANGE: return "Orange";
        case BLEUCIEL: return "Bleu ciel";
        case BLEUFONCE: return "Bleu foncé";
        default: return "Inconnue";
    }
}

ostream& operator << (ostream& flux, const vector<Propriete*>& p)
{
    for (size_t i = 0 ; i < p.size() ; i++) 
    {
        flux << "Couleur : "<< p[i]->couleurToString(p[i]->getCouleur()) << endl;
        flux << "Nom de la Case : " << p[i]->getCase()->getNom() <<endl;
        flux << "Position de la Case : " <<  p[i]->getCase()->getPos() <<endl;
        flux << "Prix : " << p[i]->getPrix() << endl;
        flux << "Loyer : "<< p[i]->getLoyer() << endl;
        
    }
    return flux;
}

// Test de régression
void Propriete::testRegression() {
    cout << "=== TestRegression Propriete ===" << endl;

    Case c1("Cafétéria Déambulatoire", 1);
    Propriete p(&c1, 100, 10, 0 , Propr ,MARRON);

    cout << "La couleur : " << p.getCouleur() << endl ;
    assert(p.getCouleur() == MARRON);

    Case c2("Cafétéria Déambulatoire", 1);
    Propriete p1(&c2, 100, 10, 0 , Propr ,ROSE);

    cout << "La couleur : " << p1.getCouleur() << endl;
    assert(p1.getCouleur() == ROSE);



    assert(p.getNiveau() == 0);
    assert(p.getProprietaire() == nullptr);
    assert(c1.getNom() == "Cafétéria Déambulatoire");

    Joueur j1("Zizou");
    p.action(&j1);
    assert(p.getProprietaire() == &j1);

    // Construire et vérifier niveau
    p.construire();
    assert(p.getNiveau() == 1);

    Joueur j2("Moha boukbouk");
    p.action(&j2); // doit payer loyer
    assert(p.getProprietaire() == &j1);

    cout << "Tous les tests de regression Propriete ont reussi !" << endl;
}

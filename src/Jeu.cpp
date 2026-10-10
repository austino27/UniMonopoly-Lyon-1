#include "Jeu.h"
#include <iostream>
#include <errno.h>
#include <string.h>
#include <limits> 
#include <cstdlib>

using namespace std;


Jeu::Jeu() : joueurCourant(0), nbTours(0) , dernierResultatDe(-1) , enAttenteChoix(false), propEnCours(nullptr), joueurEnCours(nullptr) /*carteEnCours(nullptr)*/ { }

Jeu::Jeu(int nbJoueurs) : joueurCourant(0), nbTours(0) , dernierResultatDe(-1) , enAttenteChoix(false), propEnCours(nullptr), joueurEnCours(nullptr) /*carteEnCours(nullptr)     */                  
{
    /*for(int i = 0; i < nbJoueurs; i++) {
        Joueur* j = new Joueur("Joueur " + to_string(i+1));
        joueurs.push_back(j);
    }*/
}

Jeu::~Jeu() {
    for(unsigned int i = 0; i < joueurs.size(); i++) {
        delete joueurs[i];
    }
}

void Jeu::ajouterJoueur(Joueur* j) {
    joueurs.push_back(j);
}


void Jeu::tourSuivant() {
    joueurCourant++;

    if(joueurCourant >= joueurs.size()) {
        joueurCourant = 0;
        nbTours++;
    }
}

void Jeu::Gestion_Prison(Joueur* j)
{
    if(j->estEnPrison())
    {
        cout << "Vous êtes en prison depuis: " << j->getNbTourPrison() + 1 <<" tour ."<< endl;
        if(j->getNbTourPrison() > 1)
        {
        cout << "Vous avez passer vos 3 tours en prison, vous êtes libre !"<< endl;
           j->libererPrison();
        }
        else
        j->setNbTourPrison(j->getNbTourPrison()+1);
    }
}



// en cours d'implémentation
void Jeu::gererEchange(Joueur* j)
{
    int choix;
    cout << "Avec quel joueur voulez-vous échanger ?" << endl;

    vector<Joueur*> joueursEch = getJoueurs();

    for (size_t i = 0; i < joueursEch.size(); i++)
    {
        if (joueursEch[i] != j) // éviter soi meme
            cout << i + 1 << " : " << joueursEch[i]->getNom() << endl;
    }

    do {
        cout << "Votre choix : ";
        cin >> choix;
    } while (choix < 1 || choix > (int)joueursEch.size());

    Joueur* echangeur = joueursEch[choix - 1];

    char rep;
    do {
        cout << echangeur->getNom() << " voulez-vous échanger avec "
             << j->getNom() << " (y/n) : ";
        cin >> rep;
        rep = tolower(rep);
    } while (rep != 'y' && rep != 'n');

    if (rep == 'n') return;

    
    vector<Propriete*> proprEch = echangeur->getProprietes();

    if (proprEch.empty()) {
        cout << "Ce joueur n'a aucune propriété." << endl;
        return;
    }

    cout << "Quelle propriété voulez-vous récupérer ? "<< endl;
    for (size_t i = 0; i < proprEch.size(); i++) {
        cout << i + 1 << " : " << proprEch[i]->getCase()->getNom() << endl;
    }

    int choixProp;
    do {
        cout << "Votre choix : ";
        cin >> choixProp;
    } while (choixProp < 1 || choixProp > (int)proprEch.size());

    int montant;
    cout << "Choisir un montant pour : " <<  proprEch[choixProp -1]->getCase()->getNom() <<endl;
    cin>>montant;

    do {
        cout << j->getNom() << " Accepter vous l'echange à "  << montant << "$ (y/n) : " << endl;
        cin >> rep;
        rep = tolower(rep);
    } while (rep != 'y' && rep != 'n');
    
    if (rep == 'y' ) {
    j->payer(montant);
    echangeur->recevoir(montant);
    cout << "le joueur " << echangeur->getNom() << " recoit "<<montant <<" $." <<endl;
    Propriete* p = echangeur->IemePropriete(choixProp - 1);
    if (p != nullptr) {
        p->setProprietaire(j);
        j->ajouterPropriete(p);
    }
}
}

void Jeu::gererConstruction(Joueur* j) {


    if (!j->estMonopole()) {
        cout << "Vous n'avez auncun Monopole " << endl;
        return;
    }
    cout << "Vous avez un monopole !" << endl;

    int montant = 20;
    if (!getBanque().verifierArgent(j, montant)) {
        cout << "Construction impossible : PAS ASSEZ D'ARGENT !" << endl;
        return;
    }

    vector<Propriete*> monos = j->getMonopole();

    // Affichage des propriétés
    cout << "Proprietes du monopole : ";
    for (size_t i = 0; i < monos.size(); i++) {
        cout << "[" << monos[i]->getCase()->getNom() << "] ";
    }
    cout << endl;

    char rep;
    do {
        cout << "Voulez-vous construire dessus ? (y/n) : ";
        cin >> rep;
        rep = tolower(rep);
    } while (rep != 'y' && rep != 'n');


    // Construction
    if (rep == 'y') {
        int choix;
        cout << "Sur quel propriétés voulez vous construire ? " << endl ;
        cout << "0. Quitter" << endl;
        for (size_t i = 0; i < monos.size(); i++) {
            
            cout << i + 1 << ". " << monos[i]->getCase()->getNom() << endl;
        }
        cout << "Votre choix : " ; 
        cin>>choix;
        if (choix == 0) return;

        monos[choix]->construire();

        cout << "Maisons construites !" << endl;
    } else {
        cout << "Aucune construction." << endl;
    }
}

void Jeu::gererHypotheque(Joueur* j)
{
    vector<Propriete*> prop = j->getProprietes();
    vector<Propriete*> prop_hypothecables;

    int choix;
    int nb_hypothequable;

    while (true)
    {
        nb_hypothequable = 0;
        prop_hypothecables.clear();

        for (size_t i = 0; i < prop.size(); i++)
        {
            if (!prop[i]->estHypotheque() && prop[i]->getNiveau() == 1)
            {
                nb_hypothequable++;
                prop_hypothecables.push_back(prop[i]);
            }
        }

        if (nb_hypothequable == 0)
        {
            cout << "Vous n'avez aucune propriété à hypothéquer." << endl;
            return;
        }

        cout << "\nQuelle propriété voulez-vous hypothéquer ?" << endl;
        cout << "0. Quitter" << endl; 
        for (int i = 0 ; i < nb_hypothequable; i++)
        {
            
            cout << i+1 << ". " 
                 << prop_hypothecables[i]->getCase()->getNom()
                 << " (+" << prop_hypothecables[i]->getPrix() / 2 << " crédits)" << endl;
        }

        cout << "Votre choix : ";
        cin >> choix;

        if (cin.fail() || choix < 0 || choix > nb_hypothequable)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choix invalide !" << endl;
            continue;
        }
        if (choix == 0) return;

        prop_hypothecables[choix-1]->hypothequer();
        cout << "Propriété hypothéquée !" << endl;
    }
}


void Jeu::gererLeverHypotheque(Joueur* j)
{
    vector<Propriete*> prop = j->getProprietes();
    vector<Propriete*> prop_hypothequees;

    int choix;
    int nb_hypothequees;

    while (true)
    {
        // Liste des propriétés hypothéquées
        prop = j->getProprietes();
        prop_hypothequees.clear();
        nb_hypothequees = 0;

        for (size_t i = 0; i < prop.size(); i++)
        {
            if (prop[i]->estHypotheque())
            {
                prop_hypothequees.push_back(prop[i]);
                nb_hypothequees++;
            }
        }

        if (nb_hypothequees == 0)
        {
            cout << "Vous n'avez aucune propriété hypothéquée." << endl;
            return;
        }

        cout << "\nQuelle hypothèque voulez-vous lever ?" << endl;
        cout << "0. Quitter"<< endl;
        for (int i = 1; i < nb_hypothequees; i++)
        {
            int cout_levee = (prop_hypothequees[i]->getPrix() / 2) 
                           + (prop_hypothequees[i]->getPrix() / 10);

            
            cout << i << ". "
                 << prop_hypothequees[i]->getCase()->getNom()
                 << " (coût : " << cout_levee << " crédits)" << endl;
        }

        cout << "Votre choix : ";
        cin >> choix;

        if (cin.fail() || choix < 0 || choix >= nb_hypothequees)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choix invalide !" << endl;
            continue;
        }
        if (choix == 0) return;

        prop_hypothequees[choix]->leverHypotheque();
        cout << "Hypothèque levée !" << endl;
    }
}

int Jeu::getDernierResultatDe() const {
    return dernierResultatDe;
}

void Jeu::jouerTour() {

    Joueur* j = joueurs[joueurCourant];

    cout << "Tour de " << j->getNom() << endl;

    int resultat = de.lancer();
    cout << "Resultat des des : " << resultat << endl;

    dernierResultatDe = de.getValeur();

    int position = deplacer_Joueur(*j, resultat);
    Case* c = plato.getCase(position);

    cout << j->getNom() << " arrive sur la Case "
         << c->getPos() << " : " << c->getNom() << endl;

    // ===== 1. Effet de la case =====
    c->appliquerEffet(j, banque);

    if (j->getArgent() < 0)
    {
        gererCrise(j);
        if (verifierFaillite(j))
        {
            gererFaillites();
            verifierVictoire();
            return;
        }
    }

    // ===== 2. Propriété =====
    Propriete* p = c->getPropriete();

    if (p != nullptr)
    {
        if (p->getProprietaire() == nullptr)
        {
            if (j->getArgent() >= p->getPrix())
            {
                /*int choix;
                cout << "Cette propriete coute " << p->getPrix() << endl;
                cout << "1. Acheter\n2. Refuser\nChoix : ";
                cin >> choix;

                if (choix == 1)
                    p->acheter(j);*/
            
                

                enAttenteChoix = true;
                propEnCours = const_cast<Propriete*>(p);
                joueurEnCours = j;

                cout << "Cette propriete est disponible pour " << p->getPrix() << " crédits." << endl;
            }
            else
            {
                cout << "Pas assez d'argent !" << endl;
            }
        }
        else if (p->getProprietaire() != j)
        {
            p->payerLoyer(j);

            if (j->getArgent() < 0)
            {
                gererCrise(j);
                if (verifierFaillite(j))
                {
                    gererFaillites();
                    verifierVictoire();
                    return;
                }
            }
        }
    }

    // ===== 3. Cartes =====
    if (c->getNom() == "Examens")
    {
        tirerCarteExam(*j);
    }
    else if (c->getNom() == "Vie Étudiante")
    {
        tirerCarteVieEtu(*j);
    }

    if (j->getArgent() < 0)
    {
        gererCrise(j);
        if (verifierFaillite(j))
        {
            gererFaillites();
            verifierVictoire();
            return;
        }
    }

    // ===== 4. Fin du tour =====
    gererFaillites();
    verifierVictoire();

    if (!partieTerminee())
        tourSuivant();
}


bool Jeu::peutAcheter(Joueur* j) {
    Case* c = plato.getCase(j->getPosition());
    Propriete* p = c->getPropriete();

    return (p != nullptr && p->getProprietaire() == nullptr && j->getArgent() >= p->getPrix());
}

void Jeu::acheterProprieteCourante(Joueur* j) {
    Case* c = plato.getCase(j->getPosition());
    Propriete* p = c->getPropriete();

    if (p && p->getProprietaire() == nullptr) {
        p->acheter(j);
        cout << j->getNom() << " a acheté " << p->getCase()->getNom() << endl;
    }
}


void Jeu::gererCrise(Joueur* j)
{
    cout << "\n " << j->getNom() << " est en difficulté financière !" << endl;

    while (j->getArgent() < 0)
    {
        cout << "Argent actuel : " << j->getArgent() << endl;

        cout << "\nQue voulez-vous faire ?" << endl;
        cout << "1. Hypothéquer une propriété" << endl;
        cout << "2. Ne rien faire (abandonner)" << endl;
        cout << "Votre choix : ";

        int choix;
        cin >> choix;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide !" << endl;
            continue;
        }

        if (choix == 1)
        {
            gererHypotheque(j);

            // Si plus aucune propriété hypothécable
            bool possible = false;
            for (auto p : j->getProprietes())
            {
                if (!p->estHypotheque())
                {
                    possible = true;
                    break;
                }
            }

            if (!possible)
            {
                cout << "Plus aucune propriété à hypothéquer !" << endl;
                break;
            }
        }
        else if (choix == 2)
        {
            cout << j->getNom() << " abandonne..." << endl;
            break;
        }
        else
        {
            cout << "Choix invalide !" << endl;
        }
    }
}


bool Jeu::verifierFaillite(Joueur* j)
{
    if (j->getArgent() >= 0)
        return false;

    cout << j->getNom() << " est en faillite définitive !" << endl;
    return true;
}

Plateau& Jeu::getPlateau() {
    return plato;
}

void Jeu::setAttenteChoix(bool f) { enAttenteChoix = f; }
bool Jeu::getAttenteChoix() const { return enAttenteChoix; }
Propriete* Jeu::getPropEnCours() const { return propEnCours;}
Joueur* Jeu::getJoueurEnCours() const { return joueurEnCours;}

De& Jeu::getDe() { return de; }
const De& Jeu::getDe() const { return de; }

int Jeu::deplacer_Joueur(Joueur& j, int nbCases) {

    int position = j.getPosition();
    int nouvelle_position = (position + nbCases) % plato.getNbCases();

    //passe par la case départ
    if(nouvelle_position < position)
    {
        cout << j.getNom() << " passe par la case Depart et reçoit 200 crédits !" << endl;
        j.recevoir(200);
    }

    j.setPosition(nouvelle_position);

    return nouvelle_position;
}



void Jeu::tirerCarteExam(Joueur& j) {

    int indice = rand() % plato.getExamens().size();

    Carte* c = plato.getExamens()[indice];

    cout << j.getNom() << " tire une carte Examens!" << endl;
    cout << c->getDescription() << endl;
    c->appliquerEffet(j, banque);
    // carteEnCours = c;
}

void Jeu::tirerCarteVieEtu(Joueur& j) {

    int indice = rand() % plato.getVieEtu().size();

    Carte* c = plato.getVieEtu()[indice];

    cout << j.getNom() << " tire une carte Vie etudiante !" << endl;
    cout << c->getDescription() << endl;
    c->appliquerEffet(j, banque);
    // carteEnCours = c;
}


/* Carte* Jeu::getCarteEnCours() const { return carteEnCours; } */

/*
void Jeu::verifierVictoire() {

    int joueursActifs = 0;
    Joueur* dernier = nullptr;

    for(unsigned int i = 0; i < joueurs.size(); i++) {

        if(joueurs[i]->getArgent() > 0) {
            joueursActifs++;
            dernier = joueurs[i];
        }
    }

    if(joueursActifs == 1) {
        cout << "Le gagnant est : " << dernier->getNom() << endl;
    }
}
*/

void Jeu::verifierVictoire() {
    if (joueurs.size() == 1) {
        cout << "Le gagnant est : " << joueurs[0]->getNom() << endl;
    }
}


/*
bool Jeu::partieTerminee() const {
    int joueursActifs = 0;
    for (auto& j : joueurs) {
        if (j->getArgent() > 0)
            joueursActifs++;
    }
    return joueursActifs <= 1;
}
*/

bool Jeu::partieTerminee() const {
    return joueurs.size() <= 1;
}



size_t Jeu::getJoueurCourant() const { return joueurCourant; }

/*
Joueur* Jeu::getJoueurGagnant() const {

    for(unsigned int i = 0; i < joueurs.size(); i++) {
        if(joueurs[i]->getArgent() > 0)
            return joueurs[i];
    }

    return nullptr;
}
*/

Joueur* Jeu::getJoueurGagnant() const {
    if (joueurs.size() == 1)
        return joueurs[0];
    return nullptr;
}


Banque& Jeu::getBanque() { return banque; }        
const Banque& Jeu::getBanque() const { return banque; } 

const Plateau& Jeu::getPlateau() const { return plato; }


const vector<Joueur*>& Jeu::getJoueurs() const { return joueurs; }



// Gestion de la faillite

void Jeu::gererFaillites() {
    for (size_t i = 0; i < joueurs.size(); ) {
        if (joueurs[i]->estEnFaillite()) {

            cout << joueurs[i]->getNom() << " est éliminé !" << endl;

            joueurs[i]->libererProprietes();
            delete joueurs[i];

            joueurs.erase(joueurs.begin() + i);
        }
        else {
            i++;
        }
    }
}

/*
bool Jeu::acheterPropriete(Joueur* j, Propriete* p)
{
    if (j->getArgent() >= p->getPrix())
    {
        p->acheter(j);
        return true;
    }
    return false;
}
*/

void Jeu::TestRegression() {

    cout << "Test du jeu..." << endl;

    Jeu jeu(2);

    for(int i = 0; i < 10; i++) {
        jeu.jouerTour();
    }

    cout << "Test terminé" << endl;
}

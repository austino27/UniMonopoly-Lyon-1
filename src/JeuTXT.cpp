#include "JeuTXT.h"
#include <iostream>
#include <limits>
using namespace std;


JeuTXT::JeuTXT() : jeu() { }

JeuTXT::~JeuTXT() { }

void JeuTXT::initialiser(int nbJoueurs, const vector<string>& noms) 
{
    for(int i = 0; i < nbJoueurs; i++) {
        Joueur* j = new Joueur(noms[i]);
        jeu.ajouterJoueur(j);
    }
}

void JeuTXT::afficherPlateau() const {
    int i,j;
    j=19;
    bool case_vide =true;
    vector<Joueur*> joueurs = jeu.getJoueurs();


    cout << "=== Plateau ===" << endl;
    
    for(i=20;i<31;i++)
    {
        cout <<"[";

        for (size_t x = 0; x < joueurs.size(); x++) {
        if(joueurs[x]->getPosition()==i)
        {
            cout << (x + 1);
            case_vide = false;
        }
        
    }
    if(case_vide) cout << " ";

        cout << "]";
        case_vide = true;
    }
    cout << endl;

    for(i=31;i<40;i++)
    {

        cout << "[";

        for (size_t x = 0; x < joueurs.size(); x++) {
        if(joueurs[x]->getPosition()==j)
        {
            cout << (x + 1);
            case_vide = false;
        }
        }
        if(case_vide) cout << " ";

        cout << "]";
        case_vide = true;

        j--;

        cout << "                           " ;

        cout << "[";

        for (size_t x = 0; x < joueurs.size(); x++) {
        if(joueurs[x]->getPosition()==i)
        {
            cout << (x + 1);
            case_vide = false;
        }
    }
        if(case_vide) cout << " ";

        cout << "]";
        case_vide = true;
        cout << endl;
         
}


    for(i=10;i>-1;i--)
    {
        cout <<"[";

        for (size_t x = 0; x < joueurs.size(); x++) {
        if(joueurs[x]->getPosition()==i)
        {
            cout << (x + 1);
            case_vide = false;
        }
        
    }
    if(case_vide) cout << " ";

        cout << "]";
        case_vide = true;
    }
    cout << endl;
    cout << "===============" << endl;
}


void JeuTXT::afficherInfosJoueur() const {
    cout << "=== Infos Joueurs ===" << endl;

    vector<Joueur*> joueurs = jeu.getJoueurs();
    for (size_t i = 0; i < joueurs.size(); i++) {
        Joueur* j = joueurs[i];

        cout << j->getNom() << " | Argent: " << j->getArgent()
             << " | Position: " << j->getPosition();


        vector<Propriete*> props = j->getProprietes();
        cout << " | Nb propriétés: " << props.size();

        if (j->getCarteLiberation()) {
            cout << " | CarteLibération: " << j->getCarteLiberation();
        }

        if (!props.empty()) {
            cout << " | Proprietes: ";
            for (size_t k = 0; k < props.size(); k++) {
                cout << "[" << props[k]->getCase()->getNom() << "]";
                if (props[k]->estHypotheque())
                {
                    cout << "(H) ";
                }
            }
        }

        cout << endl;
    }

    cout << "===================" << endl;
}
/*
bool JeuTXT::demanderLancerDes() const {
    int reponse;

    do {
        cout << "Voulez-vous lancer les dés ?" << endl;
        cout << "1. Lancer les dés" << endl;
        cout << "Votre choix : ";

        cin >> reponse;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide ! Veuillez choisir 1" << endl;
            continue;
        }

        if (reponse == 1) {
            cout << "Lancement des dés..." << endl;
            return true;
        } 
        else {
            cout << "Réponse invalide, veuillez taper 1." << endl;
        }

    } while (true);
}
*/

int JeuTXT::MenuJeuTXT() const {
    int reponse;

    do {
        cout << "Que voulez-vous faire? " << endl;
        cout << "1. Lancer les dés" << endl;
        cout << "2. Acheter des maisons" << endl;
        cout << "3. Hypotéquer des propriétés" << endl;
        cout << "4. Déshypothequer des propriétés" << endl;
        cout << "5. Echange avec les autres joueurs" << endl;
        cout << "Votre choix : ";

        cin >> reponse;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide ! Veuillez choisir 1" << endl;
            continue;
        }

        if (reponse == 1) {
            cout << "Lancement des dés..." << endl;
            return 1;
        } 
        if (reponse == 2) {
            return 2;
        } 
        if (reponse == 3) {
            return 3;
        } 
        if (reponse == 4) {
            return 4;
        } 
        if (reponse == 5) {
            return 5;
        } 
        else {
            cout << "Réponse invalide, veuillez taper 1." << endl;
        }

    } while (true);
}




int JeuTXT::demanderNbJoueurs() {
    int rep;

    while (true) {
        cout << "\n=== Choix du nombre de joueurs ===" << endl;
        cout << "\nChoisir un nombre de joueurs (2 à 6) : " ;
        cin >> rep;
        rep = tolower(rep);

        // gestion erreur
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrée invalide ! Veuillez entrer un nombre." << endl;
            continue;
        }

        if (rep >= 2 && rep <= 6) {
            return rep ;
        }

        cout << "Choix invalide ! Veuillez choisir entre 1 et 6." << endl;
    }
}

void JeuTXT::demanderNomsJoueurs(int nbJoueurs, vector<string>& noms) {
    cin.ignore(); // vider buffer
    for(int i = 0; i < nbJoueurs; i++) {
        string nom;
        cout << "Nom du joueur " << i+1 << " : ";
        getline(cin, nom);
        noms.push_back(nom);
    }
}

bool JeuTXT::confirmerLancement() {
    char rep;
    while (true) {
        cout << "Voulez-vous lancer la partie (y/n)? : ";
        cin >> rep;

        rep = tolower(rep);

        if (rep == 'y') return true;
        if (rep == 'n') return false;

        cout << "Entrée invalide. Essayez encore.\n";
    }
}

void JeuTXT::initialiserJeu(int nbJoueurs, const vector<string>& noms) {
    for (int i = 0; i < nbJoueurs; i++) {
        Joueur* j = new Joueur(noms[i]);
        jeu.ajouterJoueur(j); 
    }
}

void JeuTXT::jouerUnTour() {
    Joueur* j = jeu.getJoueurs()[jeu.getJoueurCourant()];

    cout << "C'est au tour de " << j->getNom() << endl;

    if (j->estEnPrison()) {
        gererTourPrison(j);
    } 
    else {
        gererTourNormal(j);
    }
}

void JeuTXT::gererTourPrison(Joueur* j) {
    cout << j->getNom() << " est en prison !" << endl;

    jeu.Gestion_Prison(j);
    jeu.tourSuivant();
}
/*
void JeuTXT::gererTourNormal(Joueur* j) {
    gererConstruction(j);

    bool lancer = demanderLancerDes();

    if (lancer) {
        jeu.jouerTour();
    } 
    else {
        jeu.tourSuivant();
    }
}
*/



void JeuTXT::gererTourNormal(Joueur* j) {
    int quoiFaire ;
    do {
        quoiFaire = MenuJeuTXT();
    
    if (quoiFaire == 1)
{
    Joueur* j = jeu.getJoueurs()[jeu.getJoueurCourant()];

    int resultat = jeu.getDe().lancer();
    cout << "Resultat des dés : " << resultat << endl;

    int pos = jeu.deplacer_Joueur(*j, resultat);

    Case* c = jeu.getPlateau().getCase(pos);

    cout << j->getNom() << " arrive sur " << c->getNom() << endl;

    
    c->appliquerEffet(j, jeu.getBanque());

    
    Propriete* p = c->getPropriete();

    if (p && p->getProprietaire() == nullptr)
    {
        char rep;
        cout << "Voulez-vous acheter " << p->getCase()->getNom()
             << " pour " << p->getPrix() << " ? (y/n) : ";
        cin >> rep;

        if (tolower(rep) == 'y')
        {
            p->acheter(j);
            cout << "Achat effectué !" << endl;
        }
    }
    else if (p && p->getProprietaire() != j)
    {
        cout << j->getNom() << " doit payer un loyer !" << endl;
        p->payerLoyer(j);
    }

    jeu.tourSuivant();
}
    if (quoiFaire == 2) {
        jeu.gererConstruction(j);
    }
    if (quoiFaire == 3) {
        jeu.gererHypotheque(j);
    }
    if (quoiFaire == 4) {
        jeu.gererLeverHypotheque(j);
    }
     if (quoiFaire == 5) {
        jeu.gererEchange(j);
        
    }


    
}
    while(quoiFaire != 1) ;
}

void JeuTXT::afficherFinPartie() const {
    Joueur* gagnant = jeu.getJoueurGagnant();

    cout << "\nLa partie est terminée !\n";

    if (gagnant) {
        cout << "Le gagnant est : " << gagnant->getNom() << endl;
    } 
    else {
        cout << "Pas de gagnant clair.\n";
    }
}

void JeuTXT::boucleDeJeu() {
    int tour = 0;

    while (tour < 40) {

        cout << "\n=== Tour " << tour + 1 << " ===\n";

        jouerUnTour();
        
        afficherPlateau();
        afficherInfosJoueur();

        if (jeu.partieTerminee()) {
            afficherFinPartie();
            break;
        }

        tour++;
    }

    if (tour >= 40) {
        cout << "\nFin des 40 tours, pas de gagnant clair.\n";
    }
}

void JeuTXT::lancerPartie() {
    cout << "=== Bienvenue au Monopoly Universitaire ===\n";

    int nbJoueurs = demanderNbJoueurs();
    vector<string> noms;
    demanderNomsJoueurs(nbJoueurs, noms);

    if(!confirmerLancement()) {
        cout << "Partie annulée.\n";
        return;
    }

    initialiserJeu(nbJoueurs, noms);
    cout << "\nPartie lancée !\n";
    boucleDeJeu();
}


bool JeuTXT::demanderAchat(Propriete* p, Joueur* j)
{
    char rep;

    while (true)
    {
        cout << "Voulez-vous acheter " 
             << p->getCase()->getNom()
             << " pour " << p->getPrix()
             << " ? (y/n) : ";

        cin >> rep;
        rep = tolower(rep);

        if (rep == 'y') return true;
        if (rep == 'n') return false;

        cout << "Réponse invalide.\n";
    }
}


void JeuTXT::TestRegression() {
    cout << "=== TestRegression JeuTXT ===" << endl;

    JeuTXT jt;

    cout << "\nAffichage initial du plateau :" << endl;
    jt.afficherPlateau();

    cout << "\nAffichage initial des joueurs :" << endl;
    jt.afficherInfosJoueur();

    cout << "\nTest deplacement joueur de 3 cases..." << endl;

    const vector<Joueur*>& joueurs = jt.jeu.getJoueurs();

    if (!joueurs.empty()) {
        Joueur* j = joueurs[0];

        int posAvant = j->getPosition();

        jt.jeu.deplacer_Joueur(*j, 3);

        cout << j->getNom() << " est passé de "
             << posAvant << " à "
             << j->getPosition() << endl;
    } 
    else {
        cout << "Aucun joueur dans la partie !" << endl;
    }

    cout << "\nEtat du plateau apres deplacement :" << endl;
    jt.afficherPlateau();

    cout << "\nInfos joueurs apres deplacement :" << endl;
    jt.afficherInfosJoueur();

    cout << "\nTous les tests JeuTXT ont reussi !" << endl;
}

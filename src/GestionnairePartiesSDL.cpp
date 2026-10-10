#include "GestionnairePartiesSDL.h"
#include "Joueur.h"
#include "Propriete.h"
using namespace std;

GestionnaireParties::GestionnaireParties() {
    
}

GestionnaireParties::~GestionnaireParties() {
    
}

void GestionnaireParties::lancerPartie()
{
    interface.setJeu(&jeu);
    interface.setGestionnaire(this);
    interface.initCases();
    
    MenuSDL menu(interface.getWindow(), interface.getRenderer());

    int choix = menu.afficherMenuPrincipalGraphique();

    if (choix == 4) return; // quitter
    if (choix == 1 || choix == 2 || choix == 3)
    {
        cout << "Mode non implemente" << endl;
        return;
    }
    
    
    int nbJoueurs = menu.demanderNbJoueur();

    if (nbJoueurs < 2) return;

    vector<int> pionsChoisis;

    for (int i = 0; i < nbJoueurs; i++)
    {

        string nom = menu.demanderNomJoueur(i + 1);
        Joueur* j = new Joueur(nom);

        
        int pion;
        do {
            pion = menu.choisirPion(i + 1);
        }  while (estDejaPris(pionsChoisis, pion));

        // 3. Enregistrer le pion
        j->setPion(pion);
        pionsChoisis.push_back(pion);

        // 4. Ajouter au jeu
        jeu.ajouterJoueur(j);
    }

    // couper musique menu ici
    Mix_HaltMusic();
    interface.afficherFenetre();
}



bool GestionnaireParties::estDejaPris(const vector<int>& pions, int pion)
{
    for  (size_t i = 0; i < pions.size(); i++)
    {
        if (pions[i] == pion)
            return true;
    }
    return false;
}


void GestionnaireParties::gererTour()
{
    jeu.jouerTour();
}


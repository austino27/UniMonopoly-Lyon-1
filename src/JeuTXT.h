#ifndef _JEUTXT_H
#define _JEUTXT_H

#include <iostream>
#include "Propriete.h"
#include "Jeu.h" 

class JeuTXT {
    public:
        JeuTXT();
        ~JeuTXT();
        void initialiser(int nbJoueurs, const std::vector<std::string>& noms);
        void afficherPlateau() const;       // Affiche le plateau avec les positions des joueurs
        void afficherInfosJoueur() const;   // Affiche argent, propriétés, position des joueurs
        void afficherFinPartie() const;

        bool demanderLancerDes() const;
        int demanderNbJoueurs();
        void demanderNomsJoueurs(int nbJoueurs, std::vector<std::string>& noms);
        bool demanderAchat(Propriete* p, Joueur* j);
        int MenuJeuTXT() const;


        bool confirmerLancement();
        void initialiserJeu(int nbJoueurs, const std::vector<std::string>& noms);
        void jouerUnTour();
        void gererConstruction(Joueur* j);
        void gererTourPrison(Joueur* j);
        void gererTourNormal(Joueur* j);
        void boucleDeJeu(); 
        void lancerPartie();  


        static void TestRegression();

    private:
        Jeu jeu;   // On utilise la classe Jeu pour gérer la partie
};

#endif


// bug sur monopole les proprietes sans couleur surtout les gares et services publiques
// fait perdre de l'argent quand on construit avec la banque
// gerer les depense avec la banque totalement
// Faire la boucle si on a pas dargent avant (Fait), monopole propriete (Fait) 
// carte (Fait mais il manque un tab de carte dans joueur si par exemple il obtient la carte de liberation)

// Faire un tab 2D,prison,case depart (augustin)

/* Fonctionnalités qui reste a implementer :
 Hypothèques , Gestion complète de la prison , échange de carte a l'amiable  */

// gerer la faillite ,

#ifndef _GESTIONNAIREPARTIES_H
#define _GESTIONNAIREPARTIES_H

#include "JeuSDL.h"
#include "Menu.h"


/**
 * @class GestionnaireParties
 * @brief coordonne le déroulement d'une partie en mode graphique
 * fait le lien entre Jeu et JeuSDL
 */

class GestionnaireParties 
{
    public:

        /**
         * @brief constructeur par défaut
         */
        GestionnaireParties();

        /**
         * @brief destructeur GestionnaireParties
         */
        ~GestionnaireParties();
        
        /**
         * @brief bascule entre mode plein écran et fenêtré
         */
        void basculerFullscreen();

        /**
         * @brief lance la partie depuis le menu jusqu'à la fin
         */
        void lancerPartie();

        /**
         * @brief retourne vrai si un pion est déjà choisi par un autre joueur
         * @param pions vecteur des pions déjà attribués
         * @param pion identifiant du pion à tester
         */
        bool estDejaPris(const std::vector<int>& pions, int pion);

        /**
         * @brief joue le tour du joueur courant via l'interface graphique
         */
        void gererTour();

        /**
         * @brief ferme proprement le jeu (libère les ressources et quitte SDL)
         */
        void fermerJeu();
       

        /**
         * @brief test de regression de la class GestionnaireParties
         */
        static void TestRegression(); 
        
    private:
         Jeu jeu;           ///< instance de la logique de jeu
         JeuSDL interface;  ///< interface graphique associée


        
};

#endif
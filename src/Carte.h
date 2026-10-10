#ifndef _CARTE_H
#define _CARTE_H

#include <string>
#include "Banque.h"
#include "Joueur.h"
/**
 * @class Carte
 * @brief représente les cartes chances et caiss de communauté (Examen/Vie Etudiante)
 */

class Carte 
{
    public:

    /**
     * @enum TypeCarte
     * @brief permet de catégoriser les effets de la carte
     */
        enum TypeCarte {
            ARGENT = 0,     ///< modifie argent 
            DEPLACEMENT = 1,    ///< modifie position
            PRISON = 2,     ///< envoie en prison
            LIBERATION = 3, // /< carte sortir de prison
            AVANTAGE = 4    ///< autres types de cartes
    };

        /**
        * @brief constructeur par défaut de carte
        */
        Carte();

        /**
        * @brief constructeur de carte 
        * @param description le texte explicatif de la carte
        * @param effet valeur associée à l'effet (ex: si argent le montant)
        * @param type le type d'effet TypeCarte
        */
        Carte(std::string description, int effet ,TypeCarte type);

        /**
         * @brief destructeur carte
         */
        ~Carte();
        
        /**
         * @brief applique l'effet de la carte à un joueur
         * @param j pointeur du joueur sur qui applique l'effet
         * @param banque gestion du transfert si argent
         */
        void appliquerEffet(Joueur& j, Banque& banque);
        
        /**
         * @brief retourne la carte courante 
         */
        const Carte& getCarte() const;

        /**
         * @brief retourne la description de la carte courante
         */
        const std::string getDescription() const;

        /**
         * @brief test de regression de la class Carte
         */
        static void TestRegression();



    private:
        std::string description;    ///< texte d'explication de l'effet de la carte
        int effet;  ///< valeur liée à l'effet (ex: montant si carte taxe)
        TypeCarte type; ///< type de la carte 

};

#endif
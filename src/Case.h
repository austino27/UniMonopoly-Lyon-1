#ifndef _CASE_H
#define _CASE_H

#include <string>
#include <iostream>

class Banque;
class Joueur;
class Propriete;

/**
 * @class Case
 * @brief représente les cases du plateau avec position, nom et un pointeur
 * sur la propriété associé si la case en est une.
 */

class Case 
{
    private:
        std::string nom;    ///< nom de la case
        int positionC;  ///< position de la case sur le plateau
        Propriete* Pr;  ///< pointeur sur propriete ou nullptr

    public:
    /**
     * @brief constructeur par défaut case 
     */
        Case();

    /**
     * @brief constructeur case avec son nom et sa position
     * @param nom nom de la case 
     * @param positionC position de la case sur le plateau int
     */
        Case(std::string nom, int positionC);

    /**
     * @brief destructeur case
     */
        ~Case();

        /**
         * @brief applique l'effet des cases prison et taxes
         * @param j pointeur sur le joueur
         * @param banque pour payer les cases taxes 
         */
        void appliquerEffet(Joueur* j, Banque& banque);


        /**
         * @brief donne le nom de la case courante
         */
        std::string getNom() const;
        /**
         * @brief donne la position de la case
         */
        int getPos() const;
        /**
         * @brief associe une propriete à la case
         * @param p pointeur sur la propriete associe à la case
         */
        void setPropriete(Propriete* p) ;

        /**
         * @brief retourne la propriete associé à la case courante 
         */
        Propriete* getPropriete() const ;

        /**
         * @brief test de regression de la class Case
         */
        static void TestRegression();
};

#endif
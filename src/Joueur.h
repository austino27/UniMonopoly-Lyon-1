#ifndef _JOUEUR_H
#define _JOUEUR_H

#include <vector>
#include <string>
#include "Case.h"    
class Propriete;

/**
 * @class Joueur
 * @brief représente un joueur avec son id associe
 * son argent, sa postion etc...
 */

class Joueur {
    private:
        bool tourJoueur; ///< vrai si c'est au tour du joueur
        std::string nom;    ///< nom du joueur
        int idJoueur;   ///< id du joueur
        int argent; ///< argent du joueur 
        int position;   ///< position du joueur sur le plateau 
        bool prison;    ///< vrai si le joueur est en prison
        bool carteLiberation;   ///< vrai si le joueur a une carte libération de prison
        std::vector<Propriete*> proprietes; ///< vecteur de pointeur sur les proprietes du joueur
        int nb_tour_prison; ///< le nombre de tour passé en prison (sort au bout de 3)

    public:

        /**
         * @brief Constructeur par défaut
         */
        Joueur();  
        
        /**
         * @brief Constructeur avec le nom
         * @param nom nom du joueur
         */
        Joueur(std::string nom);   
        
        /**
         * @brief Constructeur avec le nom et l'id
         * @param nom nom du joueur
         * @param id id du joueur
         */
        Joueur(std::string nom ,int id); 

        /**
         * @brief Destructeur Joueur
         */
        ~Joueur();

        /**
         * @brief avance le joueur d'un certain nombre de cases
         * @param nombreCases nombre de cases à avancer
         * @param taillePlateau taille du plateau
         */
        void deplacer(int nombreCases, int taillePlateau);

        /**
         * @brief recule le joueur de nbCases
         * @param nbCases nombre de cases à reculer
         * @param taillePlateau taille du plateau
         */
        void reculer(int nbCases, int taillePlateau);

        /**
         * @brief Le joueur paye un montant.
         * @param montant Somme à débiter du compte du joueur
         */
        void payer(int montant);

        /**
         * @brief Le joueur reçoit un montant
         * @param montant Somme à créditer sur le compte du joueur
         */
        void recevoir(int montant);


         /**
         * @brief Ajoute une propriété au joueur
         * @param p Pointeur sur la propriété 
         */
        void ajouterPropriete(Propriete* p);

        /**
         * @brief Retire une propriété au joueur
         * @param p Pointeur sur la propriété à céder
         */
        void vendrePropriete(Propriete* p);

        /**
         * @brief retourne le nombre de services publiques possédés par le joueur
         */
        int NbServicesPubliques() const;

        /**
         * @brief retourne le nombre de gares possédées par le joueur
         */
        int NbGarePoceder() const ;

        /**
         * @brief retourne vrai si le joueur possède au moins un monopole
         */
        bool estMonopole() const;

        /**
         * @brief Retourne les propriétés faisant partie d'un monopole
         */
        std::vector<Propriete*> getMonopole() const;
        
        /**
         * @brief retourne vrai si le joueur est en prison
         */
        bool estEnPrison() const;    

        /**
         * @brief Envoie le joueur en prison
         */
        void allerEnPrison();

        /**
         * @brief libère le joueur de prison
         */
        void libererPrison();
        
        /**
         * @brief retourne vrai si le joueur est en faillite
         */
        bool estEnFaillite() const;

        /**
         * @brief libère toutes les propriétés du joueur en cas de faillite
         */
	    void libererProprietes();


        void setPion(int id) { idJoueur = id; }
        int getPion() const { return idJoueur; }



        std::vector<Propriete*> getProprietes() const;


        Propriete* IemePropriete(int i);


        const int getNbTourPrison() const ;


        int getArgent() const;


        int getPosition() const;


        std::string getNom() const;


        bool getCarteLiberation() const;  


        void setNbTourPrison(int n); 


        void setCarteLiberation(bool valeur); 

        
        void setPosition(int p);

        static void TestRegression();
};

#endif

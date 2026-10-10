#ifndef _PROPRIETE_H
#define _PROPRIETE_H


#include <string>
#include "Case.h"
#include "Joueur.h"

/**
 * @enum TypePropriete
 * @brief Catégorie d'une propriété
 */

enum TypePropriete
{
    Propr,  ///< propriete classique couleur
    ServicePublique,    ///< service publique 
    Gares   ///< gares 
};

/**
 * @enum Couleur
 * @brief couleur propriete
 */
enum Couleur 
{
    MARRON,
    BLEUCIEL,
    ROSE,
    ORANGE,
    ROUGE,
    JAUNE,
    VERT,
    BLEUFONCE
};


/**
 * @class Propriete
 * @brief représente les proprietes du plateau  avec leur prix, leur type, les maisons etc...
 */

class Propriete{
    private:
        Case* c;                  ///< Case associée à cette propriété
        int prix;                 ///< Prix d'achat de la propriété
        int loyer;                ///< Loyer à payer
        int niveau;               ///< Niveau de construction (maison)
        Joueur* proprietaire;     ///<  pointeur sur Joueur propriétaire
        TypePropriete TypeP;      ///< Type de propriété
        Couleur couleurP;         ///< Couleur du groupe 
        bool hypotheque;          ///< true si la propriété est hypothéquée
    
    public:

        /**
         * @brief Constructeur par défaut
         */
        Propriete();
        /**
         * @brief Construit une propriété complète avec couleur
         * @param c Case associée
         * @param prix Prix d'achat
         * @param loyer Loyer initial
         * @param niveau Niveau de construction de départ
         * @param TypeP Type de propriété
         * @param couleurP Couleur du groupe
         */
        Propriete(Case* c, int prix, int loyer,int niveau,TypePropriete TypeP, Couleur couleurP);

        /**
         * @brief Construit une propriété sans couleur (gare ou service publique)
         * @param c Case associée
         * @param prix Prix d'achat
         * @param loyer Loyer initial
         * @param niveau Niveau de construction de départ
         * @param TypeP Type de propriété
         */
        Propriete(Case* c, int prix, int loyer,int niveau,TypePropriete TypeP);

        /**
         * @brief Destructeur propriete
         */
        ~Propriete();

        /**
         * @brief retourne le pointeur sur joueur proprietaire
         */
        Joueur* getProprietaire() const;

        /**
         * @brief retourne le nombre de maisons
         */
        int getNiveau() const;
        /**
         * @brief retourne le prix de la propriete
         */
        int getPrix() const;

        /**
         * @brief retourne un pointeur sur la case associé à la propriete
         */
        Case* getCase() const;

        /**
         * @brief retourne la couleur enum Couleur associé à la propriete
         */
        Couleur getCouleur() const;

        /**
         * @brief retourne le type associé à la propriete
         */
        TypePropriete getType() const ;

        /**
         * @brief retourne le loyer de la propriete
         */
        int getLoyer () const ;

        /**
         * @brief retourne la chaine de caractère couleur de la prop
         * @param c enum Couleur
         */
        std::string couleurToString(Couleur c) const;

        /**
         * @brief met à jour le loyer en fonction du niveau et du type
         */
        void setLoyer () ;
        
        /**
         * @brief change le proprietaire de la propriete
         * @param j pointeur sur nouveau proprietaire de la propriete
         */
        void setProprietaire(Joueur* j);

        /**
         * @brief procède à l'achat de la propriété par un joueur
         * @param j pointeur sur l'acheteur.
         */
        void acheter(Joueur* j);

        /**
         * @brief le joueur courant paye le loyer au propriétaire
         * @param joueur pointeur sur le joueur qui doit payer
         */
        void payerLoyer(Joueur* joueur);

        /**
         * @brief construit un niveau supplémentaire sur la propriété
         */
        void construire();

        /**
         * @brief action déclenchée lorsqu'un joueur s'arrête sur la case 
         * @param joueur pointeur sur le joueur 
         */
        void action(Joueur* joueur);

        /**
         * @brief retourne vrai si la propriete courante est hypotheque
         */
        bool estHypotheque() const;

        /**
         * @brief hypothèque la propriete et le joueur reçoit l'argent
         */
        void hypothequer();

        /**
         * @brief lève l'hypothèque 
         */
        void leverHypotheque();
        
        friend std::ostream& operator << (std::ostream& flux, const std::vector<Propriete*>& p);

        /**
         * @brief test de régression pour la class propriete
         */
        static void testRegression();
};

#endif

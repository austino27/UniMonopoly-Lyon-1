#ifndef _JEU_H
#define _JEU_H

#include "Carte.h"
#include "Joueur.h"
#include "Plateau.h"
#include "De.h"
#include "Banque.h"
#include <vector>


/**
 * @class Jeu 
 * @brief contient toute la logique de déroulement d'une partie de monopoly
 */
class Jeu {
    public:

    /**
     * @brief constructeur par défaut
     */
        Jeu();

        /**
        * @brief constructeur 
        * initiale une partie
        * @param nbJoueurs nombre de joueur dans la partie
        */
        Jeu(int nbJoueurs);

        /**
         * @brief destructeur Jeu
         */
        ~Jeu();

        /**
         * @brief ajoute un joueur à la partie
         * @param j pointeur sur le joueur à ajouter
         */
        void ajouterJoueur(Joueur* j);

        /**
         * @brief passe au tour du joueur suivant
         */
        void tourSuivant();

        /**
         * @brief joue le tour du joueur courant
         */
        void jouerTour();   

         /**
         * @brief déplace un joueur d'un nombre de cases donné
         * @param j pointeur sur le Joueur à déplacer 
         * @param nbCases nombre de cases à parcourir
         * @return nouvelle position du joueur
         */
        int deplacer_Joueur(Joueur& j, int nbCases);

         /**
         * @brief gère le tour d'un joueur en prison
         * @param j pointeur sur le joueur en prison
         */
        void Gestion_Prison(Joueur* j);

        /**
         * @brief tire une carte examen et applique son effet
         * @param j joueur cible
         */
        void tirerCarteExam(Joueur& j);

        /**
         * @brief tire une carte vie etu et applique son effet
         * @param j joueur cible
         */
        void tirerCarteVieEtu(Joueur& j);

        /**
         * @brief retourne vrai si le joueur peut acheter la propriete sur laquelle il se trouve
         * @param j pointeur sur le joueur
         */
        bool peutAcheter(Joueur* j);

        /**
         * @brief le joueur achète la propriete sur laquelle il se trouve
         * @param j pointeur sur l'acheteur
         */
        void acheterProprieteCourante(Joueur* j);

        /**
         * @brief vérifie si un joueur a gagné la partie
         */
        void verifierVictoire();

        /**
         * @brief retourne vrai si la partie est terminée
         */
        bool partieTerminee() const;
        
        //Gestion de la faillite

        /**
         * @brief gère les faillites éventuelles à la fin d'un tour
         */
        void gererFaillites();

        /**
         * @brief gère un état de crise (vente forcée, hypothèque...)
         * @param j pointeur sur le joueur en difficulté
         */
        void gererCrise(Joueur* j);

        /**
         * @brief retourne vrai si le joueur est en faillite
         * @param j pointeur sur le joueur à tester
         */
	    bool verifierFaillite(Joueur* j);

        /**
         * @brief retourne l'index du joueur dont c'est le tour
         */
        size_t getJoueurCourant() const;

        /**
         * @brief retourne le joueur gagnant (nullptr si la partie n'est pas finie)
         */
        Joueur* getJoueurGagnant() const;

        /**
         * @brief retourne le résultat du dernier lancer de dé
         */
        int getDernierResultatDe() const;

        /**
         * @brief retourne le plateau de jeu (modifiable)
         */
        Plateau& getPlateau();

        /**
         * @brief retourne le plateau de jeu (lecture seule)
         */
        const Plateau& getPlateau() const;

        /**
         * @brief retourne la banque (modifiable)
         */
        Banque& getBanque();         

        /**
         * @brief retourne la banque (lecture seule)
         */
        const Banque& getBanque() const ;

        /**
         * @brief retourne la liste des joueurs
         */
        const std::vector<Joueur*>& getJoueurs() const; 

        /**
         * @brief retourne le dé du jeu (modifiable)
         */
        De& getDe();

        /**
         * @brief retourne le dé du jeu (lecture seule)
         */
        const De& getDe() const;

        /**
         * @brief retourne vrai si la partie attend un choix du joueur courant
         */
        bool getAttenteChoix() const;

        /**
         * @brief active ou désactive l'état d'attente de choix
         * @param f true pour mettre en attente, false pour reprendre
         */
        void setAttenteChoix(bool f);

        /**
         * @brief retourne la propriete en cours de décision (achat)
         */
        Propriete* getPropEnCours() const;

        /**
         * @brief retourne le joueur en cours de décision
         */
        Joueur* getJoueurEnCours() const;
        // Carte* getCarteEnCours() const;


        /**
         * @brief gère un échange de propriétés entre deux joueurs
         * @param j pointeur sur le joueur initiant l'échange
         */
        void gererEchange(Joueur* j);

        /**
         * @brief gère la construction d'une maison sur une propriete
         * @param j pointeur sur le joueur souhaitant construire
         */
        void gererConstruction(Joueur* j);

        /**
         * @brief gère la mise sous hypothèque d'une propriete
         * @param j pointeur sur le joueur concerné
         */
        void gererHypotheque(Joueur* j);

        /**
         * @brief gère la levée d'une hypothèque
         * @param j pointeur sur le joueur concerné
         */
        void gererLeverHypotheque(Joueur* j);

        
        //bool AcheterPropriete(Joueur* j, Propriete* p);

        /**
         * @brief test de regression de la class Jeu
         */
        static void TestRegression();
    private:
        std::vector <Joueur*> joueurs;  ///< liste des joueurs de la partie
        Plateau plato;                  ///< plateau de jeu
        Banque banque;                  ///< banque centrale
        size_t joueurCourant;           ///< index du joueur dont c'est le tour
        int nbTours;                    ///< nombre total de tours joués
        De de;                          ///< dé utilisé pour les déplacements
        int dernierResultatDe;          ///< dernier résultat du dé

        bool enAttenteChoix;            ///< vrai si la partie est en pause pour attendre un choix joueur
        Propriete* propEnCours;         ///< propriete concernée par le choix en cours
        Joueur* joueurEnCours;          ///< joueur devant prendre la décision
        // Carte* carteEnCours;
};

#endif
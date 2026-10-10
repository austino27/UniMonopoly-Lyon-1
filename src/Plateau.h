#ifndef _PLATEAU_H
#define _PLATEAU_H
#include "Case.h"
#include "Propriete.h"
#include "Carte.h"
#include <vector>


/**
 * @class Plateau 
 * @brief représente le plateau de cases (40 Case)
 */
class Plateau {

    public:

    /**
     * @brief constructeur par défaut 
     * Initialise toutes les cases, propriete et cartes
     */
        Plateau();

        /**
         * @brief destructeur par défaut
         */
        ~Plateau();
        
        /**
         * @brief initialise les 40 cases du plateau
         */
        void initialiserPlateau();

        /**
         * @brief initialise les propriétés et les associe aux cases correspondantes
         */
        void initialiserPriopriete();

        /**
         * @brief initialise les cartes exam
         */
        void initialiserCartesExam();

        /**
         * @brief initialise les cartes vie etu
         */
        void initialiserCartesVieEtu();

        /**
         * @brief retourne le nombre de cases du plateau
         */
        int getNbCases() const;

        /**
         * @brief retourne la case située à la position indiquée
         * @param position id de la case
         */
        const Case* getCase(int position) const;


        Case* getCase(int index);

        /**
         * @brief retourne les cartes examen
         */
        const std::vector<Carte*>& getExamens() const ;

        /**
         * @brief retourne les cartes vie etu
         */
        const std::vector<Carte*>& getVieEtu() const ;

        /**
         * @brief test regression de la class Plateau
         */
        static void TestRegression();

    private:
        std::vector <Case*> cases;  ///< les 40 cases du plateau 
        std::vector <Propriete*> TodoProprietes;    ///< les 40 cases du plateau
        std::vector <Carte*> Examens;   ///< les cartes examens
        std::vector <Carte*> VieEtu;    ///< les cartes vie etu
    
};

#endif
#ifndef _DE_H
#define _DE_H

/**
 * @class De
 * @brief Donne une valeur aléatoire entre 1 et 6 comme un dé classique
 */

class De {
    private:
        int valeur; ///< résultat du dé 
        int nbFaces;    ///< nombre de faces du dé (6)
        

    public:
    /**
    * @brief constructeur par défaut dé à 6 faces
    */
    De();

    /**
     * @brief constructeur dé 
     * @param entier nombre de faces 
     */
    De(int faces);
    
    /**
     * @brief déstructeur dé
     */
    ~De();
        
    /**
     * @brief retourne la dernière valeur obtenue lors d'un lancé de dé
     */
        int getValeur() const;

        /**
         * @brief lance le dé, retourne une valeure aléatoire entre 1 et 6
         */
        int lancer();

};

#endif
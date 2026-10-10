#ifndef _BANQUE_H
#define _BANQUE_H

#include "Joueur.h"

/**
 * @class Banque
 * @brief banque du jeu pour gérer les transactions. 
 * Vérifier les transactions et le bon déroulement.
 */

class Banque {

private:
    int argentBanque; ///< argent de la banque (montant très grand)

public:
    /**
     * @brief constructeur par défaut de la banque 
     */
    Banque();

    /**
     * @brief déstructeur par défaut banque
     */
    ~Banque();

    /**
     * @brief retourne l'argent de la banque
     */
    int getArgentBanque() const;

    /**
     * @brief vérifier qu'un joueur a l'argent nécessaire
     * @param j pointeur sur joueur à vérifier
     * @param montant est la somme d'argent à vérifier 
     */
    bool verifierArgent(Joueur* j, int montant);

    /**
     * @brief quand un joueur doit une somme à personne ex:case taxe
     * @param joueur pointeur sur le joueur qui doit payer 
     * @param montant l'argent à payer 
     */
    void payerJoueur(Joueur* joueur, int montant);

    /**
     * @brief quand un joueur doit recevoir de l'argent pas d'un joueur ex: case départ
     * @param joueur pointeur sur le joueur qui doit recevoir
     * @param montant l'argent à recevoir
     */
    void recevoirJoueur(Joueur* joueur, int montant);

    /**
     * @brief test de regression Banque
     */
    static void TestRegression();
};

#endif
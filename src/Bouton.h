#ifndef BOUTON_H
#define BOUTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

/**
 * @class Bouton
 * @brief bouton graphique cliquable SDL avec effet de survol et animation
 */

class Bouton {
public:

    /**
     * @brief constructeur par défaut
     */
    Bouton();

    /**
     * @brief destructeur Bouton
     */
    ~Bouton();

    /**
     * @brief charge la texture du bouton et le positionne
     * @param renderer moteur de rendu SDL
     * @param path chemin vers l'image du bouton
     * @param x coordonnée x
     * @param y coordonnée y
     * @param w largeur
     * @param h hauteur
     */
    bool load(SDL_Renderer* renderer, const std::string& path, int x, int y, int w, int h);

    /**
     * @brief met à jour l'état du bouton à partir d'un évènement SDL
     * @param e évènement SDL à traiter
     */
    void gestEvent(const SDL_Event e);

    /**
     * @brief met à jour l'animation du bouton (interpolation d'échelle)
     */
    void update();

    /**
     * @brief affiche le bouton à l'écran
     * @param renderer moteur de rendu SDL
     */
    void render(SDL_Renderer* renderer);

    /**
     * @brief consomme un éventuel clic en attente, retourne vrai si un clic était présent
     */
    bool consommerClic();

    /**
     * @brief réinitialise l'état du bouton (clic et survol)
     */
    void reset();

    /**
     * @brief retourne vrai si le bouton vient d'être cliqué
     */
    bool estClique() const;

    /**
     * @brief retourne vrai si la souris survole le bouton
     */
    bool estSurvole() const;

    /**
     * @brief retourne la texture du bouton
     */
    SDL_Texture* getTexture() const;

    /**
     * @brief définit la position du bouton
     * @param x coordonnée x
     * @param y coordonnée y
     */
    void setPosition(int x, int y);

    /**
     * @brief définit la taille du bouton
     * @param w largeur
     * @param h hauteur
     */
    void setSize(int w, int h);


    /**
     * @brief libère explicitement la texture du bouton
     */
    void liberer();

private:
    SDL_Rect rect;          ///< rectangle de placement du bouton
    SDL_Texture* texture;   ///< texture du bouton

    bool survole;           ///< vrai si la souris survole le bouton
    bool clique;            ///< vrai si un clic est en attente

    float scale;            ///< échelle courante (animation)
    float targetScale;      ///< échelle cible (animation)

    /**
     * @brief retourne vrai si la souris est dans le rectangle du bouton
     * @param mx coordonnée x de la souris
     * @param my coordonnée y de la souris
     */
    bool mouseSurBouton(int mx, int my);
};

#endif
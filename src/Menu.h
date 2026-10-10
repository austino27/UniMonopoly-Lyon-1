#ifndef _MENU_H
#define _MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Bouton.h"

#include <SDL2/SDL_mixer.h>



class MenuSDL {
public:
    MenuSDL(SDL_Window* win, SDL_Renderer* rend);
    ~MenuSDL();
    
    std::string demanderNomJoueur(int numero);
    int choisirPion(int numeroJoueur);
    void initBoutons();
    int afficherMenuPrincipalGraphique();
    int demanderNbJoueur() ;
    void afficherLogo();

    void basculerFullscreen();

private:

    int winWidth, winHeight;
    
    Bouton jouer;
    Bouton regle;
    Bouton param;
    Bouton credits;
    Bouton quitter;
    Bouton valider;

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* backgroundTexture;
    SDL_Surface* bgSurface;

    SDL_Texture* logoTexture;
    SDL_Surface* logoSurface;

    Mix_Music* musiqueMenu;
/*
    SDL_Texture* jouerTexture;
    SDL_Surface* jouerSurface;

    SDL_Texture* creditsTexture;
    SDL_Surface* creditsSurface;

    SDL_Texture* quitterTexture;
    SDL_Surface* quitterSurface;
*/


    bool pleinEcran = true;

    void afficherTexte(const std::string& texte, int x, int y, SDL_Color couleur, int taille) const ;
};

#endif



#ifndef _JEUSDL_H
#define _JEUSDL_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Propriete.h"
#include "Jeu.h"
#include "Bouton.h"
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
using namespace std;

class GestionnaireParties; 

class JeuSDL {
    public:
        JeuSDL();
        ~JeuSDL();

        void initCases();
        void initBoutons();
        
        void afficherFenetre();

        void chargerPions();
        void afficherPions();

        void chargerRessources();
        void afficherTexte(string txt, int x, int y, SDL_Color c, TTF_Font* font) const;

        void afficherOUI_NON() ;
        bool demanderAchat();
        void afficherInfoTour() const;
        //void afficherInfoCarte() const;
        void dessinerInfoJoueur(int x, int y, int w,int z);

        Propriete* proprieteCliquee(int mouseX, int mouseY) const;
        void dessinerCarteEnGrand(int posCase, Propriete* p) const;
        void hypothequerProp();
        void leverHypothequeSDL();
        void echangeSDL();

        void setJeu(Jeu* j); 
        void setGestionnaire(GestionnaireParties* g);

        void basculerFullscreen();
        void afficherPlat();

        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();

        static void TestRegression(); 
        
    private:
        
            Jeu* jeu;
            SDL_Rect casesGraphiques[40];
            GestionnaireParties* gestionnaire;
            SDL_Window* window;
            SDL_Renderer* renderer;


            SDL_Surface* bgSurface;
            SDL_Texture* backgroundTexture;

            SDL_Surface* surfacePlateau;
            SDL_Texture* texturePlateau;

            SDL_Surface* infos_joueurSurface;

            SDL_Texture* texture_infos_joueur;

            SDL_Texture* texturesCases[40];

            SDL_Surface* pion1Surface;
            SDL_Surface* pion2Surface;
            SDL_Surface* pion3Surface;
            SDL_Surface* pion4Surface;
            SDL_Surface* pion5Surface;
            SDL_Surface* pion6Surface;
           

            SDL_Texture* texturePion1;
            SDL_Texture* texturePion2;
            SDL_Texture* texturePion3;
            SDL_Texture* texturePion4;
            SDL_Texture* texturePion5;
            SDL_Texture* texturePion6;

            SDL_Texture* texturePions[6];
            TTF_Font* fontGrand;
            TTF_Font* fontMoyen;
            
            Mix_Music* musiquePartie;

            std::vector<SDL_Rect> hitboxProps;
            std::vector<Propriete*> hitboxPropRefs;
            
            bool pleinEcran;
             
            Bouton oui;
            Bouton non;
            Bouton lancer;

};

#endif


// tirer une carte en cliquant sur la carte avec la souris
// lancer de dés en 3D
// Affichage des info sur les coter , regler l'affichage du plateau
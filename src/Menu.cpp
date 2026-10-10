#include "Menu.h"
#include <iostream>
#include <unistd.h>
using namespace std;

const int MAX_CARACTERES = 12;
int scale = 2;


MenuSDL::MenuSDL(SDL_Window* win, SDL_Renderer* rend)
    : window(win), renderer(rend), font(nullptr), backgroundTexture(nullptr), musiqueMenu(nullptr), pleinEcran(true)
{
    if (TTF_Init() < 0) {
        cerr << "Erreur TTF_Init: " << TTF_GetError() << endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cerr << "Erreur Mix_OpenAudio : " << Mix_GetError() << endl;
    }

    font = TTF_OpenFont("data/Fonts/Poppins-Bold.ttf", 32);
    if (!font) {
        cerr << "Erreur chargement font: " << TTF_GetError() << endl;
    }

    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_AVIF) & (IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_AVIF)) == 0) {
        cerr << "Erreur initialisation SDL_image: " << IMG_GetError() << endl;
        return;
    }

    logoSurface = IMG_Load("data/Menu/logo.png");
    if (!logoSurface) {
        cerr << "Erreur chargement logo : " << IMG_GetError() << endl;
    } else {
        logoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);
        SDL_FreeSurface(logoSurface);
        if (!logoTexture)
            cerr << "Erreur texture logo : " << SDL_GetError() << endl;
    }


    bgSurface = IMG_Load("data/Menu/Background_blur.png");
    if (!bgSurface) {
        cerr << "Erreur chargement background: " << IMG_GetError() << endl;
    } else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
        if (!backgroundTexture)
            cerr << "Erreur texture background: " << SDL_GetError() << endl;
    }
    initBoutons();
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    musiqueMenu = Mix_LoadMUS("data/Musics/Menu.mp3");

    if (!musiqueMenu)
    {
        cerr << "Erreur chargement musique menu : " << Mix_GetError() << endl;
    }
    else
    {
        Mix_PlayMusic(musiqueMenu, -1); // boucle infinie
    }
}

MenuSDL::~MenuSDL()
{
    if (musiqueMenu)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(musiqueMenu);
    }

    Mix_CloseAudio();

    if (font)
        TTF_CloseFont(font);

    if (backgroundTexture)
        SDL_DestroyTexture(backgroundTexture);

    if (logoTexture)
        SDL_DestroyTexture(logoTexture);

    TTF_Quit();
}

void MenuSDL::basculerFullscreen() {
    if (pleinEcran) {
       
        SDL_SetWindowFullscreen(window, 0);           // quitter full screen
        SDL_SetWindowSize(window, 1280, 900);         // taille fenêtre souhaitée
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        pleinEcran = false;
    } else {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // retour full screen
        pleinEcran = true;
    }
}

void MenuSDL::initBoutons()
{
    SDL_GetWindowSize(window, &winWidth, &winHeight);
    float scale = 1.4f;

    int bw = 250;
    int bh = 80;

    jouer.load(renderer, "data/Menu/Bouton/Jouer.png",
            winWidth/5, winHeight/4,
            (int)(bw * scale), (int)(bh * scale));

    regle.load(renderer, "data/Menu/Bouton/Regle.png",
            winWidth/5, winHeight/4 + 120,
            (int)(bw * scale), (int)(bh * scale));

    param.load(renderer, "data/Menu/Bouton/Param.png",
            winWidth/5, winHeight/4 + 240,
            (int)(bw * scale), (int)(bh * scale));

    credits.load(renderer, "data/Menu/Bouton/Credits.png",
                winWidth/5, winHeight/4 + 360,
                (int)(bw * scale), (int)(bh * scale));

    quitter.load(renderer, "data/Menu/Bouton/Quitter.png",
                winWidth/5, winHeight/4 + 480,
                (int)(bw * scale), (int)(bh * scale));

    valider.load(renderer, "data/Menu/Bouton/Valider.png",
             winWidth/2 - 290,
             winHeight * 3/6,
             (int)(400*scale),(int)(250*scale));
}

void MenuSDL::afficherTexte(const std::string& texte, int x, int y, SDL_Color couleur, int taille) const
{
    if (texte.empty() || !renderer || !font) return;

    TTF_Font* fontTaille = TTF_OpenFont("data/Fonts/Poppins-Bold.ttf", taille);
    if (!fontTaille) return;

    SDL_Surface* texteSurface = TTF_RenderUTF8_Solid(fontTaille, texte.c_str(), couleur);
    if (!texteSurface) { TTF_CloseFont(fontTaille); return; }

    SDL_Texture* texteTexture = SDL_CreateTextureFromSurface(renderer, texteSurface);
    SDL_Rect rect = {x, y, texteSurface->w, texteSurface->h};
    SDL_RenderCopy(renderer, texteTexture, NULL, &rect);

    SDL_DestroyTexture(texteTexture);
    SDL_FreeSurface(texteSurface);
    TTF_CloseFont(fontTaille);
}

int MenuSDL::demanderNbJoueur() 
{
    bool quit = false;
    SDL_Event event;
    int nbJoueurs = 2;
    valider.reset();

    valider.setPosition(winWidth/2 - 290, winHeight * 4/6);
    
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_f)
                    basculerFullscreen();

                /*
                if (event.key.keysym.sym == SDLK_RETURN)
                    quit = true;
                */

                // avec fleche
                if (event.key.keysym.sym == SDLK_UP) 
                {
                    if (nbJoueurs < 6)
                    nbJoueurs++;
                }
                if (event.key.keysym.sym == SDLK_DOWN) 
                {
                    if (nbJoueurs > 2)
                    nbJoueurs--;
                }
                
            }
            valider.gestEvent(event);

            // avec molette
            if (event.type == SDL_MOUSEWHEEL)
            {
                //cout << "molette : " << event.wheel.y << endl;
                if (event.wheel.y > 0 && nbJoueurs < 6)
                    nbJoueurs++;

                if (event.wheel.y < 0 && nbJoueurs > 2)
                    nbJoueurs--;
            }
        }

        valider.update();
        if (valider.consommerClic())
                        quit = true;

        SDL_GetWindowSize(window, &winWidth, &winHeight);

        SDL_RenderClear(renderer);

        if (backgroundTexture)
        {
            SDL_Rect dst = {0, 0, winWidth, winHeight};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
        }

        afficherTexte("UniMonopoly Lyon 1",
                      winWidth/2 - 330,
                      winHeight* 1/6,
                      {255,255,255,255}, 64);

        afficherTexte("Molette souris pour choisir (2 - 6 joueurs)",
                      winWidth /2 - 350,
                      winHeight* 4 /6,
                      {255,255,255,255}, 32);

        afficherTexte("Joueurs : " + std::to_string(nbJoueurs),
                      winWidth/2 - 150,
                      winHeight * 3/6,
                      {255,255,255,255}, 48);

        valider.render(renderer);
        SDL_RenderPresent(renderer);
    }

    return nbJoueurs;
}

//Menu avec Boutton
int MenuSDL::afficherMenuPrincipalGraphique()
{
    SDL_Event event;
    bool quit = false;

    
    while (!quit)
    {
        SDL_GetWindowSize(window, &winWidth, &winHeight);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 4;

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_f)
                    basculerFullscreen();
            }

            jouer.gestEvent(event);
            regle.gestEvent(event);
            param.gestEvent(event);
            credits.gestEvent(event);
            quitter.gestEvent(event);
        }

        jouer.update();
        regle.update();
        param.update();
        credits.update();
        quitter.update();

        if (jouer.consommerClic()) return 0;
        if (regle.consommerClic()) return 1;
        if (param.consommerClic()) return 2;
        if (credits.consommerClic()) return 3;
        if (quitter.consommerClic()) return 4;

        
       

        SDL_RenderClear(renderer);

        if (backgroundTexture)
        {
            SDL_Rect dst = {0, 0, winWidth, winHeight};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
        }

        jouer.render(renderer);
        regle.render(renderer);
        param.render(renderer);
        credits.render(renderer);
        quitter.render(renderer);

        afficherLogo();

        SDL_RenderPresent(renderer);
    }

    return 4;
}

void MenuSDL::afficherLogo()
{

    SDL_Rect posLogo;
    posLogo.x = winWidth * 2 / 6 + 150;
    posLogo.y = winHeight * 0 / 6 + 150;
    posLogo.w = 1210;
    posLogo.h = 790;

    if (logoTexture) {
        SDL_RenderCopy(renderer, logoTexture, NULL, &posLogo);
    }
}

string MenuSDL::demanderNomJoueur(int numero)
{
    SDL_StartTextInput();
    valider.reset();

    bool erreurNom = false;
    bool quit = false;
    SDL_Event event;
    std::string nom = "";

    SDL_Rect champTexte = {winWidth/2 - 160 , winHeight * 3/6 , 300, 50};

    valider.setPosition(winWidth/2 - 290, winHeight * 3/6);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return "";

            if (event.type == SDL_TEXTINPUT)
            {
                if (nom.length() < MAX_CARACTERES)
                    nom += event.text.text;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && !nom.empty())
                    nom.pop_back();
            }

            valider.gestEvent(event);

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                bool clicValider = valider.consommerClic();

                if (clicValider && !nom.empty())
                {
                    quit = true;
                }
                else if (clicValider && nom.empty())
                {
                    erreurNom = true;
                }
            }
        }

        valider.update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 50, 255);
        SDL_RenderClear(renderer);

        if (backgroundTexture)
        {
            SDL_Rect dst = {0, 0, winWidth, winHeight};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
        }

        if (erreurNom)
        {
            afficherTexte("Saisie impossible : Veuillez écrire un nom !!!",
                        winWidth/2 - 390,
                        winHeight * 5/6,
                        {255,0,0,255}, 32);
        }

        afficherTexte("Nom du joueur " + std::to_string(numero),
                      winWidth/2 - 280,
                      winHeight * 2/6,
                      {255,255,255,255},
                      64);

        int textW = 0;
        int textH = 0;
        TTF_SizeText(font, nom.c_str(), &textW, &textH);

        int textX = champTexte.x + (champTexte.w - textW) / 2;
        int textY = champTexte.y + (champTexte.h - textH) / 2;

        afficherTexte(nom, textX, textY, {255,255,255,255}, 32);

        valider.render(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    return nom;
}

int MenuSDL::choisirPion(int numeroJoueur)
{
    SDL_Event event;
    bool choisi = false;
    int pionChoisi = -1;

    SDL_Texture* texturesPions[6];
    string chemins[6] = {
        "data/UniPions/UniPion1.png",
        "data/UniPions/UniPion2.png",
        "data/UniPions/UniPion3.png",
        "data/UniPions/UniPion4.png",
        "data/UniPions/UniPion5.png",
        "data/UniPions/UniPion6.png"
    };

    valider.reset();
    valider.setPosition(winWidth/2 - 290, winHeight * 4/6);

    for (int i = 0; i < 6; i++)
    {
        SDL_Surface* surf = IMG_Load(chemins[i].c_str());
        if (!surf)
        {
            std::cout << "Erreur chargement pion " << i << " : " << IMG_GetError() << std::endl;
            texturesPions[i] = nullptr;
        }
        else
        {
            texturesPions[i] = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
        }
    }

   
    SDL_Rect pionsRect[6];
    for (int i = 0; i < 6; i++)
    {
        pionsRect[i] = {(winWidth * (1 + i) / 6) - 250 , winHeight * 3/6, 200, 200};
    }

    while (!choisi)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return -1;

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x;
                int y = event.button.y;

                for (int i = 0; i < 6; i++)
                {
                    if (x >= pionsRect[i].x && x <= pionsRect[i].x + pionsRect[i].w &&
                        y >= pionsRect[i].y && y <= pionsRect[i].y + pionsRect[i].h)
                    {
                        pionChoisi = i; 
                    }
                }
            }

            valider.gestEvent(event);
        }

        valider.update();

        if (valider.consommerClic() && pionChoisi != -1)
        {
            choisi = true; 
        }

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (backgroundTexture)
        {
            SDL_Rect dst = {0, 0, winWidth, winHeight};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
        }

        afficherTexte("Joueur " + std::to_string(numeroJoueur) + " : Choisissez votre pion",
            winWidth / 2 - 530, winHeight * 2 / 6,
            {255,255,255,255}, 64);

        for (int i = 0; i < 6; i++)
        {
            if (texturesPions[i])
                SDL_RenderCopy(renderer, texturesPions[i], NULL, &pionsRect[i]);

            if (i == pionChoisi)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer, &pionsRect[i]);
            }
        }

        if (pionChoisi == -1)
            SDL_SetTextureAlphaMod(valider.getTexture(), 120);
        else
            SDL_SetTextureAlphaMod(valider.getTexture(), 255);

        valider.render(renderer);

        SDL_RenderPresent(renderer);
}

    for (int i = 0; i < 6; i++)
    {
        if (texturesPions[i])
            SDL_DestroyTexture(texturesPions[i]);
    }

    valider.render(renderer);
    SDL_RenderPresent(renderer);

    return pionChoisi;
}



/*

Menu avec fleche

int MenuSDL::afficherMenuPrincipalGraphique()
{
    SDL_Event event;
    bool quit = false;

    int menuCourant = 0;
    std::string options[5] = { "Jouer", "Règle", "Paramètres", "Crédits", "Quitter" };

    SDL_Color couleurNormale = {255,255,255,255};
    SDL_Color couleurSelection = {255,200,0,255};
    int tailleTitre = 64;
    int tailleOption = 32;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return 4;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_f) basculerFullscreen();
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: menuCourant = (menuCourant + 5 - 1) % 5; break;
                    case SDLK_DOWN: menuCourant = (menuCourant + 1) % 5; break;
                    case SDLK_RETURN: return menuCourant;
                }
            }
        }

        int winWidth, winHeight;
        SDL_GetWindowSize(window, &winWidth, &winHeight);

        SDL_RenderClear(renderer);

        if (backgroundTexture) {
            SDL_Rect dst = {0, 0, winWidth, winHeight};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
        }

        afficherTexte("UniMonopoly Lyon 1", winWidth/2 - 200, winHeight/5, {255,255,255,255}, tailleTitre);

        int startY = winHeight/2 - 100;
        for (int i = 0; i < 5; ++i) {
            SDL_Color couleur = (i == menuCourant) ? couleurSelection : couleurNormale;
            afficherTexte(options[i], winWidth/2 - 50, startY + i * 60, couleur, tailleOption);
        }

        SDL_RenderPresent(renderer);
    }

    return 4; // Quitter
}
*/

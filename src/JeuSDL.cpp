#include "JeuSDL.h"
#include "GestionnairePartiesSDL.h"
using namespace std;


JeuSDL::JeuSDL() : jeu(nullptr), gestionnaire(nullptr), window(nullptr), renderer(nullptr),
      surfacePlateau(nullptr),
      texturePlateau(nullptr),
      infos_joueurSurface(nullptr),
      texture_infos_joueur(nullptr),
      pion1Surface(nullptr), pion2Surface(nullptr), pion3Surface(nullptr),
      pion4Surface(nullptr), pion5Surface(nullptr), pion6Surface(nullptr),
      texturePion1(nullptr), texturePion2(nullptr),
      texturePion3(nullptr), texturePion4(nullptr),
      texturePion5(nullptr),
      texturePion6(nullptr),
      fontGrand(nullptr), fontMoyen(nullptr),
      musiquePartie(nullptr),
      pleinEcran(false)
      
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Erreur SDL: " << SDL_GetError() << endl;
        return;
    }

    for (int i = 0; i < 40; i++) texturesCases[i] = nullptr;
    for (int i = 0; i < 6;  i++) texturePions[i]  = nullptr;

    if (IMG_Init(IMG_INIT_AVIF | IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        cerr << "Erreur initialisation SDL_image: " << IMG_GetError() << std::endl;
        return;
    }
    window = SDL_CreateWindow("UniMonopoly Lyon 1",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              0, 0,
                              SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        cerr << "Erreur création fenêtre: " << SDL_GetError() << endl;
        SDL_Quit();
        return;
    }

    

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Erreur création renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    bgSurface = IMG_Load("data/BJeuSDL_flou.jpg");
    if (!bgSurface) {
        cerr << "Erreur chargement background: " << IMG_GetError() << endl;
    } else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
        if (!backgroundTexture)
            cerr << "Erreur texture background: " << SDL_GetError() << endl;
    }

    TTF_Init();
    fontGrand = TTF_OpenFont("data/font.ttf", 24);
    fontMoyen = TTF_OpenFont("data/font.ttf", 18);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cerr << "Erreur Mix_OpenAudio : " << Mix_GetError() << endl;
    }

    musiquePartie = Mix_LoadMUS("data/Musics/Background.mp3");

    if (!musiquePartie)
    {
        cerr << "Erreur chargement musique partie : " << Mix_GetError() << endl;
    }
}

JeuSDL::~JeuSDL()
{
    if (texturePion1) SDL_DestroyTexture(texturePion1);
    if (texturePion2) SDL_DestroyTexture(texturePion2);
    if (texturePion3) SDL_DestroyTexture(texturePion3);
    if (texturePion4) SDL_DestroyTexture(texturePion4);
    if (texturePion5) SDL_DestroyTexture(texturePion5);
    if (texturePion6) SDL_DestroyTexture(texturePion6);
    if (texturePlateau) SDL_DestroyTexture(texturePlateau);


    if (surfacePlateau) SDL_FreeSurface(surfacePlateau);

    Mix_HaltMusic();

    if (musiquePartie)
        Mix_FreeMusic(musiquePartie);

    Mix_CloseAudio();


    if (backgroundTexture)
        SDL_DestroyTexture(backgroundTexture);

    for (int i = 0; i < 40; i++)
        if (texturesCases[i]) SDL_DestroyTexture(texturesCases[i]);

    if (texture_infos_joueur) SDL_DestroyTexture(texture_infos_joueur);
    texture_infos_joueur = nullptr;

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    if (fontGrand) TTF_CloseFont(fontGrand);
    if (fontMoyen) TTF_CloseFont(fontMoyen);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void JeuSDL::initBoutons() 
{
    int winWidth,winHeight;
    SDL_GetWindowSize(window,&winWidth,&winHeight);

    float scale = 1.4f;

    int bw = 150;
    int bh = 40;

    oui.load(renderer,  "data/BoutonsJeu/Oui.png" ,winWidth * 4/6 , winHeight * 4/6 ,(int)(bw * scale), (int)(bh * scale));
    non.load(renderer, "data/BoutonsJeu/Non.png" ,winWidth * 5/6 ,  winHeight * 4/6 , (int)(bw * scale), (int)(bh * scale));
    lancer.load(renderer, "data/BoutonsJeu/Lancer.png" ,  winWidth * 4/6 , winHeight * 5/6 , (int)(250 * scale), (int)(80 * scale));

}

void JeuSDL::initCases()
{
    int plateau = 900;
    int nbCasesCote = 11; 
    int taille = plateau / nbCasesCote;  // ≈81
    int max = plateau - taille;

    // bas
    for(int i=0;i<10;i++)
    {
        casesGraphiques[i] = {max - i*taille, max, taille, taille};
    }

    // gauche
    for(int i=10;i<20;i++)
    {
        casesGraphiques[i] = {0, max - (i-10)*taille, taille, taille};
    }

    // haut
    for(int i=20;i<30;i++)
    {
        casesGraphiques[i] = {(i-20)*taille, 0, taille, taille};
    }

    // droite
    for(int i=30;i<40;i++)
    {
        casesGraphiques[i] = {max,  (nbCasesCote - 1 - (i-30)) *taille, taille, taille};
    }
}

void JeuSDL::setGestionnaire(GestionnaireParties* g)
{
    gestionnaire = g;
}

SDL_Window* JeuSDL::getWindow()
{
    return window;
}

SDL_Renderer* JeuSDL::getRenderer()
{
    return renderer;
}

void JeuSDL::setJeu(Jeu* j) { jeu = j; }

void JeuSDL::chargerPions()
{
    pion1Surface = IMG_Load("data/UniPions/UniPion1.png");
    pion2Surface = IMG_Load("data/UniPions/UniPion2.png");
    pion3Surface = IMG_Load("data/UniPions/UniPion3.png");
    pion4Surface = IMG_Load("data/UniPions/UniPion4.png");
    pion5Surface = IMG_Load("data/UniPions/UniPion5.png");
    pion6Surface = IMG_Load("data/UniPions/UniPion6.png");

    if (!pion1Surface || !pion2Surface || !pion3Surface || !pion4Surface || !pion5Surface || !pion6Surface)
    {
        cout << "Erreur chargement pion: " << IMG_GetError() << endl;
        return;
    }

    texturePion1 = SDL_CreateTextureFromSurface(renderer, pion1Surface);
    texturePion2 = SDL_CreateTextureFromSurface(renderer, pion2Surface);
    texturePion3 = SDL_CreateTextureFromSurface(renderer, pion3Surface);
    texturePion4 = SDL_CreateTextureFromSurface(renderer, pion4Surface);
    texturePion5 = SDL_CreateTextureFromSurface(renderer, pion5Surface);
    texturePion6 = SDL_CreateTextureFromSurface(renderer, pion6Surface);

    SDL_FreeSurface(pion1Surface);
    SDL_FreeSurface(pion2Surface);
    SDL_FreeSurface(pion3Surface);
    SDL_FreeSurface(pion4Surface);
    SDL_FreeSurface(pion5Surface);
    SDL_FreeSurface(pion6Surface);

    texturePions[0] = texturePion1;
    texturePions[1] = texturePion2;
    texturePions[2] = texturePion3;
    texturePions[3] = texturePion4;
    texturePions[4] = texturePion5;
    texturePions[5] = texturePion6;
}

void JeuSDL::basculerFullscreen() {
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


void JeuSDL::afficherPions()
{
    if(!jeu) return;
    const auto& joueurs = jeu->getJoueurs();
    if(joueurs.empty()) return;

    for (size_t i = 0; i < joueurs.size(); ++i)
    {
        int pos = joueurs[i]->getPosition();
        if (pos < 0 || pos >= 40) continue;  // sécurité

        SDL_Rect baseCase = casesGraphiques[pos];

        SDL_Rect dst;
        dst.w = 40;
        dst.h = 40;

        // Centrer le pion sur la case
        dst.x = baseCase.x + (baseCase.w - dst.w) / 2;
        dst.y = baseCase.y + (baseCase.h - dst.h) / 2;

        // Décaler légèrement pour plusieurs joueurs sur la même case
        dst.x += (i % 2) * 20;  // décalage horizontal max 20px
        dst.y += (i / 2) * 20;  // décalage vertical si plus de 2 joueurs

        int id = joueurs[i]->getPion();
        SDL_Texture* textures[6] = {
            texturePion1,
            texturePion2,
            texturePion3,
            texturePion4,
            texturePion5,
            texturePion6,
        };

        SDL_Texture* texture = textures[id];
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
}


void JeuSDL::chargerRessources()
{
    infos_joueurSurface = IMG_Load("data/infos_Joueurs/template_infos_joueur.png");

    if (!infos_joueurSurface)
    {
        cout << "Erreur chargement infos_joueur: " << IMG_GetError() << endl;
        return;
    }

    texture_infos_joueur = SDL_CreateTextureFromSurface(renderer, infos_joueurSurface);

    SDL_FreeSurface(infos_joueurSurface);

    for (int i = 0; i < 40; i++) {
    string chemin = "data/Cases/case_" + to_string(i) + ".png";
    SDL_Surface* cs = IMG_Load(chemin.c_str());
    if (cs) {
        texturesCases[i] = SDL_CreateTextureFromSurface(renderer, cs);
        SDL_FreeSurface(cs);
    }
}

}

void JeuSDL::afficherTexte(string txt, int x, int y, SDL_Color c, TTF_Font* font) const
{
    SDL_Surface* surf = TTF_RenderText_Blended(font, txt.c_str(), c);
    if (!surf) return;

    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst = {x, y, surf->w, surf->h};

    SDL_RenderCopy(renderer, text, NULL, &dst);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(text);
}

void JeuSDL::dessinerInfoJoueur(int x, int y, int w,int z) 
{

    if (!jeu) return;
    hitboxProps.clear();
    hitboxPropRefs.clear();
    Joueur* j = jeu->getJoueurs()[jeu->getJoueurCourant()];
 
    //template infos joueur 
    SDL_Rect rectFond = {x, y, w, z};
    if (texture_infos_joueur) {
        SDL_RenderCopy(renderer, texture_infos_joueur, NULL, &rectFond);
    }
 
    //affichage pion joueur
    int id = j->getPion();
    if (id < 0 || id >= 6)
    {
        cerr << "ERREUR PION ID = " << id << endl;
    }
    SDL_Rect rectPion = {x + 15, y + 15, 60, 60};
        SDL_RenderCopy(renderer, texturePions[id], NULL, &rectPion);
 
    //affichage nom et argent
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 220, 50, 255};
 
    int texteX = x + 90;
    afficherTexte(j->getNom(), texteX, y + 20, blanc, fontGrand);
    afficherTexte(to_string(j->getArgent()) + " credits",
                  texteX + 300, y +125 , jaune, fontMoyen);
 
    //affichage propriétés joueur
    vector<Propriete*> props = j->getProprietes();
    
 
    // Paramètres de la grille
    int Lprop = 60;
    int Hprop = 90;
    int espaceP = 20;
    int posGrilleX = x + 85;
    int posGrilleY = y + 220;
 
    for (size_t i = 0; i < props.size(); i++) {
        SDL_Rect dstProp;
        dstProp.x = posGrilleX + static_cast<int>(i) * espaceP;
        dstProp.y = posGrilleY;
        dstProp.w = Lprop;
        dstProp.h = Hprop;
 
        int pos = props[i]->getCase()->getPos();

        hitboxProps.push_back(dstProp);
        hitboxPropRefs.push_back(props[i]);

        SDL_RenderCopy(renderer, texturesCases[pos], NULL, &dstProp);
        
    }

}

void JeuSDL::dessinerCarteEnGrand(int posCase, Propriete* p) const
{
    if (posCase < 0 || posCase >= 40 || !texturesCases[posCase]) return;

    int winW, winH;
    SDL_GetWindowSize(window, &winW, &winH);

    //Carte en grand, centrée
    int carteW = 300;
    int carteH = 450;
    SDL_Rect dst = {
        (winW - carteW) / 2,
        (winH - carteH) / 2 - 40,  
        carteW, carteH
    };
    SDL_RenderCopy(renderer, texturesCases[posCase], NULL, &dst);

    //Texte sous la carte
    SDL_Color blanc = {255, 255, 255, 255};

    int txtY = dst.y + dst.h + 20;
    int txtX = dst.x - 50;  

    afficherTexte("Appuyez sur ECHAP pour continuer", txtX, txtY, blanc, fontMoyen);
}

Propriete* JeuSDL::proprieteCliquee(int x, int y) const
{

    for (int i = static_cast<int>(hitboxProps.size()) - 1; i >= 0; i--) {
        const SDL_Rect& r = hitboxProps[i];
        if (x >= r.x && x < r.x + r.w &&
            y >= r.y && y < r.y + r.h) {
            return hitboxPropRefs[i];
        }
    }
    return nullptr;
}

void JeuSDL::hypothequerProp()
{
    bool quit = false;
    SDL_Event event;

    SDL_Color blanc = {255,255,255,255};

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) 
            {
                    quit = true;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int x = event.button.x;
                int y = event.button.y;

                Propriete* p = proprieteCliquee(x, y);

                if (p!=nullptr && !(p->estHypotheque()))
                {

                    p->hypothequer();
                    int gain = p->getPrix() / 2;
                    cout << "Hypotheque OK : +" << gain << endl;
                }
                else
                {
                    cout << "Déjà hypothéquée ou clique à côté" << endl;
                }
            }
        }
        SDL_RenderClear(renderer);

        // Calcul du centrage du plateau
        int winWidth, winHeight;
        SDL_GetWindowSize(window, &winWidth, &winHeight);       

        SDL_Rect dstPlateau;
        dstPlateau.w = 900;
        dstPlateau.h = 900;
        dstPlateau.x = (winWidth - 900) / 4;
        dstPlateau.y = (winHeight - 900) / 2;
        SDL_RenderCopy(renderer, texturePlateau, NULL, &dstPlateau);

        int infosL = 600;
        int infosH = 450;  
        int posInfosX = dstPlateau.x + dstPlateau.w + 30; 
        int posInfosY = dstPlateau.y;

        dessinerInfoJoueur(posInfosX, posInfosY, infosL, infosH);

        afficherTexte("MODE HYPOTHEQUE - cliquez sur une propriete ESC pour quitter", 50, 50, blanc, fontMoyen);
        SDL_RenderPresent(renderer);

        int offsetX = dstPlateau.x;
        int offsetY = dstPlateau.y;
        
            const auto& joueurs = jeu->getJoueurs();
            for (size_t i = 0; i < joueurs.size(); ++i)
            {
                int pos = joueurs[i]->getPosition();
                if (pos < 0 || pos >= 40) continue;

                SDL_Rect baseCase = casesGraphiques[pos];

                SDL_Rect dst;
                dst.w = 40;
                dst.h = 40;
                dst.x = offsetX + baseCase.x + (baseCase.w - dst.w)/2 + (i % 2)*20;
                dst.y = offsetY + baseCase.y + (baseCase.h - dst.h)/2 + (i / 2)*20;

                int id = joueurs[i]->getPion();
                SDL_Texture* textures[6] = {
                    texturePion1,
                    texturePion2, 
                    texturePion3, 
                    texturePion4, 
                    texturePion5,
                    texturePion6
                };
                SDL_RenderCopy(renderer, textures[id], NULL, &dst);
            }
        
    }
}


void JeuSDL::leverHypothequeSDL()
{
    bool quit=false;
    SDL_Event event;

    SDL_Color blanc = {255,255,255,255};

    while(!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) 
            {
                    quit = true;
            }

        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x = event.button.x;
            int y = event.button.y;

            Propriete* p = proprieteCliquee(x,y);

            if(p==nullptr || !(p->estHypotheque()))
            {
                cout << "Clique à côté ou propriétée non hypothéquée" << endl;
            }
            else
            {
                p->leverHypotheque();

                int prix = (p->getPrix() / 2) + (p->getPrix()/10) ;
                    cout << "LeverHypotheque OK : -" << prix << endl;

            }

        }
    }
        SDL_RenderClear(renderer);

        // Calcul du centrage du plateau
        int winWidth, winHeight;
        SDL_GetWindowSize(window, &winWidth, &winHeight);       

        SDL_Rect dstPlateau;
        dstPlateau.w = 900;
        dstPlateau.h = 900;
        dstPlateau.x = (winWidth - 900) / 4;
        dstPlateau.y = (winHeight - 900) / 2;
        SDL_RenderCopy(renderer, texturePlateau, NULL, &dstPlateau);

        int infosL = 600;
        int infosH = 450;  
        int posInfosX = dstPlateau.x + dstPlateau.w + 30; 
        int posInfosY = dstPlateau.y;

        dessinerInfoJoueur(posInfosX, posInfosY, infosL, infosH);

        afficherTexte("MODE LEVER HYPOTHEQUE - cliquez sur une propriete , ESC pour quitter", 50, 50, blanc, fontMoyen);
        SDL_RenderPresent(renderer);
    }
}

void JeuSDL::echangeSDL()
{
    const auto& joueurs = jeu->getJoueurs();
    if (joueurs.empty()) return;

    Joueur* courant   = joueurs[jeu->getJoueurCourant()];
    Joueur* partenaire = nullptr;

    //phase 0 le joueur choisis son partenaire d'échange

    // phase 1 le joueur choisis les props qu'il veut de son partenaire d'échange (appuyer 0 pour aucune)

    // phase 2 il choisit le montant qu'il veut recevoir 

    // phase 3 le joueur courant choisit ses props à échanger 

    // phase 4 il choisit l'argent à donner 

    // phase 5 le joueur partenaire choisit si oui ou non il accepte l'échange

    // phase 6 si accepte faire l'échange argent et props 

    int phase = 0;

    vector<Propriete*> propsChoisiesPart;
    vector<Propriete*> propsChoisiesCour;
    int    montantPart = 0;
    int    montantCour = 0;
    string saisie;
    bool   accepte = false;

    vector<SDL_Rect>   hitboxPions;
    vector<Joueur*>    hitboxPionsRefs;

    int winW, winH;
    SDL_GetWindowSize(window, &winW, &winH);

    SDL_Rect dstPlateau = { (winW - 900) / 4, (winH - 900) / 2, 900, 900 };
    int posInfosX = dstPlateau.x + dstPlateau.w + 30;
    int posInfosY = dstPlateau.y;
    int infosL = 600, infosH = 450;

    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color jaune = {255, 220,  50, 255};

    SDL_StartTextInput();

    SDL_Event event;
    bool quit = false;

    while (!quit)
    {
        SDL_RenderClear(renderer);
        if (backgroundTexture) 
        {
            SDL_Rect dstBg = {0, 0, winW, winH};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &dstBg);
        }
        SDL_RenderCopy(renderer, texturePlateau, NULL, &dstPlateau);
        for (size_t i = 0; i < joueurs.size(); ++i) 
        {
            int pos = joueurs[i]->getPosition();
            if (pos < 0 || pos >= 40) continue;
            SDL_Rect bc = casesGraphiques[pos];
            SDL_Rect dst = {
                dstPlateau.x + bc.x + (bc.w - 40)/2 + (int)(i%2)*20,
                dstPlateau.y + bc.y + (bc.h - 40)/2 + (int)(i/2)*20,
                40, 40
            };
            int id = joueurs[i]->getPion();
            if (id >= 0 && id < 6)
                SDL_RenderCopy(renderer, texturePions[id], NULL, &dst);
        }

        switch (phase)
        {
            case 0:
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = true;
                            break; 
                        }

                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        int mx = event.button.x;
                        int my = event.button.y;
                        for (size_t i = 0; i < hitboxPions.size(); ++i) {
                            const SDL_Rect& r = hitboxPions[i];
                            if (mx >= r.x && mx < r.x+r.w && my >= r.y && my < r.y+r.h) {
                                partenaire = hitboxPionsRefs[i];
                                phase = 1;
                                break;
                            }
                        }
                    }
                }

                afficherTexte("ECHANGE - Cliquez sur le pion du joueur avec qui echanger (ESC pour annuler)",50, 50, blanc, fontMoyen);

                hitboxPions.clear();
                hitboxPionsRefs.clear();
                int count = 0;
                for (size_t i = 0; i < joueurs.size(); ++i)
                {
                    Joueur* jj = joueurs[i];
                    if (jj!= courant){

                    SDL_Rect r = {posInfosX + 20, posInfosY + 20 + count * 110, 80, 80};
                    int id = jj->getPion();

                    SDL_RenderCopy(renderer, texturePions[id], NULL, &r);

                    afficherTexte(jj->getNom(), r.x + 110, r.y + 20, blanc, fontGrand);
                    afficherTexte(to_string(jj->getArgent()) + " credits", r.x + 110, r.y + 50, jaune, fontMoyen);

                    hitboxPions.push_back(r);
                    hitboxPionsRefs.push_back(jj);
                    count++;
                    }
                }
                break;
            }

            case 1:
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        { 
                            quit = true; 
                            break; 
                        }

                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        Propriete* p = proprieteCliquee(event.button.x, event.button.y);

                        if(p != nullptr)
                        {
                            int foundIdx = -1;
                            for (int j = 0; j < (int)propsChoisiesPart.size(); j++)
                                if (propsChoisiesPart[j] == p) { foundIdx = j; break; }

                            if (foundIdx == -1) 
                            {
                                propsChoisiesPart.push_back(p);
                            }
                            else 
                            {
                                propsChoisiesPart.erase(propsChoisiesPart.begin() + foundIdx);
                            }
                        }
                    }

                    if (event.type == SDL_KEYDOWN)
                    {
                        SDL_Keycode k = event.key.keysym.sym;
                        if (k == SDLK_0 || k == SDLK_KP_0)
                            { 
                                propsChoisiesPart.clear();
                                phase = 2; 
                            }
                        else if (k == SDLK_RETURN || k == SDLK_KP_ENTER)
                            {
                                phase = 2;
                            }
                    }
                }

                SDL_Rect rectFond = {posInfosX, posInfosY, infosL, infosH};
                SDL_RenderCopy(renderer, texture_infos_joueur, NULL, &rectFond);

                int id = partenaire->getPion();
                SDL_Rect rectPion = {posInfosX + 15, posInfosY + 15, 60, 60};
                SDL_RenderCopy(renderer, texturePions[id], NULL, &rectPion);

                afficherTexte(partenaire->getNom(), posInfosX + 90, posInfosY + 20, blanc, fontGrand);
                afficherTexte(to_string(partenaire->getArgent()) + " credits", posInfosX + 390, posInfosY + 125, jaune, fontMoyen);

                hitboxProps.clear();
                hitboxPropRefs.clear();

                vector<Propriete*> props = partenaire->getProprietes();
                int Lprop      = 60;
                int Hprop      = 90;
                int espaceP    = 20;
                int posGrilleX = posInfosX + 85;
                int posGrilleY = posInfosY + 220;

                for (size_t i = 0; i < props.size(); i++)
                {
                    SDL_Rect dstProp;
                    dstProp.x = posGrilleX + static_cast<int>(i) * espaceP;
                    dstProp.y = posGrilleY;
                    dstProp.w = Lprop;
                    dstProp.h = Hprop;

                    int pos = props[i]->getCase()->getPos();
                    hitboxProps.push_back(dstProp);
                    hitboxPropRefs.push_back(props[i]);

                    if (pos >= 0 && pos < 40 && texturesCases[pos])
                        SDL_RenderCopy(renderer, texturesCases[pos], NULL, &dstProp);

                    bool selectionne = false;
                    for (size_t j = 0; j < propsChoisiesPart.size(); j++)
                        if (propsChoisiesPart[j] == props[i]) { selectionne = true; break; }

                    if (selectionne)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        SDL_Rect indicateur = { dstProp.x + dstProp.w/2 - 5, dstProp.y - 14, 10, 10 };
                        SDL_RenderFillRect(renderer, &indicateur);
                    }
                }

                afficherTexte("Proprietes de " + partenaire->getNom()+ " : cliquez pour (de)selectionner, 0 = aucune, ENTREE pour valider",50, 50, blanc, fontMoyen);
                break;
            }

            case 2:
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        { 
                            quit = true; 
                            break; 
                        }

                    if (event.type == SDL_TEXTINPUT)
                    {
                        char c = event.text.text[0];
                        if (c >= '0' && c <= '9' && saisie.size() < 9)
                        {
                            saisie += c;
                        }
                            
                    }

                    if (event.type == SDL_KEYDOWN)
                    {
                        SDL_Keycode k = event.key.keysym.sym;
                        if (k == SDLK_BACKSPACE && !saisie.empty())
                            saisie.pop_back();
                        else if (k == SDLK_RETURN || k == SDLK_KP_ENTER)
                        {
                            if (!saisie.empty()) 
                            {
                                montantPart = atoi(saisie.c_str());
                            } 
                            else 
                            {
                                montantPart = 0;
                            }
                            saisie.clear();
                            phase = 3;
                        }
                    }
                }

                afficherTexte("Selectionner le montant demande a " + partenaire->getNom()+ " (chiffres puis ENTREE, 0 pour aucun)",50, 50, blanc, fontMoyen);
                afficherTexte((saisie.empty() ? "0" : saisie) + " credits", 50, 100, jaune, fontGrand);
                break;
            }

            case 3:
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = true;
                            break; 
                        }

                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        Propriete* p = proprieteCliquee(event.button.x, event.button.y);

                        if(p != nullptr)
                        {
                            int foundIdx = -1;
                            for (int j = 0; j < (int)propsChoisiesCour.size(); j++)
                                if (propsChoisiesCour[j] == p) { foundIdx = j; break; }

                            if (foundIdx == -1) 
                            {
                                propsChoisiesCour.push_back(p);
                            }
                            else                
                            {
                                propsChoisiesCour.erase(propsChoisiesCour.begin() + foundIdx);
                            }
                        }
                    }

                    if (event.type == SDL_KEYDOWN)
                    {
                        SDL_Keycode k = event.key.keysym.sym;
                        if (k == SDLK_0 || k == SDLK_KP_0)
                            { 
                                propsChoisiesCour.clear();
                                phase = 4; 
                                }
                        else if (k == SDLK_RETURN || k == SDLK_KP_ENTER)
                            {
                                phase = 4;
                            }
                    }
                }

                SDL_Rect rectFond = {posInfosX, posInfosY, infosL, infosH};
                SDL_RenderCopy(renderer, texture_infos_joueur, NULL, &rectFond);

                int id = courant->getPion();
                SDL_Rect rectPion = {posInfosX + 15, posInfosY + 15, 60, 60};
                SDL_RenderCopy(renderer, texturePions[id], NULL, &rectPion);

                afficherTexte(courant->getNom(), posInfosX + 90, posInfosY + 20, blanc, fontGrand);
                afficherTexte(to_string(courant->getArgent()) + " credits", posInfosX + 390, posInfosY + 125, jaune, fontMoyen);

                hitboxProps.clear();
                hitboxPropRefs.clear();

                vector<Propriete*> props = courant->getProprietes();
                int Lprop      = 60;
                int Hprop      = 90;
                int espaceP    = 20;
                int posGrilleX = posInfosX + 85;
                int posGrilleY = posInfosY + 220;

                for (size_t i = 0; i < props.size(); i++)
                {
                    SDL_Rect dstProp;
                    dstProp.x = posGrilleX + static_cast<int>(i) * espaceP;
                    dstProp.y = posGrilleY;
                    dstProp.w = Lprop;
                    dstProp.h = Hprop;

                    int pos = props[i]->getCase()->getPos();
                    hitboxProps.push_back(dstProp);
                    hitboxPropRefs.push_back(props[i]);

                    if (pos >= 0 && pos < 40 && texturesCases[pos])
                        SDL_RenderCopy(renderer, texturesCases[pos], NULL, &dstProp);

                    bool selectionne = false;
                    for (size_t j = 0; j < propsChoisiesCour.size(); j++)
                        if (propsChoisiesCour[j] == props[i]) { selectionne = true; break; }

                    if (selectionne)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        SDL_Rect indicateur = { dstProp.x + dstProp.w/2 - 5, dstProp.y - 14, 10, 10 };
                        SDL_RenderFillRect(renderer, &indicateur);
                    }
                }

                afficherTexte("Vos proprietes, " + courant->getNom() + " : cliquez pour (de)selectionner, 0 = aucune, ENTREE pour valider",50, 50, blanc, fontMoyen);
                break;
            }

            case 4:
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        { quit = true; break; }

                    if (event.type == SDL_TEXTINPUT)
                    {
                        char c = event.text.text[0];
                        if (c >= '0' && c <= '9' && saisie.size() < 9)
                            saisie += c;
                    }

                    if (event.type == SDL_KEYDOWN)
                    {
                        SDL_Keycode k = event.key.keysym.sym;
                        if (k == SDLK_BACKSPACE && !saisie.empty())
                            saisie.pop_back();
                        else if (k == SDLK_RETURN || k == SDLK_KP_ENTER)
                        {
                            if (!saisie.empty()) {
                                montantCour = atoi(saisie.c_str());
                            } 
                            else 
                            {
                                montantCour = 0;
                            }
                            saisie.clear();
                            phase = 5;
                        }
                    }
                }

                afficherTexte("Selectionner le montant offert par " + courant->getNom() + " (chiffres puis ENTREE, 0 pour aucun)",50, 50, blanc, fontMoyen);
                afficherTexte(saisie + " credits", 50, 100, jaune, fontGrand);
                break;
            }

            case 5:
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            quit = true; 
                            break; 
                        }

                    if (event.type == SDL_KEYDOWN)
                    {
                        SDL_Keycode k = event.key.keysym.sym;
                        if(k == SDLK_1) 
                        { 
                            accepte = true;  
                            phase = 6; 
                        }
                        else if (k == SDLK_2) 
                        { 
                            accepte = false; 
                            phase = 6; 
                        }
                    }
                }
                afficherTexte("Acceptez vous l'echange ?   1 : oui    2 : non", 50, 50, blanc, fontGrand);

                int y = 120;
                afficherTexte("Propose par " + partenaire->getNom() + " :", 50, y, blanc, fontMoyen); y += 30;
                for (Propriete* p : propsChoisiesPart)
                    { afficherTexte(" - " + p->getCase()->getNom(), 70, y, jaune, fontMoyen); y += 25; }
                afficherTexte(" + " + to_string(montantPart) + " credits", 70, y, jaune, fontMoyen);
                y += 50;

                afficherTexte("Propose par " + courant->getNom() + " :", 50, y, blanc, fontMoyen); y += 30;
                for (Propriete* p : propsChoisiesCour)
                    { afficherTexte(" - " + p->getCase()->getNom(), 70, y, jaune, fontMoyen); y += 25; }
                afficherTexte(" + " + to_string(montantCour) + " credits", 70, y, jaune, fontMoyen);
                break;
            }

            case 6:
            {
                if (accepte && partenaire != nullptr)
                {
                    for (Propriete* p : propsChoisiesPart)
                    {
                        partenaire->vendrePropriete(p);
                        p->setProprietaire(courant);
                        courant->ajouterPropriete(p);
                    }
                    for (Propriete* p : propsChoisiesCour)
                    {
                        courant->vendrePropriete(p);
                        p->setProprietaire(partenaire);
                        partenaire->ajouterPropriete(p);
                    }
                    if(montantPart > 0) 
                    { 
                        partenaire->payer(montantPart); 
                        courant->recevoir(montantPart); 
                    }
                    if (montantCour > 0) 
                    { 
                        courant->payer(montantCour);    
                        partenaire->recevoir(montantCour); 
                    }
                }
                quit = true;
                break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
}

bool JeuSDL::demanderAchat()
{
    SDL_Event event;

    Propriete* propEnCours = jeu->getPropEnCours();
    Joueur* joueurEnCours = jeu->getJoueurEnCours();

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return false;

        
        oui.gestEvent(event);
        non.gestEvent(event);

        if (event.type == SDL_MOUSEBUTTONDOWN &&
            event.button.button == SDL_BUTTON_LEFT)
        {
          
            if (oui.consommerClic())
            {
                if (propEnCours && joueurEnCours)
                    propEnCours->acheter(joueurEnCours);

                jeu->setAttenteChoix(false);
                return true;
            }

            if (non.consommerClic())
            {
                jeu->setAttenteChoix(false);
                return false;
            }
        }
    }

    return false;
}

void JeuSDL::afficherOUI_NON() 
{
    Propriete* propEnCours = jeu->getPropEnCours();
    bool enAttenteChoix = jeu->getAttenteChoix();

    if (!enAttenteChoix|| !propEnCours) return;

    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    
    afficherTexte(
        "Voulez-vous acheter : " + propEnCours->getCase()->getNom(),
        winWidth * 4/6 , winHeight * 4/6 -50 ,
        {255,255,255,255},
        fontMoyen
    );

    
    oui.render(renderer);
    non.render(renderer);
}




void JeuSDL::afficherFenetre()
{
    bool quit = false;
    SDL_Event event;
    Propriete* propZoomee = nullptr;

    surfacePlateau = IMG_Load("data/Plateauv1.jpg");
    if (!surfacePlateau) {
        cerr << "Erreur chargement plateau: " << IMG_GetError() << endl;
        return;
    }

    if (musiquePartie)
    {
        Mix_PlayMusic(musiquePartie, -1);
    }

    texturePlateau = SDL_CreateTextureFromSurface(renderer, surfacePlateau);
    SDL_FreeSurface(surfacePlateau);

    initCases();
    initBoutons();
    chargerPions();
    chargerRessources();


    // Calcul du centrage du plateau
    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    SDL_Rect dstPlateau;
    dstPlateau.w = 900;
    dstPlateau.h = 900;
    dstPlateau.x = (winWidth - 900)/4;
    dstPlateau.y = (winHeight - 900)/2;

    while (!quit)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            quit = true;

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE && propZoomee)
                propZoomee = nullptr;

            if (event.key.keysym.sym == SDLK_2)
                hypothequerProp();

            if (event.key.keysym.sym == SDLK_3)
                leverHypothequeSDL();

            if (event.key.keysym.sym == SDLK_4)
                echangeSDL();
        }

        
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int mx = event.button.x;
            int my = event.button.y;

            if (propZoomee)
            {
                propZoomee = nullptr;
            }
            else
            {
                Propriete* p = proprieteCliquee(mx, my);
                if (p) propZoomee = p;
            }
        }
        lancer.gestEvent(event);

    }

    lancer.update();

    SDL_RenderClear(renderer);

    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    if (backgroundTexture)
    {
        SDL_Rect dst = {0, 0, winWidth, winHeight};
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &dst);
    }

    SDL_RenderCopy(renderer, texturePlateau, NULL, &dstPlateau);


    if (lancer.consommerClic())
    {
        cout << "CLICK LANCER DETECTE" << endl;
        if (!jeu->getAttenteChoix() && !propZoomee)
            gestionnaire->gererTour();
    }

    
    if (jeu)
    {
        const auto& joueurs = jeu->getJoueurs();

        for (size_t i = 0; i < joueurs.size(); ++i)
        {
            int pos = joueurs[i]->getPosition();
            if (pos < 0 || pos >= 40) continue;

            SDL_Rect baseCase = casesGraphiques[pos];

            SDL_Rect dst;
            dst.w = 40;
            dst.h = 40;
            dst.x = dstPlateau.x + baseCase.x + (baseCase.w - dst.w)/2 + (i % 2)*20;
            dst.y = dstPlateau.y + baseCase.y + (baseCase.h - dst.h)/2 + (i / 2)*20;

            SDL_Texture* textures[6] =
            {
                texturePion1, texturePion2, texturePion3,
                texturePion4, texturePion5, texturePion6
            };

            SDL_RenderCopy(renderer, textures[joueurs[i]->getPion()], NULL, &dst);
        }
    }

    int infosL = 600;
    int infosH = 450;
    int posInfosX = dstPlateau.x + dstPlateau.w + 30;
    int posInfosY = dstPlateau.y;

    dessinerInfoJoueur(posInfosX, posInfosY, infosL, infosH);
    afficherInfoTour();
    //afficherInfoCarte();

    lancer.render(renderer);

    if (jeu && jeu->getAttenteChoix())
    {
        demanderAchat();

        oui.update();
        non.update();

        afficherOUI_NON();
    }

    SDL_RenderPresent(renderer);
}

SDL_DestroyTexture(texturePlateau);
} 

/*void JeuSDL::afficherInfoCarte()
{
    int winWidth, winHeight;
    SDL_GetWindowSize(window,&winWidth,&winHeight);

    Carte* c = jeu->getCarteEnCours();
    if (!c) return;

    string texte = c->getDescription() ;
    

 
   afficherTexte(texte,
                    winWidth * 4/6,
                    winHeight*3/6 + 40,
                    {255,255,255,255},
                    fontMoyen);   
} */


void JeuSDL::afficherInfoTour() const 
{
    
    int winWidth, winHeight;
    SDL_GetWindowSize(window,&winWidth,&winHeight);

    Joueur* j = jeu->getJoueurs()[jeu->getJoueurCourant()];

    afficherTexte("C'est au tour de "  + j->getNom() , winWidth * 4/6, winHeight*3/6, {255,255,255,255}, fontMoyen);

    int resultat = jeu->getDernierResultatDe();

    if (resultat != -1) {
        string texte = "Resultat des des : " + std::to_string(resultat);

        afficherTexte(texte,
                    winWidth * 4/6,
                    winHeight*3/6 + 20,
                    {255,255,255,255},
                    fontMoyen);
    }
    else {
        afficherTexte("Aucun des lance",
                    winWidth * 4/6,
                    winHeight*3/6 + 20,
                    {255,255,255,255},
                    fontMoyen);
    }
}
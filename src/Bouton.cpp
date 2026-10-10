#include "Bouton.h"
#include <iostream>
using namespace std;

Bouton::Bouton()
{
    texture = nullptr;

    survole = false;
    clique = false;

    scale = 1.0f;
    targetScale = 1.0f;

    rect = {0, 0, 0, 0};
}

Bouton::~Bouton()
{
    liberer();
}

bool Bouton::load(SDL_Renderer* renderer, const std::string& path, int x, int y, int w, int h)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cout << "Erreur IMG_Load: " << IMG_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rect = {x, y, w, h};

    return texture != nullptr;
}


void Bouton::setPosition(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Bouton::setSize(int w, int h)
{
    rect.w = w;
    rect.h = h;
}

bool Bouton::mouseSurBouton(int mx, int my)
{
    return (mx >= rect.x && mx <= rect.x + rect.w &&
            my >= rect.y && my <= rect.y + rect.h);
}

void Bouton::gestEvent(const SDL_Event e)
{
    if (e.type == SDL_MOUSEMOTION)
    {
        survole = mouseSurBouton(e.motion.x, e.motion.y);
        targetScale = survole ? 1.08f : 1.0f;
    }

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT && survole)
        {
            clique = true;
        }
    }
}

void Bouton::update()
{
    scale += (targetScale - scale) * 0.15f;
}

void Bouton::render(SDL_Renderer* renderer)
{
    if (!texture) return;

    SDL_Rect dst;

    dst.w = static_cast<int>(rect.w * scale);
    dst.h = static_cast<int>(rect.h * scale);

    dst.x = rect.x - (dst.w - rect.w) / 2;
    dst.y = rect.y - (dst.h - rect.h) / 2;

    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}



bool Bouton::consommerClic()
{
    if (clique)
    {
        clique = false;
        return true;
    }
    return false;
}

void Bouton::reset()
{
    clique = false;
}

bool Bouton::estClique() const
{
    return clique;
}

bool Bouton::estSurvole() const
{
    return survole;
}

void Bouton::liberer()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

SDL_Texture* Bouton::getTexture() const
{
    if (!texture)
    {
        cout << "Texture bouton non initialisée !" << std::endl;
    }
    return texture;
}

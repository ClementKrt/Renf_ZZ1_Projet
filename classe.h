#ifndef CLASEE_H
#define CLASSE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct animation{
    SDL_Texture * texture;
    int anim;
    int vitesse;
    int img_nb;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_bool cycle;
} anim_t;


#endif
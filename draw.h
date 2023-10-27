#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <string.h>
#include "classe.h"
#include "MatriceQ.h"

#define nbAnim (12+suite)

void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer);

void draw(SDL_Renderer * renderer, anim_t * animations, SDL_Rect tailleFenetre);

void drawAnim(SDL_Renderer * renderer, anim_t * anim, SDL_Rect tailleFenetre);

void initAnimations(SDL_Renderer *renderer, anim_t * animations, SDL_Rect tailleFenetre, int * Suite, 
                    SDL_Texture *tabTexture[]);

void event(SDL_Renderer *renderer, SDL_Rect tailleFenetre, anim_t *animations,
    int *Suite, float Q[][nbetat][nbetat][nbaction], float QSarsa[][nbetat][nbetat][nbaction], float Q1[][nbetat][nbetat][nbaction],
    SDL_Texture *tabTexture[], TTF_Font *font);

int croiseCopain(anim_t * animations);

void libereTexture(SDL_Texture *tabTexture[]);
#endif
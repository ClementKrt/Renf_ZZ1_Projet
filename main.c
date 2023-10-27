#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include"draw.h"

int main(int argc, char * argv[]){
    srand(time(NULL));
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect tailleFenetre = {0};
    SDL_Texture *tabTexture[10];
    TTF_Font* font = NULL;

    SDL_DisplayMode screen;
    int Suite[suite] = {0,0,0,0,4,4,4,4,2,2,2,2};
    int epsi = 100;

    float Q[nbetat][nbetat][nbetat][6];
    float QSarsa[nbetat][nbetat][nbetat][6];
    float Q1[nbetat][nbetat][nbetat][6];
    float Q2[nbetat][nbetat][nbetat][6];
    for(int i = 0 ; i < nbetat ; i++){
        for(int j = 0 ; j < nbetat ; j++){
            for(int a = 0 ; a < nbetat ; a++){
                for(int b = 0 ; b < nbaction ; b++){
                    Q[i][j][a][b] = 0;
                    QSarsa[i][j][a][b] = 0;
                    Q1[i][j][a][b] = 0;
                    Q2[i][j][a][b] = 0;
                    
                }
            }
        }
    }


    printf("Début de l'apprentissage\n");
    for(int test = 1 ; test < nbIte; test++)//apprentissage
    {
        Partie(Suite,test,&epsi,Q);
        PartieSarsa(Suite,&epsi,QSarsa);
        PartieDoubleQ(Suite,&epsi,Q1,Q2);
    }
    printf("\nFin de l'apprentissage\n");

    /*********************************************************************************************************************/  
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);
    if(TTF_Init()<0) end_sdl(0, "ERROR TTF", window, renderer);

    font = TTF_OpenFont("assets/arcade.ttf", 65);
    if(font == NULL) printf("BONJOUR\n");
    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("copain",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen.w * 0.8,
                                screen.h * 0.5,
                                SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /* Chargement des texture */

    anim_t * animations = malloc( nbAnim*sizeof(anim_t) );
    SDL_GetWindowSize(window, &tailleFenetre.w, &tailleFenetre.h);

    initAnimations(renderer, animations, tailleFenetre, Suite, tabTexture);

    for(int i = 0 ; i < nbetat ; i++){
        for(int j = 0 ; j < nbetat ; j++){
            for(int a = 0 ; a < nbetat ; a++){
                for(int b = 0 ; b < nbaction ; b++){
                    Q1[i][j][a][b] += Q2[i][j][a][b];
                }
            }
        }
    }
    event(renderer, tailleFenetre, animations, Suite, Q, QSarsa, Q1, tabTexture, font);


    libereTexture(tabTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}
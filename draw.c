#include "draw.h"

void end_sdl(char ok,                                               // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                                       // message à afficher
             SDL_Window* window,                                    // fenêtre à fermer
             SDL_Renderer* renderer) {                              // renderer à fermer
  char msg_formated[255];                                                         
  int l;                                                                          

  if (!ok) {                                                        // Affichage de ce qui ne va pas
    strncpy(msg_formated, msg, 250);                                              
    l = strlen(msg_formated);                                                     
    strcpy(msg_formated + l, " : %s\n");                                          

    SDL_Log(msg_formated, SDL_GetError());                                        
  }                                                                               

  if (renderer != NULL) {                                           // Destruction si nécessaire du renderer
    SDL_DestroyRenderer(renderer);                                  // Attention : on suppose que les NULL sont maintenus !!
    renderer = NULL;
  }
  if (window != NULL)   {                                           // Destruction si nécessaire de la fenêtre
    SDL_DestroyWindow(window);                                      // Attention : on suppose que les NULL sont maintenus !!
    window= NULL;
  }
  

  SDL_Quit();
  IMG_Quit();                                                                     

  if (!ok) {                                                        // On quitte si cela ne va pas                
    exit(EXIT_FAILURE);                                                           
  }                                                                               
}

void AccepteCopain(anim_t * animations, int nbCopain){
    int dino = -1;
    for (int i = 11; i < nbAnim-1; i++)
    {
        int distance = animations[nbAnim - 1].dest.x - animations[i].dest.x;
        if (distance >= 0 && distance < animations[i].vitesse)
        {
            dino = i;
        }
    }

    animations[dino].img_nb = 6;
    animations[dino].src.w = 24*6;
    animations[dino].src.x = 24*4;
    animations[dino].vitesse = 0;
    animations[dino].anim = 0;
    animations[dino].dest.x = animations[nbAnim - 1].dest.x - (animations[dino].dest.w/2) * (1 + nbCopain);

}


void drawAnim(SDL_Renderer * renderer, anim_t * anim, SDL_Rect tailleFenetre){
    SDL_Rect src = {0};
    if (anim->src.w != -1){
        src.w = anim->src.w /anim->img_nb;
        src.h = anim->src.h;
        src.x = anim->src.x + src.w * ((anim->anim)%(anim->img_nb));
        src.y = anim->src.y;
    

        SDL_RenderCopy(renderer, anim->texture, &src, &(anim->dest));
    }
    else SDL_RenderCopy(renderer, anim->texture, NULL, &(anim->dest));
    anim->dest.x -= anim->vitesse;
    anim->anim++;
    if (anim->cycle && anim->dest.x < -anim->dest.w){
        anim->dest.x += 2*tailleFenetre.w;
    }
}

void draw(SDL_Renderer * renderer, anim_t * animations, SDL_Rect tailleFenetre){
    for (int i = 0; i < nbAnim; i++)
    {
        drawAnim(renderer, &(animations[i]), tailleFenetre);
    }
    
}

void initAnimations(SDL_Renderer *renderer, anim_t * animations, SDL_Rect tailleFenetre, 
                    int * Suite, SDL_Texture *tabTexture[]){
    tabTexture[0] = IMG_LoadTexture(renderer, "assets/plx-5.png");
    tabTexture[1] = IMG_LoadTexture(renderer, "assets/plx-4.png");
    tabTexture[2] = IMG_LoadTexture(renderer, "assets/plx-3.png");
    tabTexture[3] = IMG_LoadTexture(renderer, "assets/plx-2.png");
    tabTexture[4] = IMG_LoadTexture(renderer, "assets/plx-1.png");
    tabTexture[5] = IMG_LoadTexture(renderer, "assets/ground.png");
    tabTexture[6] = IMG_LoadTexture(renderer, "assets/mort.png");
    tabTexture[7] = IMG_LoadTexture(renderer, "assets/doux.png");
    tabTexture[8] = IMG_LoadTexture(renderer, "assets/tard.png");
    tabTexture[9] = IMG_LoadTexture(renderer, "assets/run.png");

    for (int i = 0; i < nbAnim; i++)
    {
        animations[i].anim = 0;
    }
    
    for (int i = 0; i < 9; i++) //fonds parallax
    {
        animations[i].src.w = -1;
        animations[i].img_nb = 1;
        animations[i].cycle = SDL_TRUE;
        animations[i].dest.w = tailleFenetre.w;
        animations[i].dest.h = tailleFenetre.h;
        if(i<1){
            animations[i].vitesse = 0;
            animations[i].texture = tabTexture[4];
        }else if(i<3){
            animations[i].vitesse = 1;
            animations[i].texture = tabTexture[3];
        }else if(i<5){
            animations[i].vitesse = 2;
            animations[i].texture = tabTexture[2];
        }else if(i<7){
            animations[i].vitesse = 4;
            animations[i].texture = tabTexture[1];
        }else {
            animations[i].vitesse = 6;
            animations[i].texture = tabTexture[0];
        }
        if(i%2==0){
            animations[i].dest.x = 0;
            animations[i].dest.y = 0;
        }
        else{
            animations[i].dest.x = tailleFenetre.w;
            animations[i].dest.y = 0;
        }
    }
    for (int i = 9; i < 11; i++) //sol
    {
        animations[i].src.w = -1;
        animations[i].img_nb = 1;
        animations[i].cycle = SDL_TRUE;
        animations[i].dest.w = tailleFenetre.w;
        animations[i].dest.h = tailleFenetre.h/4;
        animations[i].dest.y = tailleFenetre.h - animations[i].dest.h;
        animations[i].texture = tabTexture[5];
        animations[i].vitesse = 8;
        if (i==9)
            animations[i].dest.x = 0;
        else
            animations[i].dest.x = tailleFenetre.w;
    }
    for (int i = 11; i < 11+suite; i++) //Dinos
    {
        animations[i].cycle=0;
        animations[i].img_nb=4;
        animations[i].src.x=0;
        animations[i].src.y=0;
        animations[i].src.w=24*4;
        animations[i].src.h=24;
        if (Suite[i-11]==0)
            animations[i].texture = tabTexture[6];
        else if (Suite[i-11]==2)
            animations[i].texture = tabTexture[8];
        else
            animations[i].texture = tabTexture[7];
        animations[i].vitesse = 8;
        animations[i].dest.h = 100;
        animations[i].dest.w = 100;
        animations[i].dest.y = animations[9].dest.y - animations[i].dest.h + 25;
        animations[i].dest.x = tailleFenetre.w + (i-11)*300;
    }
    animations[nbAnim - 1].cycle = 0;
    animations[nbAnim - 1].img_nb = 8;
    SDL_QueryTexture(tabTexture[9],NULL,NULL, &(animations[nbAnim - 1].src.w), &(animations[nbAnim - 1].src.h));
    animations[nbAnim - 1].src.x = 0;
    animations[nbAnim - 1].src.y = 0;
    animations[nbAnim - 1].dest.w = animations[nbAnim - 1].src.w/8*2;
    animations[nbAnim - 1].dest.h = animations[nbAnim - 1].src.h*2;
    animations[nbAnim - 1].dest.x = (tailleFenetre.w - animations[nbAnim - 1].src.w)/2;
    animations[nbAnim - 1].dest.y = (animations[9].dest.y - animations[nbAnim - 1].src.h)-25;
    animations[nbAnim - 1].vitesse = 0;
    animations[nbAnim - 1].texture = tabTexture[9];

}

int croiseCopain(anim_t * animations){
    int croise = 0;
    for (int i = 11; i < 11 + suite; i++)
    {
        int distance = animations[nbAnim - 1].dest.x - animations[i].dest.x;
        if (distance >= 0 && distance < animations[i].vitesse)
        {
            croise = 1;
        }
    }
    return croise;
}

/* -------- Ecrit un texte dans le renderer ---------*/
void ecriture(SDL_Renderer *renderer,SDL_Surface *text_surface, SDL_Rect pos){

  SDL_Texture* text_texture = NULL;                                    // la texture qui contient le texte
  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface); // transfert de la surface à la texture
    

  SDL_RenderCopy(renderer, text_texture, NULL, &pos);                  // Ecriture du texte dans le renderer
  SDL_DestroyTexture(text_texture);
}

void event(SDL_Renderer *renderer, SDL_Rect tailleFenetre, anim_t *animations,
            int *Suite, float Q[][nbetat][nbetat][nbaction], 
            float QSarsa[][nbetat][nbetat][nbaction], float Q1[][nbetat][nbetat][nbaction],
            SDL_Texture *tabTexture[], TTF_Font * font){
    SDL_bool program_on = SDL_TRUE;                          // Booléen pour dire que le programme doit continuer
    SDL_Event event;                                  // Evènement à traiter
    SDL_Surface* infoSurface = NULL;
    SDL_Rect posInfo = {0};
    SDL_Color colorInfo = {255, 255, 255, 255};

    posInfo.w = tailleFenetre.w * 0.3;
    posInfo.h = tailleFenetre.h * 0.1;
    posInfo.x = (tailleFenetre.w - posInfo.w)/2;
    posInfo.y = tailleFenetre.h - posInfo.h;



    int copains = 0;

    int Rouges = 0;
    int Bleus = 0;
    int Verts = 0;
    
    int ite = 0;

    Uint32 lastTick;
    Uint32 currentTick;
    int sleep;
    int compteurClique = 0;
    char infoMat[25] = "QLEARNING";

    /* Boucle principale */
    while (program_on) {                              // La boucle des évènements
    lastTick = SDL_GetTicks();
    while(SDL_PollEvent(&event)) {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                    // terminé le programme Défiler l'élément en tête de file dans 'event'
        switch (event.type) {                         // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_RETURN){
                    if(compteurClique < 2){
                        compteurClique++;
                        if(compteurClique == 1) strcpy(infoMat, "SARSA");
                        else if (compteurClique == 2) strcpy(infoMat, "DOUBLEQLEARNING");
                        printf("\n");
                        copains = 0;
                        ite = 0;
                        Rouges = 0;
                        Bleus = 0;
                        Verts = 0;
                        initAnimations(renderer, animations, tailleFenetre, Suite, tabTexture);
                    }
                }
            break;
            default:                                      // Les évènements qu'on n'a pas envisagé
                break;
        }
    }

    infoSurface = TTF_RenderText_Blended(font, infoMat, colorInfo);
    SDL_RenderClear(renderer);
    draw(renderer, animations, tailleFenetre); // On dessine
    ecriture(renderer,infoSurface, posInfo);


    if (croiseCopain(animations))
    {
        int action;
        if(compteurClique == 0) action = choixaction(Q,Rouges,Verts,Bleus,Suite[ite],0);
        else if (compteurClique == 1) action = choixaction(QSarsa,Rouges,Verts,Bleus,Suite[ite],0);
        else action = choixaction(Q1,Rouges,Verts,Bleus,Suite[ite],0);
        
        int accepte = effectue(&Rouges,&Verts,&Bleus,action); 
        if(accepte){
            copains++;
            AccepteCopain(animations, copains);
            printf("%d copains !\n",copains);
        }
        ite++;
    }
    
    SDL_RenderPresent(renderer);
    currentTick = SDL_GetTicks();
    sleep = 1000/20 - (currentTick - lastTick);
    if(sleep < 0) { sleep = 0; }
    SDL_Delay(sleep);                                  // Petite pause
    }
    SDL_FreeSurface(infoSurface);
    printf("\nQSimple :\n");
    afficherQ(Q);
    printf("\nSarsa :\n");
    afficherQ(QSarsa);
    printf("\nQDouble :\n");
    afficherQ(Q1);
}

void libereTexture(SDL_Texture *tabTexture[]){
    for(int i=0; i< 10; i++){
        SDL_DestroyTexture(tabTexture[i]);
        tabTexture[i] = NULL;
    }
}
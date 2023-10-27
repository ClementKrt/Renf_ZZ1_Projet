#include"MatriceQ.h"



void updateQ(float Q[][nbetat][nbetat][nbaction],cellule_t * tete){

    cellule_t * cour = tete;
    cellule_t * prec = NULL; //precedent dans la liste mais antecedent dans l'ordre des actions
   
    while(cour != NULL)
    {
            
        if(prec != NULL) //la tête est normalement toujours terminale mais condition dans le doute
        {
            float max = Q[prec->nbrouge][prec->nbvert][prec->nbbleu][prec->action];
            for(int i = 1 ; i < nbaction ; i++)
            {
                if(max < Q[prec->nbrouge][prec->nbvert][prec->nbbleu][prec->action])
                {
                    max = Q[prec->nbrouge][prec->nbvert][prec->nbbleu][prec->action];
                }
            }
            int rec = 0;
            if(prec->nbrouge + prec->nbbleu + prec->nbvert > 9){
                rec = prec->nbrouge + prec->nbbleu + prec->nbvert;
            }
            Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] =  
                Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] + alpha * (rec + (float)(gama * max) - Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
            
        }
        else 
        {
            if(cour->nbbleu + cour->nbrouge + cour->nbvert > 9)
            {
                int dernier = 0;
                if(cour->action%2){
                    dernier = 1;
                }
                Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] += alpha * ( dernier + cour->nbbleu + cour->nbrouge + cour->nbvert - Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
            }
        }

       
        prec = cour;
        cour = cour->suiv;
        
    }
    
}


void updateQSarsa(float Q[][nbetat][nbetat][nbaction],cellule_t * tete){

    cellule_t * cour = tete;
    cellule_t * prec = NULL; //precedent dans la liste mais antecedent dans l'ordre des actions
   
    while(cour != NULL)
    {
            
        if(prec != NULL) //la tête est normalement toujours terminale mais condition dans le doute
        {
            int rec = 0;
            if(prec->nbrouge + prec->nbbleu + prec->nbvert > 9){
                rec = prec->nbrouge + prec->nbbleu + prec->nbvert;
            }
            Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] =  
                Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] + alpha * (rec + (float)(gama * Q[prec->nbrouge][prec->nbvert][prec->nbbleu][prec->action]) - Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
            
        }
        else 
        {
            if(cour->nbbleu + cour->nbrouge + cour->nbvert > 9)
            {
                int dernier = 0;
                if(cour->action%2){
                    dernier = 1;
                }
                Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] += alpha * ( dernier + cour->nbbleu + cour->nbrouge + cour->nbvert - Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
            }
        }

       
        prec = cour;
        cour = cour->suiv;
        
    }
    
}


void updateQDoubleQlearningSarsa(float Q[][nbetat][nbetat][nbaction],float Q2[][nbetat][nbetat][nbaction],cellule_t * tete){

    cellule_t * cour = tete;
    cellule_t * prec = NULL; //precedent dans la liste mais antecedent dans l'ordre des actions
    if(rand()%100< 50)
    { 
        while(cour != NULL)
        {
           
            if(prec != NULL) //la tête est normalement toujours terminale mais condition dans le doute
            {
                int rec = 0;
                if(prec->nbrouge + prec->nbbleu + prec->nbvert > 9){
                    rec = prec->nbrouge + prec->nbbleu + prec->nbvert;
                }
                Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] =  
                    Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] + alpha * (rec + (float)(gama * Q2[prec->nbrouge][prec->nbvert][prec->nbbleu][prec->action]) - Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
            
            }
            else 
            {
                if(cour->nbbleu + cour->nbrouge + cour->nbvert > 9)
                {
                    int dernier = 0;
                    if(cour->action%2){
                        dernier = 1;
                    }
                    Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] += alpha * ( dernier + cour->nbbleu + cour->nbrouge + cour->nbvert - Q[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
                }
            }

       
            prec = cour;
            cour = cour->suiv;
        
        }
    }
    else{
        while(cour != NULL)
        {
           
            if(prec != NULL) //la tête est normalement toujours terminale mais condition dans le doute
            {
                int rec = 0;
                if(prec->nbrouge + prec->nbbleu + prec->nbvert > 9){
                    rec = prec->nbrouge + prec->nbbleu + prec->nbvert;
                }
                Q2[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] =  
                    Q2[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] + alpha * (rec + (float)(gama * Q[prec->nbrouge][prec->nbvert][prec->nbbleu][prec->action]) - Q2[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
            
            }
            else 
            {
                if(cour->nbbleu + cour->nbrouge + cour->nbvert > 9)
                {
                    int dernier = 0;
                    if(cour->action%2){
                        dernier = 1;
                    }
                    Q2[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action] += alpha * ( dernier + cour->nbbleu + cour->nbrouge + cour->nbvert - Q2[cour->nbrouge][cour->nbvert][cour->nbbleu][cour->action]);
                }
            }
            prec = cour;
            cour = cour->suiv;
        }
    }
    
}


void afficherQ(float Q[][nbetat][nbetat][nbaction]){
    for(int i = 0 ; i < nbetat ; i++){
        for(int j = 0 ; j < nbetat ; j++){
            for(int a = 0 ; a < nbetat ; a++){
                printf("%d %d %d : ",i,j,a);
                for(int b = 0 ; b < nbaction ; b++){
                    printf("%f ",Q[i][j][a][b]);
                }
                printf("\n");
            }
        }
    }   
}

void InsertionListe(cellule_t ** tete, int action , int rouge,int vert,int bleu){
    cellule_t * nouv = malloc(sizeof(cellule_t));
    nouv->nbvert = vert;
    nouv->nbbleu = bleu;
    nouv->nbrouge = rouge;
    nouv->action = action;
    if(*tete != NULL)
    {
        nouv->suiv= *tete;
    }
    else
    {
        nouv->suiv = NULL;
    }
    *tete = nouv;
}

int choixaction(float Q[][nbetat][nbetat][nbaction],int Rouge,int Vert,int Bleu,int coulsuiv,int epsi){
    int action = 0;
    if(rand()%100 < epsi)
    {
        if(rand() < RAND_MAX/2){
            action = coulsuiv;
        }else{
            action = coulsuiv + 1;
        }  
    }
    else{
        action = coulsuiv;
        if(Q[Rouge][Vert][Bleu][action] < Q[Rouge][Vert][Bleu][action + 1]){
            action += 1;
        }
    }
    switch(action){
        case 1:
        if(Rouge + Bleu + Vert > 4 || Rouge == 5){
            action = 0;
        }
        break;
        case 3:
        if(Vert >= Rouge || Vert == 5){
            action = 2;
        }
        break;
        case 5:
        if(Bleu == 5){
            action = 4;
        }
        break;
        default:
        break;
    }
    return action;
}

int choixactionDoubleQ(float Q[][nbetat][nbetat][nbaction],float Q2[][nbetat][nbetat][nbaction],int Rouge,int Vert,int Bleu,int coulsuiv,int epsi){
    int action = 0;
    if(rand()%100 < epsi)
    {
        if(rand() < RAND_MAX/2){
            action = coulsuiv;
        }else{
            action = coulsuiv + 1;
        }  
    }
    else{
        action = coulsuiv;
        if(Q[Rouge][Vert][Bleu][action] + Q2[Rouge][Vert][Bleu][action] < Q[Rouge][Vert][Bleu][action + 1] + Q2[Rouge][Vert][Bleu][action + 1]){
            action += 1;
        }
    }
    switch(action){
        case 1:
        if(Rouge + Bleu + Vert > 4 || Rouge == 5){
            action = 0;
        }
        break;
        case 3:
        if(Vert >= Rouge || Vert == 5){
            action = 2;
        }
        break;
        case 5:
        if(Bleu == 5){
            action = 4;
        }
        break;
        default:
        break;
    }
    return action;
}



int effectue(int * rouge,int * vert,int * bleu,int action){
    int tmp = *rouge + * bleu + * vert;
    switch(action){
        case 1:
        (*rouge) ++;
        break;
        case 3:
        (*vert)++;
        break;
        case 5:
        (*bleu)++;
        break;
        default:
        break;
    }
    return (tmp != (*bleu + *rouge + *vert));
}


void liberationListe(cellule_t ** tete){
    cellule_t * cour = *tete;
    cellule_t * prec = NULL;
    while(cour != NULL){
        prec = cour;
        cour = cour->suiv;
        free(prec);
    }
}

void Partie(int Suite[suite],int test,int * epsi,float Q[][nbetat][nbetat][6]){
    cellule_t * tete = NULL;
    int Rouges = 0;
    int Bleus = 0;
    int Verts = 0;

    int ite = 0;
    while(ite < suite){
        int action = choixaction(Q,Rouges,Verts,Bleus,Suite[ite],*epsi);
       
        InsertionListe(&tete,action,Rouges,Verts,Bleus);
        effectue(&Rouges,&Verts,&Bleus,action); 
        ite++;
        }
    if(test%(nbIte/100) == 0){
        *epsi -= 1;
        printf("%d\n",*epsi);
    }
    if(tete->nbrouge + tete->nbvert + tete-> nbbleu > 9){ //Update si victoire
        updateQ(Q,tete);
    }
    liberationListe(&tete);
    tete = NULL;
}

void PartieSarsa(int Suite[suite],int * epsi,float Q[][nbetat][nbetat][6]){
    cellule_t * tete = NULL;
    int Rouges = 0;
    int Bleus = 0;
    int Verts = 0;

    int ite = 0;
    while(ite < suite){
        int action = choixaction(Q,Rouges,Verts,Bleus,Suite[ite],*epsi);
       
        InsertionListe(&tete,action,Rouges,Verts,Bleus);
        effectue(&Rouges,&Verts,&Bleus,action); 
        ite++;
        }
   /* if(test%(nbIte/100) == 0){
        *epsi -= 1;
        printf("%d\n",*epsi);
    }*/
    if(tete->nbrouge + tete->nbvert + tete-> nbbleu > 9){ //Update si victoire
        updateQSarsa(Q,tete);
    }
    liberationListe(&tete);
    tete = NULL;
}


void PartieDoubleQ(int Suite[suite],int * epsi,float Q1[][nbetat][nbetat][6],float Q2[][nbetat][nbetat][6]){
    cellule_t * tete = NULL;
    int Rouges = 0;
    int Bleus = 0;
    int Verts = 0;

    int ite = 0;
    while(ite < suite){
        int action = choixactionDoubleQ(Q1,Q2,Rouges,Verts,Bleus,Suite[ite],*epsi);
       
        InsertionListe(&tete,action,Rouges,Verts,Bleus);
        effectue(&Rouges,&Verts,&Bleus,action); 
        ite++;
        }
   /* if(test%(nbIte/100) == 0){
        *epsi -= 1;
        printf("%d\n",*epsi);
    }*/
    if(tete->nbrouge + tete->nbvert + tete-> nbbleu > 9){ //Update si victoire
        updateQDoubleQlearningSarsa(Q1,Q2,tete);
    }
    liberationListe(&tete);
    tete = NULL;
}




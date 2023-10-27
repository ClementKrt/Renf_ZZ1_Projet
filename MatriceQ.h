#ifndef MAT_H
#define MAT_H

#include <stdio.h>
#include "ListeChainee.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define nbaction 6
#define nbetat 6
#define alpha 0.6
#define gama 0.4
#define suite 15
#define nbIte 1000000

void Partie(int Suite[suite],int test,int * epsi,float Q[][nbetat][nbetat][6]);
void PartieSarsa(int Suite[suite],int * epsi,float Q[][nbetat][nbetat][6]);
void PartieDoubleQ(int Suite[suite],int * epsi,float Q1[][nbetat][nbetat][6],float Q2[][nbetat][nbetat][6]);
int choixaction(float Q[][nbetat][nbetat][nbaction],int Rouge,int Vert,int Bleu,int coulsuiv,int epsi);
int effectue(int * rouge,int * vert,int * bleu,int action);
void afficherQ(float Q[][nbetat][nbetat][nbaction]);
#endif
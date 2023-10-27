#ifndef LC_H
#define LC_H 

typedef struct cellule{
    int nbvert;
    int nbrouge;
    int nbbleu;
    int action;
    struct cellule * suiv;

}cellule_t;

#endif 
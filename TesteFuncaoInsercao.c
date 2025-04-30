#include "ArvoreRn.h"

void RR(NoRn *no)
{
    NoRn *aux;
    no->esq = aux;
    aux->dir->pai = no;
    no->esq = aux->dir;
    aux->dir = no;
    aux->pai = no->pai;
    no->pai = aux;
    no = aux; //para continuar subindo em uma recursão
}

void LL(NoRn *no)
{
    NoRn *aux;
    no->dir = aux;
    aux->esq->pai = no;
    no->dir = aux->esq;
    aux->esq = no;
    aux->pai = no->pai;
    no->pai = aux;
    no = aux;
}

void RL(NoRn *no){
    RR(no->dir);
    LL(no);
}

void LR(NoRn *no){
    LL(no->esq);
    RR(no);
}





//anisio



int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

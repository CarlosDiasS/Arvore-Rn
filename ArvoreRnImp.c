#include "ArvoreRn.h"

NoRn *criaNoRn(int idCliente)
{
    NoRn *aux = malloc(sizeof(NoRn));
    aux->esq = NULL;
    aux->dir = NULL;
    aux->pai = NULL;
    aux->idCliente = idCliente;
    //talvez uma condicional para a raiz
    aux->cor = RED;
    return aux;
}

ArvoreRn *criaArvore(){
    ArvoreRn *aux = malloc(sizeof(ArvoreRn));
    aux->raiz = NULL;
    return aux;
}

NoRn *buscaNo(int idCliente, NoRn *raiz)
{
    if (raiz != NULL)
    {
        NoRn *atual = raiz;

        while (atual != NULL && idCliente != atual->idCliente)
        {
            if (idCliente < atual->idCliente)
            {
                atual = atual->esq;
            }
            else
            {
                atual = atual->dir;
            }
        }
        if(atual !=NULL){
           return atual; 
        }
        printf("Nó não encontrado.\n");
        exit(1);
    }
    printf("arvore vazia.\n");
    exit(1);
}

// FUNÇAÕ INSERÇÃO
// FUNÇÃO REMOÇAO
// FUNCAO PRINT (ALTERAR COR DE EXIBICAO: R/N)
//grafico em log N (relatorio)

int main()
{
    //teste
    ArvoreRn *arvoreRn = criaArvore();
    arvoreRn->raiz = criaNoRn(12);
    arvoreRn->raiz->esq = criaNoRn(6);
    arvoreRn->raiz->dir = criaNoRn(18);
    arvoreRn->raiz->esq->esq = criaNoRn(3);
    arvoreRn->raiz->esq->dir= criaNoRn(8);
    arvoreRn->raiz->dir->esq = criaNoRn(15);
    arvoreRn->raiz->dir->dir= criaNoRn(20);

    NoRn *buscado = buscaNo(0,arvoreRn->raiz);
    printf("idCliente %d achado.\n", buscado->idCliente);


    return 0;
}
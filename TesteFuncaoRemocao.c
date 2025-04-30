#include <stdlib.h>
#include <stdbool.h>

typedef enum Cor{
    BLACK,
    RED
}Cor;

typedef struct NoRn{
    int idCliente;
    Cor cor;
    struct NoRn *esq;
    struct NoRn *dir;
    struct NoRn *pai;
}NoRn;

typedef struct ArvoreRn{
    NoRn *raiz;
}ArvoreRn;

bool isBalanceado(ArvoreRn *grafo);

void balancearRn(ArvoreRn *grafo);

NoRn *menorNo(ArvoreRn *grafo){

    NoRn *aux = grafo->raiz;
    if(aux !=NULL){
        while(aux->esq != NULL){
            aux = aux->esq;
        }
        return aux;
    }
}

NoRn *sucessor(ArvoreRn *grafo, NoRn *No){

    NoRn *aux = grafo->raiz;
    aux = aux->dir;
    while(aux->esq != NULL){
        aux = aux->esq;
    }
    return aux;
}

NoRn *antecessor(ArvoreRn *grafo, NoRn *No){

    NoRn *aux = grafo->raiz;
    aux = aux->esq;
    while(aux->dir != NULL){
        aux = aux->dir;
    }
    return aux;
}

//Rotacoes ja implementadas

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


void TransplanteRn(ArvoreRn *grafo, NoRn *u, NoRn *z){
    if(u->pai == NULL){
        grafo->raiz = z;
    }
    else if(u == u->pai->esq){
        u->pai->esq = z;
    }
    else{
        u->pai->dir = z;
    }
    z->pai = u->pai;
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

bool RemoverNoRn(ArvoreRn *grafo,int idCliente){

    NoRn *aux = buscaNo(idCliente, grafo->raiz);
    //tratamento de erro na funcao buscaNo( caso nao encontrado)

    //Caso 1, ambos os filhos nulos

    if(!aux->esq && !aux->dir){

        if(aux->idCliente>aux->pai->idCliente){
            aux->pai->dir = NULL;
            if(!isBalanceado(grafo)){
                balancearRn(grafo);
                printf("No %d removido.\n",idCliente);
                return true;
            }
            
        }
        //a esquerda, sendo menor ou igual
        else{
            aux->pai->esq = NULL;
            if(!isBalanceado(grafo)){
                balancearRn(grafo);
                printf("No %d removido.\n",idCliente);
                return true;
            }
        }
    }

    //Caso 2.1, sem filhos a esquerda 

    if(aux->esq == NULL && aux->dir !=NULL){

        aux = aux->dir;
        aux->dir = NULL;
        if(!isBalanceado(grafo)){
                balancearRn(grafo);
                printf("No %d removido.\n",idCliente);
                return true;
            }
    }

    //Caso 2.2, sem filhos a direita 

    if(aux->dir == NULL && aux->esq !=NULL){

        aux = aux->esq;
        aux->esq = NULL;
        if(!isBalanceado(grafo)){
                balancearRn(grafo);
                printf("No %d removido.\n",idCliente);
                return true;
            }
    }

    //Casos 3.1,3.2,3.3,3.2,3.4

    //Caso 3.1, slide 16-20





}


int main()
{
    // teste arvore mock
    ArvoreRn *arvoreRn = criaArvore();
    arvoreRn->raiz = criaNoRn(12);
    arvoreRn->raiz->esq = criaNoRn(6);
    arvoreRn->raiz->dir = criaNoRn(18);
    arvoreRn->raiz->esq->esq = criaNoRn(3);
    arvoreRn->raiz->esq->dir = criaNoRn(8);
    arvoreRn->raiz->dir->esq = criaNoRn(15);
    arvoreRn->raiz->dir->dir = criaNoRn(20);






    return 0;
}

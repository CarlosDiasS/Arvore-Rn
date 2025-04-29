#include "ArvoreRn.h"

//nó sentinela global (nil, vou abreviar muito grande o nome) (acho que pode funcionar melhor do que botar um nó para cada arvóre)
NoRn *NIL = NULL;

//inicializa o nil
void inicializarNil() {
    if (NIL == NULL) {
        NIL = (NoRn*)malloc(sizeof(NoRn));
        NIL->cor = BLACK;
        NIL->esq = NIL->dir = NIL->pai = NIL;
        
    }
    return NIL;
    //funcao ja existe na principal
}

//função que busca um nó na ARN (se Deus quiser tá certo)

//verificar busca feita em lab(aeds2)

NoRn *buscaNo(int idCliente, NoRn *raiz) {
    NoRn *atual = raiz;
    
    while (atual != NIL && idCliente != atual->idCliente) {
        if (idCliente < atual->idCliente) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    
    return atual; //retorna o nó encontrado ou NIL se não encontrado (vulgo se deu merda)
}

//função que verifica se um cliente está na fila
bool clienteNaFila(int idCliente, NoRn *raiz) {
    NoRn *resultado = buscaNo(idCliente, raiz);
    return (resultado != NIL);
    //ternario
    
}

//função auxiliar para testar se a busca deu certo
void testarBusca(int idCliente, NoRn *raiz) {
    if (clienteNaFila(idCliente, raiz)) {
        printf("Cliente com ID %d esta na fila de atendimento.\n", idCliente);
    } else {
        printf("Cliente com ID %d NAO esta na fila de atendimento.\n", idCliente);
    }
}// agora a gente reza pra nao ter dado algum erro
//a partir daqui é sucessofefe
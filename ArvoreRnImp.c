#include "ArvoreRn.h"

NoRn *criaNoRn(int idCliente)
{
    NoRn *aux = malloc(sizeof(NoRn));
    aux->esq = NULL;
    aux->dir = NULL;
    aux->pai = NULL;
    aux->idCliente = idCliente;
    aux->cor = RED;
    return aux;
}

NoRn *buscaNo(int idCliente, NoRn *raiz)
{

}

// FUNÇAÕ INSERÇÃO
// FUNÇÃO REMOÇAO
// FUNCAO PRINT (ALTERAR COR DE EXIBICAO: R/N)
//grafico em log N (relatorio)

int main()
{
    /* code */ 
    return 0;
}
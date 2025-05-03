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

FilaAtendimento *criaFila(){
    FilaAtendimento *aux = malloc(sizeof(FilaAtendimento));
    aux->totalAtendimentos = 0;
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


// FUNÇAÕ INSERÇÃO
// FUNÇÃO REMOÇAO
// FUNCAO PRINT (ALTERAR COR DE EXIBICAO: R/N)
//grafico em log N (relatorio)


/*
    a fila de atendimento ira armazenar os inputs
    caso seja -1, chamar a remocao(que ira remover o idCliente de menor valor)
    demais valores serao adicionado a arvore
    ao final, a funcao impressao ira imprimir a arvore resultante(que contem os clientes que ainda nao foram atendidos)

    -> uma funcao handleInput da vida, que ira analisar as entradas(x1,x2,x3...): 

    while fim dos inputs

    x = -1: remover no com menor idCliente(naturalmente, no na extrema esquerda da arvore)
    x >= 0: adicionar a arvore Rn

    -> imprimir arvore resultante no formato: 

    41 BLACK
    34 RED
    25 BLACK
    32 RED
    36 BLACK
    43 BLACK
    49 RED

    -> funcao para limpar todas as alocações de memoria

*/

void imprimirGrafo(ArvoreRn *grafo);

bool inserirNoRn( int idCliente,ArvoreRn *grafo);

ArvoreRn *tratarInputDados(FilaAtendimento *fila){

    int totalEntradas = sizeof(fila->vetor)/sizeof(int); // ou entao receber por parametro
    fila->totalAtendimentos = totalEntradas;
    ArvoreRn *grafo = criaArvore();

    for(int i=0;i<totalEntradas;i++){

        if(fila->vetor[i] != -1){
            inserirNoRn(fila->vetor[i],grafo);
            //testar com printf aqui
        }
        else{
            removerNoRn(fila->vetor[i],grafo);
             //testar com printf aqui
        }
    }
    return grafo;
}



int main()
{
    //main ofc:

    //input e tratamento de dados
    FilaAtendimento *fila = criaFila();

    //um for para popular a fila(scanf)

    ArvoreRn *grafo = tratarInputDados(fila);
    imprimirGrafo(grafo);


    return 0;
}
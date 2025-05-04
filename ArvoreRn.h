#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// java na veia
typedef enum
{
    BLACK,
    RED,
} Cor;

typedef struct NoRn
{
    int idCliente;
    Cor cor;
    struct NoRn *esq;
    struct NoRn *dir;
    struct NoRn *pai;
} NoRn;

typedef struct ArvoreRn
{
    NoRn *raiz;
} ArvoreRn;

typedef struct FilaAtendimento
{
    int *vetor;
    int totalAtendimentos;
} FilaAtendimento;

// cabeçalhos das funcoes e comentarios

NoRn *criaNoRn(int idCliente);

ArvoreRn *criaArvore();

FilaAtendimento *criaFila();

NoRn *menorNo(NoRn *no);

NoRn *antecessor(ArvoreRn *grafo, NoRn *No);

NoRn *buscaNo(int idCliente, NoRn *raiz);

bool RR(ArvoreRn *grafo, NoRn *no);

bool LL(ArvoreRn *grafo, NoRn *no);

void RL(ArvoreRn *grafo, NoRn *no);

void LR(ArvoreRn *grafo, NoRn *no);

void TransplanteRn(ArvoreRn *grafo, NoRn *u, NoRn *z);

/*
@brief aplica os 4 casos e seus respectivos subcasos
@param arvore: arvore rubro negra
@param x: no usado na remocao

*/
void CorrigirRemocaoRn(ArvoreRn *arvore, NoRn *x);
/*
@brief realiza a remocao de um no e uma arvore nao nula
@param grafo: arvore rubro negra
@param idCliente: numero de registro do cliente

*/
bool RemoverNoRn(ArvoreRn *grafo, int idCliente);

/*
@brief aplica os 3 casos de balanceamento
@param novoNo: no usado na insercao
@param arvore: arvore rubro negra

*/
void ajustarInsercao(ArvoreRn *arvore, NoRn *novoNo);

/*
@brief insere um novo NoRn na arvore
@param idCLiente: numero de registro do cliente
@param arvore: arvore rubro negra

*/
void inserirNo(int idCliente, ArvoreRn *arvore);
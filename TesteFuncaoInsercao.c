#include "ArvoreRn.h"

NoRn *criaNoRn(int idCliente)
{
    NoRn *aux = malloc(sizeof(NoRn));
    aux->esq = NULL;
    aux->dir = NULL;
    aux->pai = NULL;
    aux->idCliente = idCliente;
    // talvez uma condicional para a raiz
    aux->cor = RED;
    return aux;
}

bool RR(ArvoreRn *grafo, NoRn *no)
{
    if (no == NULL || no->esq == NULL || grafo->raiz == NULL)
        return false;

    NoRn *aux = no->esq;
    no->esq = aux->dir;

    if (aux->dir != NULL)
    {
        aux->dir->pai = no;
    }

    aux->pai = no->pai;

    if (no->pai == NULL)
    {
        grafo->raiz = aux;
    }
    else if (no == no->pai->dir)
    {
        no->pai->dir = aux;
    }
    else
    {
        no->pai->esq = aux;
    }
    aux->dir = no;
    no->pai = aux;
}

bool LL(ArvoreRn *grafo, NoRn *no)
{

    if (no == NULL || no->esq == NULL || grafo->raiz == NULL)
        return false;

    NoRn *aux = no->dir;
    no->dir = aux->esq;

    if (aux->esq != NULL)
    {
        aux->esq->pai = no;
    }

    aux->pai = no->pai;

    if (no->pai == NULL)
    {
        grafo->raiz = aux;
    }
    else if (no == no->pai->esq)
    {
        no->pai->esq = aux;
    }
    else
    {
        no->pai->dir = aux;
    }
    aux->esq = no;
    no->pai = aux;
}

void RL(ArvoreRn *grafo, NoRn *no)
{
    RR(grafo, no->dir);
    LL(grafo, no);
}

void LR(ArvoreRn *grafo, NoRn *no)
{
    LL(grafo, no->esq);
    RR(grafo, no);
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
        return (atual);
    }

    // retorna o nó encontrado ou NULL se não encontrado (vulgo se deu merda)
}

bool clienteNaFila(int idCliente, NoRn *raiz)
{
    NoRn *resultado = buscaNo(idCliente, raiz);
    return (resultado != NULL) ? true : false;
    // ternario
}

// anisio
bool ajustarInsercao(NoRn *novoNo, ArvoreRn *arvore)
{
    if (arvore->raiz == NULL)
    {
        return false;
    }

    if (novoNo->idCliente == arvore->raiz->idCliente)
    {
        arvore->raiz->cor = BLACK;
        return true;
    }

    NoRn *tio = NULL;
    while (novoNo->pai != NULL && novoNo->pai->cor == RED && novoNo != arvore->raiz)
    {
        if (novoNo->pai->pai == NULL)
        {
            break; // Avô não existe, não podemos continuar
        }
        if (novoNo->pai == novoNo->pai->pai->esq)
        {
            tio = novoNo->pai->pai->dir;

            if (tio != NULL && tio->cor == RED)
            {
                // caso 1:tio vermelho Ok
                novoNo->pai->cor = BLACK;
                tio->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                novoNo = novoNo->pai->pai;
            }
            else
            {
                // caso 2:tio preto
                if (novoNo == novoNo->pai->dir)
                {
                    novoNo = novoNo->pai;
                    LL(arvore, novoNo);
                }
                // caso 3 OK
                novoNo->pai->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                RR(arvore, novoNo->pai->pai);
            }
        }
        else
        {
            // espelho dos casos anteriores
            tio = novoNo->pai->pai->esq;

            if (tio != NULL && tio->cor == RED)
            {
                novoNo->pai->cor = BLACK;
                tio->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                novoNo = novoNo->pai->pai;
            }
            else
            {
                if (novoNo == novoNo->pai->esq)
                {
                    novoNo = novoNo->pai;
                    RR(arvore, novoNo);
                }
                novoNo->pai->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                LL(arvore, novoNo->pai->pai);
            }
        }
    }
    // a raiz é sempre preta (se por acaso ela ficar vermelha é pra mudar a cor dos filhos)
    arvore->raiz->cor = BLACK;
    return true;
}

// função de inserção
bool inserirNo(int idCliente, ArvoreRn *arvore)
{
    NoRn *novoNo = criaNoRn(idCliente);
    if (novoNo == NULL)
        return false;
    NoRn *y = NULL;
    NoRn *x = arvore->raiz;
    // encontra a posição de inserção
    while (x != NULL)
    {
        y = x;
        if (novoNo->idCliente < x->idCliente)
        {
            x = x->esq;
        }
        else
        {
            x = x->dir;
        }
    }
    novoNo->pai = y;
    if (y == NULL)
    {
        arvore->raiz = novoNo; // árvore vazia
    }
    else if (novoNo->idCliente < y->idCliente)
    {
        y->esq = novoNo;
    }
    else
    {
        y->dir = novoNo;
    }
    // ajusta as propriedades da ARN
    ajustarInsercao(novoNo, arvore);
    // encontra a nova raiz
    while (arvore->raiz->pai != NULL)
    {
        arvore->raiz = arvore->raiz->pai;
    }

    return true;
}

// função para imprimir em pré-ordem (como ela pediu no trabalho)
void imprimirPreOrdem(NoRn *no) // funcao errada
{
    if (no != NULL)
    {
        printf("%d %s\n", no->idCliente, no->cor == RED ? "RED" : "BLACK");
        imprimirPreOrdem(no->esq);
        imprimirPreOrdem(no->dir);
    }
}

ArvoreRn *criaArvore()
{
    ArvoreRn *aux = malloc(sizeof(ArvoreRn));
    aux->raiz = NULL;
    return aux;
}

int main()
{
    ArvoreRn *arvoreRn = criaArvore();
    inserirNo(12, arvoreRn);

    inserirNo(5, arvoreRn);
    inserirNo(56, arvoreRn);
    inserirNo(20, arvoreRn);
    inserirNo(1, arvoreRn);
    inserirNo(57, arvoreRn);
    inserirNo(2, arvoreRn);

    printf("cor: %d\n", arvoreRn->raiz->cor);

    imprimirPreOrdem(arvoreRn->raiz);

    return 0;
}
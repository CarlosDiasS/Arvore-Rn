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

ArvoreRn *criaArvore()
{
    ArvoreRn *aux = malloc(sizeof(ArvoreRn));
    aux->raiz = NULL;
    return aux;
}

FilaAtendimento *criaFila()
{
    FilaAtendimento *aux = malloc(sizeof(FilaAtendimento));
    aux->totalAtendimentos = 0;
    return aux;
}

NoRn *menorNo(ArvoreRn *grafo)
{

    NoRn *aux = grafo->raiz;
    if (aux != NULL)
    {
        while (aux->esq != NULL)
        {
            aux = aux->esq;
        }
        return aux;
    }
}

NoRn *antecessor(ArvoreRn *grafo, NoRn *No)
{
    if (No == NULL)
    {
        return NULL;
    }

    if (No->esq != NULL)
    {
        NoRn *aux = No->esq;

        while (aux->dir != NULL)
        {
            aux = aux->dir;
        }
        return aux;
    }
    return No;
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
    no = aux; // para continuar subindo em uma recursão
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

void RL(NoRn *no)
{
    RR(no->dir);
    LL(no);
}

void LR(NoRn *no)
{
    LL(no->esq);
    RR(no);
}

void TransplanteRn(ArvoreRn *grafo, NoRn *u, NoRn *z)
{
    printf("transplante\n");
    if (u->pai == NULL)
    {
        grafo->raiz = z;
    }
    else if (u == u->pai->esq)
    {
        u->pai->esq = z;
    }
    else
    {
        u->pai->dir = z;
    }
    z->pai = u->pai;
}

NoRn *buscaNo(int idCliente, NoRn *raiz)
{
    NoRn *atual = raiz;

    while (atual != NULL)
    {
        if (idCliente == atual->idCliente)
        {
            return atual;
        }
        else if (idCliente < atual->idCliente)
        {
            atual = atual->esq;
        }
        else
        {
            atual = atual->dir;
        }
    }
    // Não encontrado
    return NULL;
}

bool RemoverNoRn(ArvoreRn *grafo, int idCliente)
{

    NoRn *aux = buscaNo(idCliente, grafo->raiz);
    printf("ok\n");
    if (aux == NULL || grafo == NULL || grafo->raiz == NULL)
    {
        return false;
    }
    printf("no : %d\n", aux->idCliente);

    NoRn *noAntecessor = antecessor(grafo, aux);

    // caso 0 raiz
    if (aux->pai == NULL)
    {
        grafo->raiz = NULL;
        printf("Arvore esvaziada.\n");
        return true;
    }

    // Caso 1, ambos os filhos nulos OK
    if (!aux->esq && !aux->dir)
    {

        if (aux->idCliente > aux->pai->idCliente)
        {
            aux->pai->dir = NULL;
            // TESTE
            printf("caso 1: \n");
            printf("No %d removido.\n", idCliente);
            return true;
        }
        // a esquerda, sendo menor ou igual
        else
        {
            aux->pai->esq = NULL;
            // TESTE
            printf("caso 1: \n");
            printf("No %d removido.\n", idCliente);
            return true;
        }
    }

    // Caso 2.1, sem filhos a esquerda OK

    if (aux->esq == NULL && aux->dir != NULL)
    {
        NoRn *temp = aux->dir;
        aux = aux->dir;
        aux->cor = temp->cor;
        aux->dir = NULL;
        printf("caso 2.1: \n");
        printf("No %d removido.\n", idCliente);
        return true;
    }

    // Caso 2.2, sem filhos a direita OK

    if (aux->dir == NULL && aux->esq != NULL)
    {
        NoRn *temp = aux->esq;
        aux = aux->esq;
        aux->cor = temp->cor;
        aux->esq = NULL;
        // TESTE
        printf("caso 2.2: \n");
        printf("No %d removido.\n", idCliente);
        return true;
    }

    // Caso 3, utilizando o no antecessor

    if (aux->esq != NULL && aux->dir != NULL)
    {
        printf("caso 3: \n");

        printf("ok1\n");

        // filho a esq do antecessor
        NoRn *x = noAntecessor->esq;
        printf("ok2\n");

        // tio de x(irmao do antecessor)
        NoRn *w = NULL;
        if (x != NULL)
        {
            w = x->pai->pai->esq;
        };
        printf("ok3\n");
        // recortar o antecessor e substituir aux pelo antecessor

        TransplanteRn(grafo, aux, noAntecessor);
        printf("ok4\n");
        // Caso 3.1
        if (w != NULL && w->cor == RED)
        {
            printf("caso 3.1: \n");
            printf("No %d removido.\n", idCliente);
            w->cor = BLACK;
            if (x->pai->cor == BLACK)
            {
                x->pai->cor = RED;
            }
            else
                x->pai->cor = BLACK;
            LL(x->pai);
        }

        // Caso 3.2
        if (w->cor == BLACK && w->esq->cor == BLACK && w->dir->cor == BLACK)
        {
            // retirar um preto de x e de w
            printf("terminar");

            // maldito duplo preto
        }

        // Caso 3.3
        if (w->cor == BLACK && w->esq->cor == RED && w->dir->cor == BLACK)
        {
            if (w->cor == BLACK)
            {
                w->cor = RED;
            }
            else
            {
                w->cor = BLACK;
            }

            if (w->esq->cor == BLACK)
            {
                w->esq->cor = RED;
            }
            else
            {
                w->esq->cor = BLACK;
            }
            RR(w);
            // w e preto, w->dir->cor == RED : Caso 3.4
        }

        // Caso 3.4
        if (w->cor == BLACK && w->esq->cor == BLACK && w->dir->cor == RED)
        {
            NoRn *auxAnterior = noAntecessor;
            LL(x->pai);
            x->pai->cor = BLACK;
            w->cor = auxAnterior->cor;
            w->dir = BLACK;
        }
    }

    // Caso 4
    if (aux->cor == RED && noAntecessor->cor == BLACK)
    {

        // filho a esq do antecessor
        NoRn *x = noAntecessor->esq;
        x->cor = RED;
        RemoverNoRn(grafo, idCliente);
    }
}

int main()
{
    // teste arvore mock
    ArvoreRn *arvoreRn = criaArvore();
    arvoreRn->raiz = criaNoRn(12);
    arvoreRn->raiz->cor = BLACK;
    arvoreRn->raiz->esq = criaNoRn(6);
    arvoreRn->raiz->esq->cor = BLACK;
    arvoreRn->raiz->esq->pai = arvoreRn->raiz;
    arvoreRn->raiz->dir = criaNoRn(18);
    arvoreRn->raiz->dir->cor = BLACK;
    arvoreRn->raiz->dir->pai = arvoreRn->raiz;
    arvoreRn->raiz->esq->esq = criaNoRn(3);
    arvoreRn->raiz->esq->esq->cor = RED;
    arvoreRn->raiz->esq->esq->pai = arvoreRn->raiz->esq;
    arvoreRn->raiz->esq->dir = criaNoRn(8);
    arvoreRn->raiz->esq->dir->cor = RED;
    arvoreRn->raiz->esq->dir->pai = arvoreRn->raiz->esq;
    arvoreRn->raiz->dir->esq = criaNoRn(15);
    arvoreRn->raiz->dir->esq->cor = RED;
    arvoreRn->raiz->dir->esq->pai = arvoreRn->raiz->dir;
    arvoreRn->raiz->dir->dir = criaNoRn(20);
    arvoreRn->raiz->dir->dir->cor = RED;
    arvoreRn->raiz->dir->dir->pai = arvoreRn->raiz->dir;
    arvoreRn->raiz->esq->esq->esq = criaNoRn(2);
    arvoreRn->raiz->esq->esq->esq->cor = RED;
    arvoreRn->raiz->esq->esq->esq->pai = arvoreRn->raiz->esq->esq;
    arvoreRn->raiz->esq->esq->dir = criaNoRn(5);
    arvoreRn->raiz->esq->esq->dir->cor = RED;
    arvoreRn->raiz->esq->esq->dir->pai = arvoreRn->raiz->esq->esq;

    printf("ok\n");
    printf("ant 6: %d", antecessor(arvoreRn, arvoreRn->raiz->esq)->idCliente);
    RemoverNoRn(arvoreRn, 6);

    return 0;
}

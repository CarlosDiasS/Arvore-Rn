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
    if (z != NULL)
    {
        z->pai = u->pai;
    }
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

void CorrigirRemocaoRn(ArvoreRn *arvore, NoRn *x)
{
    while (x != arvore->raiz && (x == NULL || x->cor == BLACK))
    {
        if (x == x->pai->esq)
        {
            NoRn *w = x->pai->dir; // Irmão de x

            // Caso 3.1: Irmão w é vermelho
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                LL(arvore, x->pai);
                w = x->pai->dir;
            }

            // Caso 3.2: Ambos os filhos de w são pretos
            if ((w->esq == NULL || w->esq->cor == BLACK) &&
                (w->dir == NULL || w->dir->cor == BLACK))
            {
                w->cor = RED;
                x = x->pai;
            }
            else
            {
                // Caso 3.3: Filho direito de w é preto
                if (w->dir == NULL || w->dir->cor == BLACK)
                {
                    if (w->esq != NULL)
                        w->esq->cor = BLACK;
                    w->cor = RED;
                    RR(arvore, w);
                    w = x->pai->dir;
                }

                // Caso 3.4: Filho direito de w é vermelho
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->dir != NULL)
                    w->dir->cor = BLACK;
                LL(arvore, x->pai);
                x = arvore->raiz;
            }
        }
        else
        {
            // Caso simétrico (x é filho direito)
            NoRn *w = x->pai->esq; // Irmão de x

            // Caso 1 simétrico: Irmão w é vermelho
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                RR(arvore, x->pai);
                w = x->pai->esq;
            }

            // Caso 2 simétrico: Ambos os filhos de w são pretos
            if ((w->dir == NULL || w->dir->cor == BLACK) &&
                (w->esq == NULL || w->esq->cor == BLACK))
            {
                w->cor = RED;
                x = x->pai;
            }
            else
            {
                // Caso 3 simétrico: Filho esquerdo de w é preto
                if (w->esq == NULL || w->esq->cor == BLACK)
                {
                    if (w->dir != NULL)
                        w->dir->cor = BLACK;
                    w->cor = RED;
                    LL(arvore, w);
                    w = x->pai->esq;
                }

                // Caso 4 simétrico: Filho esquerdo de w é vermelho
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                if (w->esq != NULL)
                    w->esq->cor = BLACK;
                RR(arvore, x->pai);
                x = arvore->raiz;
            }
        }
    }

    if (x != NULL)
    {
        x->cor = BLACK;
    }
}

bool RemoverNoRn(ArvoreRn *grafo, int idCliente)
{

    NoRn *aux = buscaNo(idCliente, grafo->raiz);
    if (aux == NULL || grafo == NULL || grafo->raiz == NULL)
    {
        return false;
    }
    // teste
    printf("no : %d\n", aux->idCliente);

    NoRn *noAntecessor = antecessor(grafo, aux);
    NoRn *w, *x = NULL;
    Cor temp = aux->cor;

    // caso 0 raiz OK
    if (aux->pai == NULL)
    {
        free(aux);
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
            free(aux);
            // TESTE
            printf("caso 1.1: \n");
            printf("No %d removido.\n", idCliente);
            return true;
        }
        // a esquerda, sendo menor ou igual
        else
        {
            aux->pai->esq = NULL;
            free(aux);
            // TESTE
            printf("caso 1.2: \n");
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
        free(aux->dir);
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
        free(aux->esq);
        aux->esq = NULL;

        // TESTE
        printf("caso 2.2: \n");
        printf("No %d removido.\n", idCliente);
        return true;
    }

    // Caso 3, utilizando o no antecessor

    if (aux->esq != NULL && aux->dir != NULL)
    {
        printf("ok1 \n");
        temp = noAntecessor->cor;
        printf("ok1 \n");
        x = noAntecessor->esq;
        printf("ok2 \n");
        if (noAntecessor->pai == aux)
        {
            if (x != NULL)
                x->pai = noAntecessor;
        }
        else
        {
            TransplanteRn(grafo, noAntecessor, noAntecessor->esq);
            noAntecessor->esq = aux->esq;
            if (noAntecessor->esq != NULL)
            {
                noAntecessor->esq->pai = noAntecessor;
            }
        }
        TransplanteRn(grafo, aux, noAntecessor);
        noAntecessor->dir = aux->dir;
        noAntecessor->dir->pai = noAntecessor;
        noAntecessor->cor = aux->cor;
    }

    free(aux);
    if (temp == BLACK)
    {
        CorrigirRemocaoRn(grafo, x);
    }
    printf("ok6 \n");
    return true;
}

int main()
{
    // teste arvore mock OK
    ArvoreRn *arvoreRn = criaArvore();
    arvoreRn->raiz = criaNoRn(12);
    arvoreRn->raiz->cor = BLACK;

    arvoreRn->raiz->esq = criaNoRn(6);
    arvoreRn->raiz->esq->cor = RED;
    arvoreRn->raiz->esq->pai = arvoreRn->raiz; // Ponteiro para o pai
    arvoreRn->raiz->dir = criaNoRn(18);
    arvoreRn->raiz->dir->cor = BLACK;
    arvoreRn->raiz->dir->pai = arvoreRn->raiz; // Ponteiro para o pai

    arvoreRn->raiz->esq->esq = criaNoRn(3);
    arvoreRn->raiz->esq->esq->cor = BLACK;
    arvoreRn->raiz->esq->esq->pai = arvoreRn->raiz->esq; // Ponteiro para o pai
    arvoreRn->raiz->esq->dir = criaNoRn(8);
    arvoreRn->raiz->esq->dir->cor = BLACK;
    arvoreRn->raiz->esq->dir->pai = arvoreRn->raiz->esq; // Ponteiro para o pai

    arvoreRn->raiz->esq->esq->esq = criaNoRn(2);
    arvoreRn->raiz->esq->esq->esq->cor = RED;
    arvoreRn->raiz->esq->esq->esq->pai = arvoreRn->raiz->esq->esq; // Ponteiro para o pai

    arvoreRn->raiz->esq->esq->dir = criaNoRn(5);
    arvoreRn->raiz->esq->esq->dir->cor = RED;
    arvoreRn->raiz->esq->esq->dir->pai = arvoreRn->raiz->esq->esq; // Ponteiro para o pai

    arvoreRn->raiz->dir->dir = criaNoRn(20);
    arvoreRn->raiz->dir->dir->cor = RED;
    arvoreRn->raiz->dir->dir->pai = arvoreRn->raiz->dir; // Ponteiro para o pai

    arvoreRn->raiz->dir->esq = criaNoRn(15);
    arvoreRn->raiz->dir->esq->cor = RED;
    arvoreRn->raiz->dir->esq->pai = arvoreRn->raiz->dir; // Ponteiro para o pai

    RemoverNoRn(arvoreRn, 6);
    if (buscaNo(6, arvoreRn->raiz))
    {
        printf("fodeo");
    }
    else
    {
        printf("bom\n");
    }
    printf("id %d", buscaNo(12, arvoreRn->raiz)->esq->idCliente);
    return 0;
}

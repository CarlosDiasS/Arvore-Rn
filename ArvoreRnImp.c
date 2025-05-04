#include "ArvoreRn.h"

#define MAX 1000

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
    aux->vetor = NULL;
    return aux;
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
    return true;
}

bool LL(ArvoreRn *grafo, NoRn *no)
{

    if (no == NULL || no->dir == NULL || grafo->raiz == NULL)
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
    return true;
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

NoRn *menorNo(NoRn *no)
{
    while (no != NULL && no->esq != NULL)
    {
        no = no->esq;
    }
    return no;
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

void CorrigirRemocaoRn(ArvoreRn *arvore, NoRn *x)
{
    while (x != arvore->raiz && (x == NULL || x->cor == BLACK))
    {
        if (x == x->pai->esq)
        {
            NoRn *w = x->pai->dir;

            // Caso 3.1: w é vermelho
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
        // Simetria
        else
        {
            NoRn *w = x->pai->esq;

            // Caso 3.1 simétrico: Irmão w é vermelho
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                RR(arvore, x->pai);
                w = x->pai->esq;
            }

            // Caso 3.2 simétrico: Ambos os filhos de w são pretos
            if ((w->dir == NULL || w->dir->cor == BLACK) &&
                (w->esq == NULL || w->esq->cor == BLACK))
            {
                w->cor = RED;
                x = x->pai;
            }
            else
            {
                // Caso 3.3 simétrico: Filho esquerdo de w é preto
                if (w->esq == NULL || w->esq->cor == BLACK)
                {
                    if (w->dir != NULL)
                        w->dir->cor = BLACK;
                    w->cor = RED;
                    LL(arvore, w);
                    w = x->pai->esq;
                }

                // Caso 3.4 simétrico: Filho esquerdo de w é vermelho
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
    if (aux == NULL)
    {
        return false;
    }

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
            return true;
        }
        // a esquerda, sendo menor ou igual
        else
        {
            aux->pai->esq = NULL;
            free(aux);
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
        free(aux->dir);
        return true;
    }

    // Caso 2.2, sem filhos a direita OK

    if (aux->dir == NULL && aux->esq != NULL)
    {
        NoRn *temp = aux->esq;
        aux = aux->esq;
        aux->cor = temp->cor;
        aux->esq = NULL;
        free(aux->esq);
        return true;
    }

    // Caso 3, utilizando o no antecessor

    if (aux->esq != NULL && aux->dir != NULL)
    {
        temp = noAntecessor->cor;
        x = noAntecessor->esq;
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
    return true;
}

void imprimirPreOrdem(NoRn *no)
{
    if (no != NULL)
    {
        printf("%d %s\n", no->idCliente, no->cor == RED ? "RED" : "BLACK");
        imprimirPreOrdem(no->esq);
        imprimirPreOrdem(no->dir);
    }
}

void ajustarInsercao(ArvoreRn *arvore, NoRn *novoNo)
{
    while (novoNo != arvore->raiz && novoNo->pai->cor == RED)
    {
        if (novoNo->pai == novoNo->pai->pai->esq)
        {
            NoRn *tio = novoNo->pai->pai->dir;

            if (tio != NULL && tio->cor == RED)
            {
                // Caso 1: Tio vermelho
                novoNo->pai->cor = BLACK;
                tio->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                novoNo = novoNo->pai->pai;
            }
            else
            {
                // Caso 2: Tio preto e nó é filho direito
                if (novoNo == novoNo->pai->dir)
                {
                    novoNo = novoNo->pai;
                    LL(arvore, novoNo);
                }
                // Caso 3: Tio preto e nó é filho esquerdo
                novoNo->pai->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                RR(arvore, novoNo->pai->pai);
            }
        }
        else
        {
            // Caso simétrico
            NoRn *tio = novoNo->pai->pai->esq;

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
    arvore->raiz->cor = BLACK;
}

void inserirNo(int idCliente, ArvoreRn *arvore)
{
    NoRn *novoNo = criaNoRn(idCliente);
    if (novoNo == NULL)
        return;

    NoRn *y = NULL;
    NoRn *x = arvore->raiz;

    // Encontra a posição de inserção
    while (x != NULL)
    {
        y = x;
        if (idCliente < x->idCliente)
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
        arvore->raiz = novoNo;
    }
    else if (idCliente < y->idCliente)
    {
        y->esq = novoNo;
    }
    else
    {
        y->dir = novoNo;
    }

    ajustarInsercao(arvore, novoNo);
}

ArvoreRn *tratarInputDados(FilaAtendimento *fila)
{
    ArvoreRn *grafo = criaArvore();

    for (int i = 0; i < fila->totalAtendimentos; i++)
    {

        if (fila->vetor[i] != -1)
        {
            inserirNo(fila->vetor[i], grafo);
            printf("ins: %d\n", fila->vetor[i]);
        }
        else
        {
            NoRn *aux = menorNo(grafo->raiz);
            printf("rem: %d\n", aux->idCliente);
            RemoverNoRn(grafo, aux->idCliente);
        }
    }
    return grafo;
}

void insercaoNaFila(FilaAtendimento *fila)
{

    fila->vetor = malloc(sizeof(int) * MAX);
    int aux = 0;
    while (scanf("%d", &aux) == 1)
    {
        fila->vetor[fila->totalAtendimentos] = aux;
        fila->totalAtendimentos++;
    }
}

int main()
{

    // clock
    //  input e tratamento de dados
    FilaAtendimento *fila = criaFila();

    // popular a fila
    insercaoNaFila(fila);

    // tratar insercoes na fila
    ArvoreRn *grafo = tratarInputDados(fila);

    // impressao
    imprimirPreOrdem(grafo->raiz);
    return 0;
}
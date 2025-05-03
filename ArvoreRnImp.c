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
    if (aux == NULL || grafo == NULL || grafo->raiz == NULL)
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
        free(aux->dir);
        aux->dir = NULL;
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

// FUNÇAÕ INSERÇÃO
// FUNÇÃO REMOÇAO ok
// FUNCAO PRINT (ALTERAR COR DE EXIBICAO: R/N)
// grafico em log N (relatorio)

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

void imprimirGrafo(ArvoreRn *grafo){
    printf("teste");
}

bool inserirNoRn(int idCliente, ArvoreRn *grafo){
    return false;
}

ArvoreRn *tratarInputDados(FilaAtendimento *fila)
{

    int totalEntradas = sizeof(fila->vetor) / sizeof(int); // ou entao receber por parametro
    fila->totalAtendimentos = totalEntradas;
    ArvoreRn *grafo = criaArvore();

    for (int i = 0; i < totalEntradas; i++)
    {

        if (fila->vetor[i] != -1)
        {
            inserirNoRn(fila->vetor[i], grafo);
            // testar com printf aqui
        }
        else
        {
            RemoverNoRn(grafo,fila->vetor[i]);
            // testar com printf aqui
        }
    }
    return grafo;
}

int main()
{
    // main ofc:

    // input e tratamento de dados
    FilaAtendimento *fila = criaFila();

    // um for para popular a fila(scanf)

    ArvoreRn *grafo = tratarInputDados(fila);
    imprimirGrafo(grafo);

    return 0;
}
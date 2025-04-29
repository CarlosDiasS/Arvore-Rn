#include "ArvoreRn.h"

// função que busca um nó na ARN (se Deus quiser tá certo)

// verificar busca feita em lab(aeds2)

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
        return atual;
    }

    // DPS FAZER UMA BUSCA RECURSIVA

    // retorna o nó encontrado ou NIL se não encontrado (vulgo se deu merda)
}

// função que verifica se um cliente está na fila
bool clienteNaFila(int idCliente, NoRn *raiz)
{
    NoRn *resultado = buscaNo(idCliente, raiz);
    return (resultado != NULL) ? true : false;
    // ternario
}

// função auxiliar para testar se a busca deu certo
void testarBusca(int idCliente, NoRn *raiz)
{
    if (clienteNaFila(idCliente, raiz))
    {
        printf("Cliente com ID %d esta na fila de atendimento.\n", idCliente);
    }
    else
    {
        printf("Cliente com ID %d NAO esta na fila de atendimento.\n", idCliente);
    }
} // agora a gente reza pra nao ter dado algum erro
// a partir daqui é sucessofefe

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

int main()
{
    //teste
    ArvoreRn *arvoreRn = criaArvore();
    arvoreRn->raiz = criaNoRn(12);
    arvoreRn->raiz->esq = criaNoRn(6);
    arvoreRn->raiz->dir = criaNoRn(18);
    arvoreRn->raiz->esq->esq = criaNoRn(3);
    arvoreRn->raiz->esq->dir= criaNoRn(8);
    arvoreRn->raiz->dir->esq = criaNoRn(15);
    arvoreRn->raiz->dir->dir= criaNoRn(20);

    NoRn *buscado = buscaNo(3,arvoreRn->raiz);
    printf("idCliente %d achado.\n", buscado->idCliente);
    if(clienteNaFila(15,arvoreRn->raiz)){
        printf("cliente na fila.\n");
    }

    return 0;
}

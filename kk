bool balanceamentoRn(ArvoreRn *grafo, int idCliente)
{

    NoRn *raiz = grafo->raiz;
    NoRn *x = buscaNo(idCliente, raiz);
    NoRn *w = NULL;

    while (x != grafo->raiz && x->cor == BLACK)
    {

        if (x == x->pai->esq)
        {
            w = x->pai->dir;

            // Caso 3.1
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                LL(grafo, x->pai);
                w = x->pai->dir;
            }

            // Caso 3.2
            if (w->esq->cor == BLACK && w->dir->cor == BLACK)
            {
                w->cor = RED;
                x = x->pai;
            }

            // Casos 3.3 e 3.4
            else if (w->dir->cor == BLACK)
            {
                w->esq->cor = BLACK;
                w->cor = RED;
                RR(grafo, w);
                w = x->pai->dir;
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
            }
            w->dir->cor = BLACK;
            LL(grafo, x->pai);
            x = grafo->raiz;
        }

        // simetria
        else
        {
            w = x->pai->esq;

            // Caso 3.1 simetrico
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                LL(grafo, x->pai);
                w = x->pai->esq;
            }

            // Caso 3.2 simetrico
            if (w->dir->cor == BLACK && w->esq->cor == BLACK)
            {
                w->cor = RED;
                x = x->pai;
            }

            // Casos 3.3 e 3.4 simetricos
            else if (w->esq->cor == BLACK)
            {
                w->dir->cor = BLACK;
                w->cor = RED;
                RR(grafo, w);
                w = x->pai->esq;
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
            }
            w->esq->cor = BLACK;
            LL(grafo, x->pai);
            x = grafo->raiz;
        }
    }
    x->cor = BLACK;
    return true;
}
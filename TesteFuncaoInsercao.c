#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    BLACK,
    RED
} Cor;

typedef struct NoRn {
    int idCliente;
    Cor cor;
    struct NoRn *esq;
    struct NoRn *dir;
    struct NoRn *pai;
} NoRn;

typedef struct {
    NoRn *raiz;
} ArvoreRn;

NoRn *criaNoRn(int idCliente) {
    NoRn *aux = malloc(sizeof(NoRn));
    aux->esq = NULL;
    aux->dir = NULL;
    aux->pai = NULL;
    aux->idCliente = idCliente;
    aux->cor = RED; // Novo nó sempre começa como vermelho
    return aux;
}

ArvoreRn *criaArvore() {
    ArvoreRn *aux = malloc(sizeof(ArvoreRn));
    aux->raiz = NULL;
    return aux;
}

// Funções de rotação corrigidas
void RR(ArvoreRn *arvore, NoRn *no) {
    NoRn *filhoEsq = no->esq;
    no->esq = filhoEsq->dir;
    
    if (filhoEsq->dir != NULL) {
        filhoEsq->dir->pai = no;
    }
    
    filhoEsq->pai = no->pai;
    
    if (no->pai == NULL) {
        arvore->raiz = filhoEsq;
    } else if (no == no->pai->dir) {
        no->pai->dir = filhoEsq;
    } else {
        no->pai->esq = filhoEsq;
    }
    
    filhoEsq->dir = no;
    no->pai = filhoEsq;
}

void LL(ArvoreRn *arvore, NoRn *no) {
    NoRn *filhoDir = no->dir;
    no->dir = filhoDir->esq;
    
    if (filhoDir->esq != NULL) {
        filhoDir->esq->pai = no;
    }
    
    filhoDir->pai = no->pai;
    
    if (no->pai == NULL) {
        arvore->raiz = filhoDir;
    } else if (no == no->pai->esq) {
        no->pai->esq = filhoDir;
    } else {
        no->pai->dir = filhoDir;
    }
    
    filhoDir->esq = no;
    no->pai = filhoDir;
}

void ajustarInsercao(ArvoreRn *arvore, NoRn *novoNo) {
    while (novoNo != arvore->raiz && novoNo->pai->cor == RED) {
        if (novoNo->pai == novoNo->pai->pai->esq) {
            NoRn *tio = novoNo->pai->pai->dir;
            
            if (tio != NULL && tio->cor == RED) {
                // Caso 1: Tio vermelho
                novoNo->pai->cor = BLACK;
                tio->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                novoNo = novoNo->pai->pai;
            } else {
                // Caso 2: Tio preto e nó é filho direito
                if (novoNo == novoNo->pai->dir) {
                    novoNo = novoNo->pai;
                    LL(arvore, novoNo);
                }
                // Caso 3: Tio preto e nó é filho esquerdo
                novoNo->pai->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                RR(arvore, novoNo->pai->pai);
            }
        } else {
            // Caso simétrico
            NoRn *tio = novoNo->pai->pai->esq;
            
            if (tio != NULL && tio->cor == RED) {
                novoNo->pai->cor = BLACK;
                tio->cor = BLACK;
                novoNo->pai->pai->cor = RED;
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->esq) {
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

void inserirNo(int idCliente, ArvoreRn *arvore) {
    NoRn *novoNo = criaNoRn(idCliente);
    if (novoNo == NULL) return;

    NoRn *y = NULL;
    NoRn *x = arvore->raiz;

    // Encontra a posição de inserção
    while (x != NULL) {
        y = x;
        if (idCliente < x->idCliente) {
            x = x->esq;
        } else {
            x = x->dir;
        }
    }

    novoNo->pai = y;

    if (y == NULL) {
        arvore->raiz = novoNo;
    } else if (idCliente < y->idCliente) {
        y->esq = novoNo;
    } else {
        y->dir = novoNo;
    }

    ajustarInsercao(arvore, novoNo);
}

void imprimirPreOrdem(NoRn *no) {
    if (no != NULL) {
        printf("%d %s\n", no->idCliente, no->cor == RED ? "RED" : "BLACK");
        imprimirPreOrdem(no->esq);
        imprimirPreOrdem(no->dir);
    }
}

int main() {
    ArvoreRn *arvoreRn = criaArvore();
    
    // Inserções na ordem correta para manter 12 como raiz
    inserirNo(12, arvoreRn);
    inserirNo(5, arvoreRn);
    inserirNo(56, arvoreRn);
    inserirNo(20, arvoreRn);
    inserirNo(1, arvoreRn);
    inserirNo(57, arvoreRn);
    inserirNo(2, arvoreRn);

    printf("Árvore Rubro-Negra em pré-ordem:\n");
    imprimirPreOrdem(arvoreRn->raiz);

    printf("\nRaiz: %d\n", arvoreRn->raiz->idCliente);
    printf("Cor da raiz: %s\n", arvoreRn->raiz->cor == RED ? "RED" : "BLACK");

    return 0;
}
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//java na veia
typedef enum {
    BLACK,
    RED,
} Cor;

typedef struct NoRn{
    int idCliente;
    Cor cor;
    struct NoRn *esq;
    struct NoRn *dir;
    struct NoRn *pai;
}NoRn;


//cabeçalhos das funcoes e comentarios


NoRn *buscaNo(int idCliente, NoRn *raiz);



void removerNoRn(int idCliente, NoRn *arvore);


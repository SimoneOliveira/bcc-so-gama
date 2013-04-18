#include <stdio.h>
#include <stdlib.h>
#include "GeMem.h"

int main()
{
    char *Teste1 = Aloc(1);
    char *Teste2 = Aloc(2);
    char *Teste3 = Aloc(3);
    char *Teste4 = Aloc(4);
    char *Teste5 = Aloc(5);

    Libera(Teste4);

    char *Teste6 = Aloc(2);
    printf("\n");
    printf("Teste1 %d\n",PMemoria->nTam);
    printf("Teste2 %d\n",PMemoria->oProx->nTam);
    printf("Teste3 %d\n",PMemoria->oProx->oProx->nTam);
    printf("Teste4 %d\n",PMemoria->oProx->oProx->oProx->nTam);
    printf("Teste5 %d\n",PMemoria->oProx->oProx->oProx->oProx->nTam);
    //printf("Teste6 %d\n",PMemoria->oProx->oProx->oProx->oProx->oProx->nTam);



    return 0;
}

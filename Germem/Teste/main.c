#include <stdio.h>
#include <stdlib.h>
#include "GeMem.h"

int main()
{

    char *Teste1 = Aloc(26);
    char *Teste2 = Aloc(286);
    char *Teste3 = Aloc(6);
    char *Teste4 = Aloc(1);
    Memoria *Aux = PMemoria;

    while(Aux!=NULL){
        printf("Aloc= %c Teste1 %d\n",Aux->lAloc,Aux->nMem);
        Aux = Aux->oProx;
    }

    Memoria* oBus =BuscarMem(Teste1);
    Libera(Teste1);
    Libera(Teste2);

    Aux = PMemoria;
    while(Aux!=NULL){
        printf("Aloc= %c Teste1 %d\n",Aux->lAloc,Aux->nTam);
        Aux = Aux->oProx;
    }

    char *Teste5 = Aloc(1000);
    char *Teste6 = Aloc(4);
    Libera(Teste4);
    char *Teste7 = Aloc(50);

    printf("\n");

    Aux = PMemoria;
    while(Aux!=NULL){
        printf("Aloc= %c Teste1 %d\n",Aux->lAloc,Aux->nTam);
        Aux = Aux->oProx;
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "GeMem.h"

char* Aloc(int tnTam){
    if(Limite<tnTam)
        return NULL;

    GerMemInit(); //seta espaço vazio total como primeiro no da lista

    Memoria *lsMem = AlocMem(PMemoria,tnTam);

    if(lsMem==NULL)
        return NULL;

    return lsMem->nMem;
}

Memoria* AlocMem(Memoria *toAtu,int tnTam)
{
    int nFalta = tnTam;
    Memoria *lsMem,*lsAnt,*lsPro,*lsEsp;

    // BUSCA O PRIMEIRO ESPAÇO VAZIO
    lsMem = BuscaEsp(toAtu);

    if(lsMem==NULL)
        return NULL;

    lsMem->lAloc='s';
    lsAnt = lsMem->oAnt;
    lsPro = lsMem->oProx;

    nFalta = lsMem->nTam - nFalta;

    // cria espaço com o que sobrar
    if(nFalta > 0){
        lsEsp = AlocEsp(nFalta);
        lsEsp->nMem  = lsMem->nMem + tnTam;
        lsEsp->oAnt  = lsMem;
        lsEsp->oProx = lsPro;
        lsPro        = lsEsp;
        lsMem->nTam  = lsMem->nTam - nFalta;
        nFalta=0;
    }
    // SE NÃO FALTA MAIS ESPAÇO PARA SER ALOCADO, MARCA COMO FINAL
    if(nFalta==0)
        lsMem->lFim='s';
    // SE FALTAR ESPAÇO ALOCA EM OUTRO LUGAR
    if(nFalta < 0){
        nFalta = nFalta*-1;
        lsPro = AlocMem(lsMem->oProx,nFalta);

        if(lsPro==NULL){
            lsMem->lAloc=' ';
            return NULL;
        }
        lsPro->oAnt->oProx = lsPro->oProx;
        if(lsPro->oProx!=NULL){
            lsPro->oProx->oAnt = lsPro->oAnt;
        }
        lsPro->oProx = lsMem->oProx;
    }

    if(lsAnt!=NULL)
        lsAnt->oProx = lsMem;
    if(lsPro!=NULL)
        lsPro->oAnt  = lsMem;

    lsMem->oAnt  = lsAnt;
    lsMem->oProx = lsPro;

    return lsMem;
}
Memoria* BuscaEsp(Memoria *toMem){
    if(toMem==NULL)
        return NULL;

    Memoria *lsAux = toMem;
    while(lsAux->oProx!=NULL)
    {
        if(lsAux->lAloc == ' '){
            return(lsAux);
        }
        lsAux = lsAux->oProx;
    }

    if(lsAux->lAloc==' ')
        return lsAux;

    return NULL;
}

Memoria* AlocEsp(int tnTam)
{
    Memoria *lsEsp;

    lsEsp=(Memoria*)malloc(sizeof(Memoria));
    lsEsp->lAloc = ' ';
    lsEsp->lFim  = ' ';
    lsEsp->nTam  = tnTam;

    return lsEsp;
}

void Libera(char *tpMem){
    // se a lista está nula ignora
    if(PMemoria == NULL){
        return;
    }
    Memoria *Aux;
    Aux = BuscarMem(tpMem);

    // se retornar null não tem nada para fazer
    if(Aux==NULL)
        return;

    while(Aux->lFim != 's')
    {
        Aux->lAloc = ' ';
        nAloc = nAloc - Aux->nTam;
        Aux->lFim = ' ';
        Aux = Aux->oProx;
    }
    // apaga o ultimo no
    Aux->lAloc = ' ';
    Aux->lFim = ' ';
}

Memoria* BuscarMem(char *tnMem)
{
    Memoria *MAux;
    MAux = PMemoria; //coloca a lista atual na lista auxiliar

    while(MAux != NULL)
    {
		if (tnMem >= MAux->nMem && tnMem < (MAux->nMem+MAux->nTam))
		{
			while (MAux->oAnt != NULL){

				if(MAux->oAnt->lFim=='s'){
					break;
				}
				else
					MAux = MAux->oAnt;
			}
			break;
		}

		MAux = MAux->oProx;
	}
	return MAux;
}

void GerMemInit()
{
	 // cria a lista inicial caso ela não exista
	if(PMemoria == NULL){
        PMemoria 		= (Memoria*)malloc(sizeof(Memoria));
		PMemoria->nMem 	= cHeap;
		PMemoria->nTam 	= sizeof(cHeap);
		PMemoria->lAloc = ' ';
		PMemoria->lFim	= ' ';
		PMemoria->oProx	= NULL;
		PMemoria->oAnt	= NULL;

		nAloc = 0;
	}
}

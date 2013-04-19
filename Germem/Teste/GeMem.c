#include <stdio.h>
#include <stdlib.h>
#include "GeMem.h"

//Funçao que insere na memoria
char* Aloc(int tnTam){

    if(Limite<tnTam)
        return NULL;

    GerMemInit(); //seta espaço vazio total como primeiro no da lista

   // if((nAloc+tnTam)>Limite)
     //   return NULL;

    int tnTamAux = tnTam,nSobra;
    Memoria *lsMem,*lsEsp,*Aux;//criando ponteiro nova lista de memoria.
    lsMem=(Memoria*)malloc(sizeof(Memoria));//alocando o espaço em memória e converte
    lsMem->nMem  = 0;
    Aux = PMemoria;

    while(tnTamAux!=0){
        if(Aux->lAloc == ' '){
            lsMem=(Memoria*)malloc(sizeof(Memoria));//alocando o espaço em memória e converte

            // novo no para o espaço
            lsMem->nMem  = Aux->nMem;
            lsMem->lFim = ' ';
            lsMem->lAloc = 's';
            nSobra = Aux->nTam;


            // verifica se falta espaço para gravar
            if(nSobra < tnTamAux){
                lsMem->nTam = nSobra;
                tnTamAux= tnTamAux - nSobra;
                nSobra=0;
            }
            else
            {
                // verifica se sobra espaço
                if(nSobra > tnTamAux){
                    lsMem->nTam = tnTamAux;
                    nSobra = nSobra - tnTamAux;
                    tnTamAux = 0;
                }
                // verifica se tem o espaço exato
                else{
                    lsMem->nTam = tnTamAux;
                    tnTamAux = 0;
                    nSobra   = 0;
                }
            }
            nAloc = nAloc + lsMem->nTam;

            // guarda o anterior
            lsMem->oAnt  = Aux->oAnt;
            lsMem->oProx = Aux->oProx;

            // coloca a nova memoria como proxima da anterior
            if(Aux->oAnt!=NULL){
                Aux->oAnt->oProx = lsMem;
            }
            // coloca a nova memoria como atual como anterior
            if(Aux->oProx!=NULL){
                Aux->oProx->oAnt = lsMem;
            }

            // se não faltar mais memoria para alocar, marca como final
            if(tnTamAux==0){
                lsMem->lFim = 's';

                if(nSobra > 0){
                    lsEsp=(Memoria*)malloc(sizeof(Memoria));
                    lsEsp->lAloc = ' ';
                    lsEsp->lFim  = ' ';
                    lsEsp->nMem  = Aux->nMem + nSobra;

                    lsEsp->nTam  = nSobra;
                    lsEsp->oAnt  = lsMem;
                    lsEsp->oProx = Aux->oProx;

                    // COLOCA O ESPAÇO LIVRE NA FRENTE DO ESPAÇO ALOCADO
                    lsMem->oProx = lsEsp;
                }
            }

            // VERIFICA SE É O PRIMEIRO
            if(Aux == PMemoria){
                PMemoria = lsMem;
                PMemoria->oAnt = NULL;
            }
        }

        // Não precisa alocar mais nada
        if(tnTamAux==0)
            break;

        // proximo da lista
        if(Aux->oProx==NULL){
            tnTamAux = 0;

            while(lsMem->oAnt!=NULL){
                if(lsMem->lFim == ' ')
                    lsMem->lAloc = ' ';
                else
                    break;
                lsMem = lsMem->oAnt;
            }


            return NULL;
        }
        //free(Aux);
        Aux = Aux->oProx;
    }

    return lsMem->nMem;
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

    Memoria *oAnt,*oProx;
    // guarda a lista anterior
    oAnt = Aux->oAnt;

    while(Aux->lFim != 's')
    {
        Aux->lAloc = ' ';
        nAloc = nAloc - Aux->nTam;
        Aux->lFim = ' ';
        Aux = Aux->oProx;
    }
    //guarda o proximo
    oProx = Aux->oProx;
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
		if (tnMem >= MAux->nMem && tnMem <= (MAux->nMem+MAux->nTam))
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

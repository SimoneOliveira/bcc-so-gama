
#ifndef FUNCOES_H
#define FUNCOES_H

#define Limite 1024

typedef struct MyMem
{
  char *nMem;
  int nTam;
  char lAloc;
  char lFim;
  struct MyMem *oProx;
  struct MyMem *oAnt;

} Memoria;

Memoria *PMemoria;
char cHeap[Limite];
int nAloc;

void GerMemInit();
Memoria* AlocMem(Memoria *,int);
Memoria* AlocEsp(int);
Memoria* BuscaEsp(Memoria *);
Memoria* BuscarMem(char *);

void Libera(char *);
char* Aloc(int);

#endif

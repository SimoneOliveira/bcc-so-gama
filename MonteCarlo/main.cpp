#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#define NUMTHR 1  // Numero total de threads
#define NUMCHA 100000000   // Numero total de threads

int nPtos [NUMTHR]; // Total de pontos da thread
int nPCir [NUMTHR]; // Pontos no circulo

void *Calcular (void *tnParam); // sorteia e verifica os pontos pela thread
double fRand(double fMin, double fMax);

int main (int argc, char *argv[])
{
    int nI;
    double nPi   = 0;  // contem o valor de pi
    int nTPoints = 0; // total de pontos
    int nTCirc   = 0; // pontos no circulo
    pthread_t oTid[NUMTHR];  // ID das threads

    // cria todas as threads
    for (nI = 0; nI< NUMTHR ; nI++)
    {
        // cria a i-esima thread
        pthread_create (&oTid[nI], NULL, Calcular, &nI);
    }

    // Para cada thread
    for (nI = 0; nI< NUMTHR ; nI++)
    {
        // espera que as threads terminem
        pthread_join (oTid[nI], NULL);
    }

    for (nI = 0; nI < NUMTHR ; nI++)
    {
        nTPoints += nPtos[nI];  // totalp = totalp + num_ptos[i]
        nTCirc   += nPCir[nI]; // totalc = totalp + num_ptos[i]
    }

    // Calcula o valor de pi e imprime na tela
    nPi = 4.0*(((double)nTCirc)/((double)nTPoints)); // transforma totalp
    // e totalc em double
    printf("Valor de PI:%lf    \n",nPi);
}

void *Calcular (void *tnParam)
{
    int nI;
    int nThrNum = *((int *)tnParam); // O número da thread ()
    double nX,nY,nQuad;
    nPtos[nThrNum] = 0;
    nPCir[nThrNum] = 0;

    for (nI = 0; nI < NUMCHA; nI++)
    {
        nX    = fRand(0,2); // sorteia um número de 0 a 1
        nY    = fRand(0,2 ); // sorteia um número de 0 a 1
        nQuad = sqrt(pow(nX-1,2) + pow(nY-1,2));
        // Se a soma dos quadrados for menor que R = 1
        // então caiu no círculo
        if (nQuad <= 1)
        {
            nPCir[nThrNum] ++; // conta pontos no círculo
        }
        nPtos[nThrNum] ++; // incrementa os pontos totais da thread N (0 a 9)
    }
    pthread_exit(0);
}
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

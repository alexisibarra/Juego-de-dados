/*
 * =====================================================================================
 *
 *       Filename:  juegodedados_h.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/07/13 16:07:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexis Ibarra (ai), ar.ibarrasalas@gmail.com
 *   Organization:  Universidad Simón Bolívar
 *
 * =====================================================================================
 */

#include <errno.h>
#include <pthread.h>
#include "funciones.h"

struct parametros {
	int n;
	int nvalue;
	int randN;
};

void *jugada(void *arg)
{
	struct parametros * p;
	p = ( struct parametros *) arg;
	int *cuenta = (int *) malloc(sizeof(int));
	printf("#####################################%d\n",p->n);
	*cuenta = tirarDados(p->n,p->nvalue,p->randN);
	pthread_exit(cuenta);
}

int
main (int argc, char **argv)
{
	int t;
	int *tiempo_dormido1, *tiempo_dormido2;

	int * p = procCML(argc,argv);
	int nvalue=p[0]; 
	int svalue=p[1]; 
	int jvalue=p[2]; 
	int i, n;
  int status;
	int ganador=0;
	int mayorPuntaje=0;
	int totalTirada=0; 
  pid_t childpid;
//	srand(svalue);
	srand(rdtsc());

	pthread_t threads[jvalue];
	for(t=0;t<jvalue;t++){
		int randN = rand();
		struct parametros vars;
		vars.n = t;
		vars.nvalue = nvalue;
		vars.randN = randN;
		if (pthread_create(&threads[t], NULL, (void*) jugada, (void*)&vars)){
			perror("No se puede crear el hilo");
		}
		
		pthread_join(threads[t], (void **)&tiempo_dormido1);
			totalTirada = tirarDados(i,nvalue,randN);
			if (totalTirada>mayorPuntaje){
				mayorPuntaje = (int)totalTirada;
				ganador = t+1;
			}
	}
  printf("**** Gana el jugador %d, con %d puntos\n", ganador, mayorPuntaje);
}


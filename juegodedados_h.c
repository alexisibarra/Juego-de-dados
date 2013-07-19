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

int
main (int argc, char **argv)
{
	int t;

	struct CML values;
	values = procCML(argc,argv);

	int i, n;
  int status;
	int ganador=0;
	int mayorPuntaje=0;
	int *totalTirada=0; 
	pthread_t threads[values.j];
	
	if(values.x){
		srand(rdtsc());
	}else{
		srand(values.s);
	}

	if (!values.h){
		for(t=0;t<values.j;t++){
			int randN = rand();
			struct parametros vars;
			vars.indice = t+1;
			vars.nvalue = values.n;
			vars.randN = randN;
			if (pthread_create(&threads[t], NULL, (void*) jugada, (void*)&vars)){
				perror("ERROR: pthread_create");
				break;
			}
		}
		for(t=0;t<values.j;t++){
			if(pthread_join(threads[t], (void **)&totalTirada)){
				perror("ERROR: pthread_join");
				break;
			};

			if (*totalTirada>mayorPuntaje){
				mayorPuntaje = (int)*totalTirada;
				ganador = t+1;
			}
		}
		printf("**** Gana el jugador %d, con %d puntos\n", ganador, mayorPuntaje);
	}
	return 0;
}


/*
 * =====================================================================================
 *
 *       Filename:  juegodedados_p.c
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
#include "funciones.h"

int
main (int argc, char **argv)
{
	struct CML values;
	values = procCML(argc,argv);
	int i;
  int status;
	int ganador=0;
	int ganadorPID; 
	int mayorPuntaje=0;
	int totalTirada=0; 
  pid_t childpid;
//	srand(values.s);
	srand(rdtsc());
	int procesos[values.j];
	if (!values.h){
		for (i = 1; i <= values.j; i++){
			int randN = rand();
			childpid=fork();
			procesos[i-1]=childpid;
			if (childpid==0){
				exit(tirarDados(i,values.n,randN));
			} else 
			if (childpid <= 0){
				printf("ERROR: fork() %s\n", strerror(errno));
				break;
			}
		}
		while (1) {
			childpid = wait(&status);
			totalTirada = status>>8;
			if (errno == ECHILD){
				break;
			}
			if ((childpid == -1) && (errno != EINTR) ){
				printf("ERROR: wait() %s\n", strerror(errno));
				break;
			}
			if (totalTirada>mayorPuntaje){
				mayorPuntaje = totalTirada;
				ganadorPID = childpid;
			}
		}
		for (i=0; i<values.j; i++){
			if(procesos[i]==ganadorPID){
				ganador=i+1;
			}
		}
		printf("**** Gana el jugador %d, con %d puntos\n", ganador, mayorPuntaje);
	}
	return 0;
}

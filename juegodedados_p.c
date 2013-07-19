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
	int * p = procCML(argc,argv);
	int nvalue=p[0]; 
	int svalue=p[1]; 
	int jvalue=p[2]; 
	int i, n;
  int status;
	int ganador=0;
	int mayorPuntaje=0;
	int totalTirada=0; 
	int ganadorPID; 
  pid_t childpid;
//	srand(svalue);
	srand(rdtsc());
	int procesos[jvalue];
  for (i = 1; i <= jvalue; i++){
		int randN = rand();
		childpid=fork();
		procesos[i-1]=childpid;
		if (childpid==0){
			totalTirada = tirarDados(i,nvalue,randN);
			exit(tirarDados(i,nvalue,randN));
//			exit(totalTirada);
		} else 
		if (childpid <= 0)
			break;
	}
  while (1) {
		childpid = wait(&status);
		totalTirada = status>>8;
		if ((childpid == -1) && (errno != EINTR))
			break;
		if (totalTirada>mayorPuntaje){
			mayorPuntaje = (int)totalTirada;
			ganadorPID = childpid;
		}
		printf ("===%d--%d\n",childpid,status>>8);
  }
	for (i=0; i<jvalue; i++){
		if(procesos[i]==ganadorPID){
			ganador=i;
		}
	}
  printf("**** Gana el jugador %d, con %d puntos\n", ganador, mayorPuntaje);
	return 0;
}

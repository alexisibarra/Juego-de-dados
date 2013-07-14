/*
 * =====================================================================================
 *
 *       Filename:  juegodedados_p.c
 *
 *    Description:  
 *
 *        Version:  procesos_1.0
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
  pid_t childpid;
//	srand(svalue);
	srand(rdtsc());
  for (i = 1; i <= jvalue; i++){
		int x = rand();
		childpid=fork();
		if (childpid==0){
			exit(tirarDados(i,nvalue,x));
		}else 
		if (childpid <= 0)
			break;
	}
  while (1) {
		childpid = wait(&status);
		if ((childpid == -1) && (errno != EINTR))
			break;
		printf("Un hijo con PID %d y padre %d termino con codigo de salida %d\n", childpid, getpid(), status>>8);
  }
  printf("Este es el proceso %ld con padre %ld\n", (long)getpid(), (long)getppid());
	return 0;
}

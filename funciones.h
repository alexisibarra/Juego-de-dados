/*
 * =====================================================================================
 *
 *       Filename:  funciones.h
 *
 *    Description:  Descripción de funciones comunes para ambas versiones de juego de dados
 *
 *        Version:  1.0
 *        Created:  14/07/13 18:12:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexis Ibarra (ai), ar.ibarrasalas@gmail.com
 *   Organization:  Universidad Simón Bolívar
 *
 * =====================================================================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sysexits.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  usage
 *  Description:  Despliega en pantalla un mensaje con la invocación correcta del progra
 *  							ma
 * =====================================================================================
 */
void usage(){
	printf("\n SINTAXIS:\n juegodedados_p [-n i] [-s x] [-h]\n -n i: tamano de la secuencia (por defecto, 10)\n -s x: semilla (por defecto, 1)\n -j y: numero de jugadores\n -h: imprime esta ayuda y sale\n\n");
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  help
 *  Description:  Imprime por pantalla el mensaje de ayuda del programa
 * =====================================================================================
 */
void help() {
  printf("\n juegodedados_p: imprime una secuencia de numeros aleatorios\n");
	usage();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isNumeric
 *  Description:  Función booleana que determina si un string dado es numérico
 *      Entrada:  s: String a analizar
 *       Salida:  1 en caso si s es numérica, 0 en caso contrario
 * =====================================================================================
 */
int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  procCML 
 *  Description:  Procesa la linea de argumentos con la que es invocado el programa
 *      Entrada:  argc: Número de argumentos 
 *      					argv: String con los argumentos
 *       Salida:  outputs: arreglo de strings con los flags y valores procesados
 * =====================================================================================
 */
int*
procCML (int argc, char **argv)
{
	int hflag=0,nflag=0,sflag=0,jflag=0;
  int nvalue,svalue,jvalue;
  int c;
	static int outputs[4];

  opterr = 0;

  while ((c = getopt (argc, argv, "hs:n:j:")) != -1)
    switch (c)
      {
      case 'h':
        hflag = 1;
        break;
      case 'n':
				if (optarg != NULL){
					if (isNumeric(optarg)){
						nvalue = atoi(optarg);
						if (nvalue>20){
							fprintf (stderr, "El argumento de -n debe estar entre 1 y 20\n");
							abort();
						}else{
							nflag = 1;
						}
					} else {
						fprintf (stderr, "Valor `%s' no válida.\n", optarg);
						abort();
					}
				}
        break;
      case 's':
				if (optarg != NULL){
					if (isNumeric(optarg)){
						svalue = atoi(optarg);
						sflag = 1;
					} else {
						fprintf (stderr, "Valor `%s' no válida.\n", optarg);
						abort();
					}
				}
        break;
      case 'j':
				if (optarg != NULL){
					if (isNumeric(optarg)){
						jvalue = atoi(optarg);
						jflag = 1;
					} else {
						fprintf (stderr, "Valor `%s' no válida.\n", optarg);
						abort();
					}
				}
        break;
      case '?':
				if (optopt == 's' || optopt == 'j' || optopt == 'n')
					fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
				else 
				if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				usage();
      default:
        abort ();
			}
	if (!sflag) svalue = 1;
	if (!nflag) nvalue = 10;
  if (hflag) 
		help();
	else if (!jflag){
		fprintf(stderr,"Debe especificar el número de jugadores\n");
	}
	else {
		printf("Numero de tiradas: %d\nSemilla: %d\nJugadores: %d\n",nvalue,svalue,jvalue);
	}
	outputs[0]=nvalue;
	outputs[1]=svalue;
	outputs[2]=jvalue;
	outputs[3]=hflag;
	return outputs;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  tirarDados
 *  Description:  Implementa la tirada de dados de un jugador, crea un fichero y escribe
 *  							en él la información de cada tirada y el número total de puntos.
 *      Entrada:  indice: Entero que representa el numero del jugador
 *      					nTiradas: Entero con el número de tiradas
 *      					seed: Entero con la semilla
 *       Salida:  cuenta: Entero con la suma de las tiradas del jugador
 * =====================================================================================
 */
int tirarDados(int indice, int nTiradas, int seed){
	srand(seed);
	int j;
	int cuenta=0;
	int tirada;
	FILE *fp;
	char nArchivo[80];
	printf("Soy el proceso %d\n",indice);
	printf("Generé: ");
	sprintf(nArchivo,"tirada_%d",indice);
  fp = fopen(nArchivo, "w+");   
  if (fp == NULL) {
    perror("El archivo no existe; fopen");
    exit(EX_USAGE);
  }
	fprintf(fp,"Jugador: %d\n",indice);
	fprintf(fp,"Número de tiradas: %d\n",nTiradas);
	for(j=1;j<=nTiradas;j++){
		tirada = 1+rand()%6;
		cuenta +=tirada; 
		printf("%d, ",tirada );
		fprintf(fp,"Tirada %d: %d\n",j,tirada);
	}
	fprintf(fp,"TOTAL: %d\n",cuenta);
	printf("el total es %d\n",cuenta);
	fclose(fp);
	return cuenta;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rdtsc
 *  Description:  Devuelve una semilla aletoria según las variables del equipo
 * =====================================================================================
 */
int rdtsc()
{
	__asm__ __volatile__("rdtsc");
}

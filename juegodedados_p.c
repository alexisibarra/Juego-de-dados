#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(){
	printf("\n SINTAXIS:\n juegodedados_p [-n i] [-s x] [-h]\n -n i: tamano de la secuencia (por defecto, 10)\n -s x: semilla (por defecto, 1)\n -j y: numero de jugadores\n -h: imprime esta ayuda y sale\n\n");
}

void help() {
  printf("\n juegodedados_p: imprime una secuencia de numeros aleatorios\n");
	usage();
}

int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}


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
						nflag = 1;
					} else {
						fprintf (stderr, "Valor `%s' no válida.\n", optarg);
						usage();
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
	outputs[0]=jvalue;
	outputs[1]=svalue;
	outputs[2]=nvalue;
	outputs[4]=hflag;
	return outputs;
}

int
main (int argc, char **argv)
{
	int * p = procCML(argc,argv);
	printf("%d",p[0]);
}

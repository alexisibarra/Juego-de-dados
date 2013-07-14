CC = gcc
CFLAGS = 
OBJS = juegodedados_p.o 

juegodedados_p: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@

juegodedados_p.o: juegodedados_p.c funciones.h
	$(CC) $(CFLAGS) -c juegodedados_p.c funciones.h

clean:
	/bin/rm *.o juegodedados_p tirada_* *.h.gch

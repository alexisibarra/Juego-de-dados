CC = gcc
CFLAGS = 
OBJS_P = juegodedados_p.o 
OBJS_H = juegodedados_h.o 

juegodedados_p: $(OBJS_P) 
	$(CC) $(CFLAGS) $(OBJS_P) -o $@

juegodedados_p.o: juegodedados_p.c funciones.h
	$(CC) $(CFLAGS) -c juegodedados_p.c funciones.h

juegodedados_h: $(OBJS_H) 
	$(CC) $(CFLAGS) $(OBJS_H) -o $@

juegodedados_h.o: juegodedados_h.c funciones.h
	$(CC) $(CFLAGS) -c juegodedados_h.c funciones.h

clean:
	/bin/rm *.o juegodedados_p tirada_* *.h.gch

CC = gcc
CFLAGS = 
OBJS = juegodedados_p.o 

juegodedados_p: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@

juegodedados_p.o: juegodedados_p.c 
	$(CC) $(CFLAGS) -c juegodedados_p.c

clean:
	/bin/rm *.o juegodedados_p

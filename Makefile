CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra
LIBS=-lm -lpthread -lcunit 
CODEFILES_RW=threads.c
CODEFILES_PH=threads.c
CODEFILES_PC=threads.c

rw: reader_writer/*
	cd reader_writer && $(CC) $(CFLAGS) -o ../rw -O3 $(CODEFILES_RW) main.c $(LIBS)
	
ph: philosophe/*
	cd philosophe && $(CC) $(CFLAGS) -o ../ph -O3 $(CODEFILES_PH) main.c $(LIBS)
	
pc: producer_consumer/*
	cd producer_consumer && $(CC) $(CFLAGS) -o ../pc -O3 $(CODEFILES_PC) main.c $(LIBS)

    
#timer: c/*
#	cd c && $(CC) $(CFLAGS) -o ../timer -O3 timer.c $(LIBS)

#debug: c/*
#	cd c && $(CC) $(CFLAGS) -o ../debug -g $(CODEFILES) main.c $(LIBS)

doc: 
	doxygen

clean:
	rm -f rw 
	rm -f ph
	rm -f pc
	rm -rf doc

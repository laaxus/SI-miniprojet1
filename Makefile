CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra
LIBS=-lm -lpthread -lcunit 
CODEFILES_RW=threads.c

rw: reader_writer/*
	cd reader_writer && $(CC) $(CFLAGS) -o ../rw -O3 $(CODEFILES_RW) main.c $(LIBS)

    
#timer: c/*
#	cd c && $(CC) $(CFLAGS) -o ../timer -O3 timer.c $(LIBS)

#debug: c/*
#	cd c && $(CC) $(CFLAGS) -o ../debug -g $(CODEFILES) main.c $(LIBS)

doc_rw: reader_writer/*
	doxygen

clean:
	rm -f rw 
	rm -rf doc_rw

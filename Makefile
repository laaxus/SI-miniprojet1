CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra 
LIBS=-lm -lpthread -lcunit 
CODEFILES_RW=threads.c
CODEFILES_PH=threads.c
CODEFILES_PC=threads.c
CODEFILES_TAS=threads.c
CODEFILES_TTS=threads.c

rw: reader_writer/*
	cd reader_writer && $(CC) $(CFLAGS) -o ../rw -O3 $(CODEFILES_RW) main.c $(LIBS)
	
ph: philosophe/*
	cd philosophe && $(CC) $(CFLAGS) -o ../ph -O3 $(CODEFILES_PH) main.c $(LIBS)
	
pc: producer_consumer/*
	cd producer_consumer && $(CC) $(CFLAGS) -o ../pc -O3 $(CODEFILES_PC) main.c $(LIBS)
	
ts: test_and_set/*
	cd test_and_set && $(CC) $(CFLAGS) -o ../ts -O3 $(CODEFILES_TAS) main.c $(LIBS)
	
tts: test_and_test_and_set/*
	cd test_and_test_and_set && $(CC) $(CFLAGS) -o ../tts -O3 $(CODEFILES_TTS) main.c $(LIBS)
    

debug_rw: reader_writer/*
	cd reader_writer && $(CC) $(CFLAGS) -o ../debug_rw -g $(CODEFILES_RW) main.c $(LIBS)
	
debug_ph: philosophe/*
	cd philosophe && $(CC) $(CFLAGS) -o ../debug_ph -g $(CODEFILES_PH) main.c $(LIBS)
	
debug_pc: producer_consumer/*
	cd producer_consumer && $(CC) $(CFLAGS) -o ../debug_pc -g $(CODEFILES_PC) main.c $(LIBS)
	
debug_ts: test_and_set/*
	cd test_and_set && $(CC) $(CFLAGS) -o ../debug_ts -g $(CODEFILES_TAS) main.c $(LIBS)
	
debug_tts: test_and_test_and_set/*
	cd test_and_test_and_set && $(CC) $(CFLAGS) -o ../debug_tts -g $(CODEFILES_TTS) main.c $(LIBS)
	
doc: 
	doxygen

clean:
	rm -f rw 
	rm -f ph
	rm -f pc
	rm -f ts
	rm -f tts
	rm -f debug_rw 
	rm -f debug_ph
	rm -f debug_pc
	rm -f debug_ts
	rm -f debug_tts
	rm -rf doc

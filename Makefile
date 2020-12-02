CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra 
LIBS=-lm -lpthread  
CODEFILES_RW=threads.c
CODEFILES_PH=threads.c
CODEFILES_PC=threads.c
CODEFILES_TS=threads.c
CODEFILES_TTS=threads.c mutex_sema.c
CODEFILES_RW2=threads.c mutex_sema.c
CODEFILES_PH2=threads.c mutex_sema.c
CODEFILES_PC2=threads.c mutex_sema.c
CODEFILES_RW3=threads.c mutex_sema.c
CODEFILES_PH3=threads.c mutex_sema.c
CODEFILES_PC3=threads.c mutex_sema.c

rw: reader_writer/*
	cd reader_writer && $(CC) $(CFLAGS) -o ../rw -O3 $(CODEFILES_RW) main.c $(LIBS)
	
ph: philosophe/*
	cd philosophe && $(CC) $(CFLAGS) -o ../ph -O3 $(CODEFILES_PH) main.c $(LIBS)
	
pc: producer_consumer/*
	cd producer_consumer && $(CC) $(CFLAGS) -o ../pc -O3 $(CODEFILES_PC) main.c $(LIBS)
	
ts: test_and_set/*
	cd test_and_set && $(CC) $(CFLAGS) -o ../ts -O3 $(CODEFILES_TS) main.c $(LIBS)
	
tts: test_and_test_and_set/*
	cd test_and_test_and_set && $(CC) $(CFLAGS) -o ../tts -O3 $(CODEFILES_TTS) main.c $(LIBS)
	
rw2: reader_writer_tts/*
	cd reader_writer_tts && $(CC) $(CFLAGS) -o ../rw2 -O3 $(CODEFILES_RW2) main.c $(LIBS)
	
ph2: philosophe_tts/*
	cd philosophe_tts && $(CC) $(CFLAGS) -o ../ph2 -O3 $(CODEFILES_PH2) main.c $(LIBS)
	
pc2: producer_consumer_tts/*
	cd producer_consumer_tts && $(CC) $(CFLAGS) -o ../pc2 -O3 $(CODEFILES_PC2) main.c $(LIBS)
	
rw3: reader_writer_ts/*
	cd reader_writer_tts && $(CC) $(CFLAGS) -o ../rw3 -O3 $(CODEFILES_RW3) main.c $(LIBS)
	
ph3: philosophe_ts/*
	cd philosophe_tts && $(CC) $(CFLAGS) -o ../ph3 -O3 $(CODEFILES_PH3) main.c $(LIBS)
	
pc3: producer_consumer_ts/*
	cd producer_consumer_tts && $(CC) $(CFLAGS) -o ../pc3 -O3 $(CODEFILES_PC3) main.c $(LIBS)

test:
	./script.sh

debug_rw: reader_writer/*
	cd reader_writer && $(CC) $(CFLAGS) -o ../debug_rw -g $(CODEFILES_RW) main.c $(LIBS)
	
debug_ph: philosophe/*
	cd philosophe && $(CC) $(CFLAGS) -o ../debug_ph -g $(CODEFILES_PH) main.c $(LIBS)
	
debug_pc: producer_consumer/*
	cd producer_consumer && $(CC) $(CFLAGS) -o ../debug_pc -g $(CODEFILES_PC) main.c $(LIBS)
	
debug_ts: test_and_set/*
	cd test_and_set && $(CC) $(CFLAGS) -o ../debug_ts -g $(CODEFILES_TS) main.c $(LIBS)
	
debug_tts: test_and_test_and_set/*
	cd test_and_test_and_set && $(CC) $(CFLAGS) -o ../debug_tts -g $(CODEFILES_TTS) main.c $(LIBS)
	
debug_rw2: reader_writer_tts/*
	cd reader_writer_tts && $(CC) $(CFLAGS) -o ../debug_rw2 -g $(CODEFILES_RW2) main.c $(LIBS)
	
debug_ph2: philosophe_tts/*
	cd philosophe_tts && $(CC) $(CFLAGS) -o ../debug_ph2 -g $(CODEFILES_PH2) main.c $(LIBS)
	
debug_pc2: producer_consumer_tts/*
	cd producer_consumer_tts && $(CC) $(CFLAGS) -o ../debug_pc2 -g $(CODEFILES_PC2) main.c $(LIBS)
	
debug_rw3: reader_writer_ts/*
	cd reader_writer_ts && $(CC) $(CFLAGS) -o ../debug_rw3 -g $(CODEFILES_RW3) main.c $(LIBS)
	
debug_ph3: philosophe_ts/*
	cd philosophe_ts && $(CC) $(CFLAGS) -o ../debug_ph3 -g $(CODEFILES_PH3) main.c $(LIBS)
	
debug_pc3: producer_consumer_ts/*
	cd producer_consumer_ts && $(CC) $(CFLAGS) -o ../debug_pc3 -g $(CODEFILES_PC3) main.c $(LIBS)
	
doc: 
	doxygen

clean:
	rm -f rw 
	rm -f ph
	rm -f pc
	rm -f ts
	rm -f tts
	rm -f rw2 
	rm -f ph2
	rm -f pc2
	rm -f rw3 
	rm -f ph3
	rm -f pc3
	rm -f debug_rw 
	rm -f debug_ph
	rm -f debug_pc
	rm -f debug_ts
	rm -f debug_tts
	rm -f debug_rw2 
	rm -f debug_ph2
	rm -f debug_pc2
	rm -f debug_rw3 
	rm -f debug_ph3
	rm -f debug_pc3
	rm -rf doc

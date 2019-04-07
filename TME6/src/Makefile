CC=gcc
CFLAGS=-W -Wall
LDFLAGS= -lm

all: exercice1.exe exercice2.exe exercice3.exe
	
exercice1.exe: exercice1.o cle.h exercice1.h
	$(CC) -o $@ $^ $(LDFLAGS)
	
exercice2.exe: exercice2.o cle.h exercice2.h
	$(CC) -o $@ $^ $(LDFLAGS)

exercice3.exe: exercice3.o
	$(CC) -o $@ $^ $(LDFLAGS)	
		
exercice1.o: exercice1.c
	$(CC) -o $@ -c $< $(CFLAGS)
			
exercice2.o: exercice2.c 
	$(CC) -o $@ -c $< $(CFLAGS)
	
exercice3.o: exercice3.c 
	$(CC) -o $@ -c $< $(CFLAGS)


		
clean:
	rm -rf *.o exercice1.exe exercice2.exe exercice3.exe

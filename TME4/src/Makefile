CC=gcc
CFLAGS=-W -Wall
LDFLAGS=

all: exercice2.exe
	
exercice2.exe: exercice2.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
		
exercice2.o: exercice2.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
		
clean:
	rm -rf *.o exercice2.exe


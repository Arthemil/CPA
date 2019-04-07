CC=gcc
CFLAGS=
LDFLAGS=

all: exercice1.exe exercice2.exe
	
exercice1.exe: exercice1.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
exercice2.exe: exercice2.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
		
exercice1.o: exercice1.c
	$(CC) -o $@ -c $< $(CFLAGS)
			
exercice2.o: exercice2.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
		
clean:
	rm -rf *.o  exercice1.exe exercice2.exe


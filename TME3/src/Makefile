CC=gcc
CFLAGS=-W -Wall
LDFLAGS=

all: exercice2.exe exercice4.exe exercice5.exe exercice6.exe exercice7_1.exe exercice7_2.exe exercice7_3.exe exercice8.exe exercice9.exe
	
exercice2.exe: exercice2.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
exercice4.exe: exercice4.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
exercice5.exe: exercice5.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
exercice6.exe: exercice6.o
	$(CC) -o $@ $^ $(LDFLAGS)

exercice7_1.exe: exercice7_1.o
	$(CC) -o $@ $^ $(LDFLAGS)

exercice7_2.exe: exercice7_2.o
	$(CC) -o $@ $^ $(LDFLAGS)

exercice7_3.exe: exercice7_3.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
exercice8.exe:  exercice8.o
	$(CC) -o $@ $^ $(LDFLAGS)

exercice9.exe:  exercice9.o
	$(CC) -o $@ $^ $(LDFLAGS)
		
exercice2.o: exercice2.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
exercice4.o: exercice4.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
exercice5.o: exercice5.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
exercice6.o: exercice6.c
	$(CC) -o $@ -c $< $(CFLAGS)

exercice7_1.o: exercice7_1.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
exercice7_2.o: exercice7_2.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
exercice7_3.o: exercice7_3.c
	$(CC) -o $@ -c $< $(CFLAGS)

exercice8.o:  exercice8.c
	$(CC) -o $@ -c $< $(CFLAGS)

exercice9.o:  exercice9.c
	$(CC) -o $@ -c $< $(CFLAGS)
		
clean:
	rm -rf *.o exercice2.exe exercice4.exe exercice5.exe exercice6.exe exercice7_1.exe exercice7_2.exe exercice7_3.exe exercice8.exe exercice9.exe


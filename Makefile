OBJ = Caesar.o \
			Playfair.o \
			Vigenere.o \
			RowTransposition.o \
			Railfence.o

all:	cipher

cipher:	cipher.o $(OBJ)
	g++ cipher.o $(OBJ) -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp

Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
	g++ -g -c -std=c++11 Playfair.cpp

Caesar.o:	Caesar.cpp Caesar.h CipherInterface.h
	g++ -g -c -std=c++11 Caesar.cpp

Railfence.o:	Railfence.cpp Railfence.h CipherInterface.h
	g++ -g -c -std=c++11 Railfence.cpp

Vigenere.o:	Vigenere.cpp Vigenere.h CipherInterface.h
	g++ -g -c Vigenere.cpp

RowTransposition.o:	RowTransposition.cpp RowTransposition.h
	g++ -g -c RowTransposition.cpp


clean:
	rm -rf *.o *.h.gch cipher

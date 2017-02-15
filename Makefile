all:	cipher

cipher:	cipher.o Caesar.o Playfair.o
	g++ cipher.o Caesar.o Playfair.o -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp

Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
	g++ -g -c -std=c++11 Playfair.cpp

Caesar.o:	Caesar.cpp Caesar.h CipherInterface.h
	g++ -g -c -std=c++11 Caesar.cpp

#Railfence.o:	Railfence.cpp Railfence.h CipherInterface.h
#	g++ -g -c Railfence.cpp

#Vigenre.o:	Vigenre.cpp Vigenre.h CipherInterface.h
#		g++ -g -c Vigenre.cpp

# Uncomment this code once you add the appropriate files
#RowTransposition.o:	RowTransposition.cpp RowTransposition.h
#	g++ -g -c RowTransposition.cpp


clean:
	rm -rf *.o cipher

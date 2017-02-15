#ifndef VIGNERE_H
#define VIGNERE_H

#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include <ctype.h>
#include "CipherInterface.h"

using namespace std;


class Vigenere: public CipherInterface
{
	public:
    Vigenere() { }
    Vigenere(bool debug) : _debug(debug) { }
    ~Vigenere() { }
		virtual bool setKey(const string&);
		virtual string encrypt(const string&);
		virtual string decrypt(const string&);


	protected:
    bool _debug;
    string _key;

};

#endif

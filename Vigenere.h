#ifndef VIGNERE_H
#define VIGNERE_H

#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include <ctype.h>
#include <iostream>
#include "CipherInterface.h"

using namespace std;


class Vigenere: public CipherInterface
{
	public:
		// Default Constructor
    Vigenere() { }

		// Constructor used for debugging purposes
		// Will print important information at each step of cipher
		// @param {bool} debug
    Vigenere(bool debug) : _debug(debug) { }

		// Destructor
    ~Vigenere() { }

		// Will set the key for the cipher
		// @param {const string&}
		// @return {bool} will return true if key is in valid format
		//	false otherwise.  Valid format is any alpha characters
		virtual bool setKey(const string&);

		// Encrypt the plaintext
		// @param {const string&}
		// @return {string} will return the cipher_text
		virtual string encrypt(const string&);

		// Decrypt the cipher text
		// @param {const string&}
		// @return {string} will return the plain text
		virtual string decrypt(const string&);


	protected:

		// Used for debugging purposes
    bool _debug;

		// The key is stored
    string _key;

};

#endif

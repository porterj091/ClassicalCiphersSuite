#ifndef CAESAR_H
#define CAESAR_H

#include <stdexcept>
#include <iostream>
#include <ctype.h>
#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include "CipherInterface.h"

using namespace std;


class Caesar: public CipherInterface
{
	public:
		// Default Constructor
    Caesar() { }

		// Destructor
    ~Caesar() { }

		// Will set the key for the cipher
		// @param {const string&}
		// @return {bool} will return true if key is in valid format
		//	false otherwise.  Valid format is numeric characters
		virtual bool setKey(const string&);

		// Encrypt the plaintext
		// @param {const string&}
		// @return {string} will return the cipher_text
		virtual string encrypt(const string&);

		// Decrypt the cipher text
		// @param {const string&}
		// @return {string} will return the plain text
		virtual string decrypt(const string&);

  private:

		// Will rotate the character based on the key
		// @param{const string&} cipher or plain text
		// @param {bool} true for encrypt false for decrypt
		// @return {string} the either plain or cipher text
    string rotateText(const string&, bool);

	protected:

		// The key for cipher
    int _key;

};

#endif

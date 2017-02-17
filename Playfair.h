#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <utility>
#include <cstring>

#include "CipherInterface.h"

using namespace std;

class Playfair: public CipherInterface
{
	public:
		// Default Constructor
    Playfair() { }

		// Constructor used for debugging purposes
		// Will print important information at each step of cipher
		// @param {bool} debug
    Playfair(bool debug) : _debug(debug) { }

		// Destructor
    ~Playfair() { }

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


  private:
		// Will create the matrix from the key to use in cipher
		// Must be called after key has been set not before
		// @return {vector<vector<string> >} to store in _matrix
    vector<vector<string> > createMatrix();

		// Creates the two pair groups the cipher uses to decrypt and encrypt
		// @param {const string&} Either plaintext or cipher text
		// @return {vector<string>} A vector with the two pair groups
    vector<string> createGroups(const string&);

		// Find's the location of the character in the matrix
		// @param {string&} group of two characters
		// @param {bool} which part of group true for left false for right
		// @return {pair<int, int>} contains the cordinate location in the matrix
		// will be -1 -1 if could not find
    pair<int, int> findLocation(string&, bool);

		// Used to print the key matrix for debugging
		void printMatrix();

		// If letters are in same Column moveRow over
		// @param {string&} either cipher or plaintext to add to
		// @param {pair<int,int>} first cordinate
		// @param {pair<int,int>} second cordinate
		// @param {bool} true for encrypt false for decrypt
    void moveRow(string&, pair<int,int>&, pair<int,int>&, bool);

		// If letters are in same Row move column down or up
		// @param {string&} either cipher or plaintext to add to
		// @param {pair<int,int>} first cordinate
		// @param {pair<int,int>} second cordinate
		// @param {bool} true for encrypt false for decrypt
    void moveColumn(string&, pair<int,int>&, pair<int,int>&, bool);

		// If letters are in different column and row encrypt normally
		// @param {string&} either cipher or plaintext to add to
		// @param {pair<int,int>} first cordinate
		// @param {pair<int,int>} second cordinate
		// @param {bool} true for encrypt false for decrypt
    void moveNormal(string&, pair<int,int>&, pair<int,int>&, bool);

	protected:
		// The key for the cipher
    string _key;

		// Encrypt and Decrypt matrix
    vector<vector<string> > _matrix;

		// Used for debuggin
    bool _debug;

};

#endif

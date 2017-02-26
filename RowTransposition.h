#ifndef ROWTRANSPOSITION_H
#define ROWTRANSPOSITION_H

#include <string> /* For C++ strings */
#include <stdexcept>
#include <iostream>
#include <vector>
#include <ctype.h>

#include "CipherInterface.h"

using namespace std;

class RowTransposition : public CipherInterface
{
	public:

    // Default Constructor
		RowTransposition(){ }

    /** Constructor used for degbugging purposes
    * @param {bool} true for debug info false otherwise
    */
    RowTransposition(bool debug) : _debug(debug) { }

    // Destructor
    ~RowTransposition(){ }

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
		vector<vector<string> > makeMatrixEncrypt(const string&);
		vector<vector<string> > makeMatrixDecrypt(const string&);

	protected:
    string _key;
    bool _debug;

};

#endif

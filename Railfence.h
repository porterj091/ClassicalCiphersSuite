#ifndef RAILFENCE_H
#define RAILFENCE_H

#include <string> /* For C++ strings */
#include <stdexcept>
#include <iostream>
#include <vector>
#include <ctype.h>

#include "CipherInterface.h"

using namespace std;

class Railfence : public CipherInterface
{
	public:

    // Default Constructor
		Railfence(){ }

    /** Constructor used for degbugging purposes
    * @param {bool} true for debug info false otherwise
    */
    Railfence(bool debug) : _debug(debug) { }

    // Destructor
    ~Railfence(){ }
		virtual bool setKey(const string&);
		virtual string encrypt(const string&);
		virtual string decrypt(const string&);

  private:

	protected:
    int _key;
    bool _debug;

};

#endif

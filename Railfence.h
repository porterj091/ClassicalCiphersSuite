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

		Railfence(){ }
    Railfence(bool debug) : _debug(debug) { }
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

#ifndef CAESAR_H
#define CAESAR_H

#include "CipherInterface.h"

using namespace std;


class Caesar: public CipherInterface
{
	public:
    Caesar() { }
    ~Caesar() { }
		virtual bool setKey(const string&);
		virtual string encrypt(const string&);
		virtual string decrypt(const string&);

  private:
    string rotateText(const string&, bool);

	protected:
    int _key;

};

#endif

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
    Playfair() { }
    Playfair(bool debug) : _debug(debug) { }
    ~Playfair() { }
		virtual bool setKey(const string&);
		virtual string encrypt(const string&);
		virtual string decrypt(const string&);
		void printMatrix();

  private:
    vector<vector<string> > createMatrix();
    vector<string> createGroups(const string&);
    pair<int, int> findLocation(string&, bool);
    void moveRow(string&, pair<int,int>&, pair<int,int>&, bool);
    void moveColumn(string&, pair<int,int>&, pair<int,int>&, bool);
    void moveNormal(string&, pair<int,int>&, pair<int,int>&, bool);

	protected:
    string _key;
    vector<vector<string> > _matrix;
    bool _debug;

};

#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>

#include "CipherInterface.h"
#include "Caesar.h"
#include "Playfair.h"
#include "Vigenere.h"
#include "Railfence.h"
#include "RowTransposition.h"


using namespace std;

void usage()
{
  printf("%s\n",
      "USAGE: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>");
  printf("%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n",
      "CIPHERS",
      "PLF: Playfair",
      "RFC: Railfence",
      "RTS: Row Transposition",
      "VIG: Vigenere",
      "CES: Caesar");
}

int main(const int argc, const char *argv[])
{
  // Make sure user has submitted correct num of arguments
  if (argc != 6)
  {
    printf("%s\n", "Incorrect number of arguments!");
    usage();
    return 1;
  }

  CipherInterface *cipher;

  string CIPHER(argv[1]);
  string key(argv[2]);

  // Find which cipher the user wants
  if (CIPHER == "RTS")
  {
    cipher = new RowTransposition();
    if(!cipher->setKey(key))
      return 1;
  }
  else if (CIPHER == "PLF")
  {
    cipher = new Playfair();
    if(!cipher->setKey(key))
      return 1;
  }
  else if (CIPHER == "RFC")
  {
    cipher = new Railfence();
    if(!cipher->setKey(key))
      return 1;
  }
  else if (CIPHER == "CES")
  {
    cipher = new Caesar();
    if(!cipher->setKey(key))
      return 1;
  }
  else if (CIPHER == "VIG")
  {
    cipher = new Vigenere();
    if(!cipher->setKey(key))
      return 1;
  }
  else
  {
    printf("%s\n", "Incorrect Cipher NAME");
    usage();
    return 1;
  }

  string inFile(argv[4]);
  string outFile(argv[5]);

  ifstream fIn(inFile, ios_base::in);
  ofstream fOut(outFile, ios_base::out);

  if(!fIn)
  {
    cerr << "Error: Could not open file - " << inFile << endl;
    return 1;
  }

  if(!fOut)
  {
    cerr << "Error: Could not open file - " << outFile << endl;
    return 1;
  }

  string cipher_input;

  while(fIn.good())
  {
    string stuff;
    fIn >> stuff;

    cipher_input += stuff;
  }

  if(strncmp(argv[3], "ENC", 4) == 0)
  {
    fOut << cipher->encrypt(cipher_input) << endl;
  }
  else if(strncmp(argv[3], "DEC", 4) == 0)
  {
    fOut << cipher->decrypt(cipher_input) << endl;
  }
  else
  {
    printf("%s\n", "Incorrect method of using the cipher!!");
    usage();
    return 1;
  }

  return 0;
}

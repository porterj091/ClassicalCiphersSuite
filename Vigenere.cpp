#include "Vigenere.h"

bool Vigenere::setKey(const string& key)
{
  _key = "";
  // Make sure our key does not have any non alpha characters in it
  for(unsigned int i = 0; i < key.length(); ++i)
  {
    if(isalpha(key[i]) == 0)
      return false;
    else
      _key += toupper(key[i]);
  }

  return true;
}

string Vigenere::encrypt(const string& plaintext)
{
  string cipher_text = "";

  int key_index = 0;
  for(unsigned int i = 0; i < plaintext.length(); ++i)
  {
    // If its an alpha character add to cipher text then continue
    if(isalpha(plaintext[i]) == 0)
    {
      cipher_text += plaintext[i];
      continue;
    }

    // Make the characters uppercase to see results better
    char c = toupper(plaintext[i]);
    cipher_text += (c + _key[key_index]) % 26 + 'A';
    if(_debug)
    {
      cout << (c + _key[key_index]) % 26 + 'A' << endl;
    }
    key_index = (key_index + 1) % _key.length();

  }
  return cipher_text;
}

string Vigenere::decrypt(const string& ciphertext)
{
  string plain_text = "";
  int key_index = 0;
  for(unsigned int i = 0; i < ciphertext.length(); ++i)
  {
    // If its an alpha character add to cipher text then continue
    if(isalpha(ciphertext[i]) == 0)
    {
      plain_text += ciphertext[i];
      continue;
    }

    // Make the characters uppercase to see results better
    char c = toupper(ciphertext[i]);
    plain_text += (c - _key[key_index]  + 26) % 26 + 'A';

    if(_debug)
    {
      cout << (c - _key[key_index] + 26) % 26 + 'A' << endl;
    }
    key_index = (key_index + 1) % _key.length();

  }
  return plain_text;
}

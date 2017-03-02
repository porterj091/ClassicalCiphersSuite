#include "Railfence.h"

bool Railfence::setKey(const string & key)
{
  try
  {
    _key = stoi(key);
    return true;
  }
  catch(const invalid_argument& e)
  {
    cout << "Has to be an INT number!!" << endl;
    return false;
  }
  catch(const out_of_range& e)
  {
    cout << "Key out of INT range make it samller"<< endl;
    return false;
  }
}

string Railfence::encrypt(const string& plaintext)
{
  // Create _key many vectors to hold the cipher text
  vector<vector<string> > text(_key);

  int curr = 0;
  unsigned int size = plaintext.length();
  string s;

  // Create the rows to encrypt
  for(unsigned int i = 0; i < size; ++i)
  {
    // Ignore any whitespace
    if(isspace(plaintext[i]) == 0 || isalpha(plaintext[i]) == 0)
    {
      // Add to the vector
      s = "";
      s += toupper(plaintext[i]);
      text[curr].emplace_back(s);
      curr = (curr + 1) % _key;
    }
    else
    {
      if(_debug)
      {
        cout << "Non char: " << plaintext[i] << endl;
      }
    }
  }

  // Move the rows into a string to be returned
  s = "";
  for(int i = 0; i < _key; ++i)
  {
    for(unsigned int j = 0; j < text[i].size(); ++j)
    {
      s += text[i][j];
      if(_debug)
      {
        cout << " " << text[i][j];
      }
    }

    if(_debug)
    {
      cout << endl;
    }

  }

  return s;
}

string Railfence::decrypt(const string& ciphertext)
{
  // Create _key many vectors to hold the plaintext
  vector<vector<string> > text(_key);
  unsigned int size = ciphertext.length();

  unsigned int leftOver = size % _key;

  int curr = 0, next = (size / 3), vecRow = 0;
  string s;
  for(unsigned int i = 0; i < size; ++i)
  {
    s = "";
    s += ciphertext[i];

    if(curr < next)
    {
      text[vecRow].emplace_back(s);
      curr++;
      if(_debug)
      {
        cout << " " << s;
      }
    }
    else
    {
      if(leftOver != 0)
      {
        text[vecRow++].emplace_back(s);
        leftOver--;
        curr = 0;
      }
      else
      {
        text[++vecRow].emplace_back(s);
        curr = 1;
      }

      if(_debug)
      {
        cout << endl;
      }
    }
  }

  s = "";

  int row = 0, col = 0;
  for(unsigned int i = 0; i < size; ++i)
  {
    s += text[row][col];

    if(++row == _key)
    {
      row = 0;
      col++;
    }
  }

  if(_debug)
  {
    cout << endl;
  }


  return s;
}

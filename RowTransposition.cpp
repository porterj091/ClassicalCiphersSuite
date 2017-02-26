#include "RowTransposition.h"

bool RowTransposition::setKey(const string& key)
{
  unsigned int size = key.length();
  _key = "";
  for(unsigned int i = 0; i < size; ++i)
  {
    if(isdigit(key[i]))
    {
      _key += key[i];
    }
    else
    {
      return false;
    }
  }

  if(_debug)
  {
    cout << "The key: " << _key << endl;
  }
  return true;
}

vector<vector<string> > RowTransposition::makeMatrixEncrypt(const string& text)
{
  string t = "";

  unsigned int tempLen = text.size();

  // Get rid of the spaces and non alpha characters
  for(unsigned int i = 0; i < tempLen; ++i)
  {
    if(isalpha(text[i]))
    {
      t += text[i];
    }
  }
  unsigned int size = t.size();
  int sizeMatrix = size / _key.length(), extra = size % _key.length();

  if(extra != 0)
  {
    sizeMatrix++;
  }

  vector<vector<string> > matrix(sizeMatrix);

  string s = "";

  unsigned int curr = 0, len = _key.length(), row = 0;

  for(unsigned int i = 0; i < size; ++i)
  {
    if(isalpha(t[i]))
    {
      s = "";
      s += toupper(t[i]);

      if(curr++ < len)
      {
        matrix[row].emplace_back(s);
      }
      else
      {
        matrix[++row].emplace_back(s);
        curr = 1;
      }
    }
  }

  // Fill the rest of the matrix with filler values
  while (matrix[row].size() < len)
  {
    matrix[row].emplace_back("x");

    if(_debug)
    {
      cout << "Adding extra On Row: " << row << endl;
    }
  }

  if(_debug)
  {
    for(unsigned int i = 0; i < matrix.size(); ++i)
    {
      cout << "{";
      for(unsigned int j = 0; j < matrix[i].size(); ++j)
      {
        cout << " " << matrix[i][j];
      }
      cout << " }" << endl;
    }
  }

  return matrix;
}

vector<vector<string> > RowTransposition::makeMatrixDecrypt(const string& text)
{
  vector<vector<string> > matrix(text.size() / _key.length(), vector<string>(_key.length(), "0"));

  unsigned int len = text.length(), rowSize = matrix.size(), currRow = 0, currCol = 0;



  for(unsigned int i = 0; i < len; ++i)
  {
    matrix[currRow++][currCol] = text[i];

    if(currRow == rowSize)
    {
      currCol++;
      currRow = 0;
    }
  }

  if(_debug)
  {
    for(unsigned int i = 0; i < matrix.size(); ++i)
    {
      cout << "{";
      for(unsigned int j = 0; j < matrix[i].size(); ++j)
      {
        cout << " " << matrix[i][j];
      }
      cout << " }" << endl;
    }
  }

  return matrix;
}


string RowTransposition::encrypt(const string& plaintext)
{
  vector<vector<string> > matrix = makeMatrixEncrypt(plaintext);

  unsigned int len = _key.length(), size = matrix.size();
  string s = "";
  for(unsigned int i = 0; i < len; ++i)
  {
    int currCol = (_key[i] - '0') - 1;

    for(unsigned int j = 0; j < size; ++j)
    {
      s += matrix[j][currCol];
    }
  }

  return s;
}

string RowTransposition::decrypt(const string& ciphertext)
{
  vector<vector<string> > matrix = makeMatrixDecrypt(ciphertext);

  unsigned int len = _key.length(), size = matrix.size(), currRow = 0;

  string s = "";
  while(currRow < size)
  {
    for(unsigned int j = 0; j < len; ++j)
    {
      char locate = (j+1) + '0';
      size_t found = _key.find(locate);

      if(_debug)
      {
        cout << "CurrRow: " << currRow << " Found at: " << found << endl;
      }

      s += matrix[currRow][found];

    }

    currRow++;
  }

  return s;
}

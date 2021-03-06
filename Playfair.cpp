#include "Playfair.h"

// Set the key for the cipher
bool Playfair::setKey(const string& key)
{
  int a[256] = {0};
  string newKey = "";

  // Make sure the key is all alpha characters and only repeated once.
  for(unsigned int i = 0; i < key.length(); ++i)
  {
    if(isalpha(key[i]) != 0)
    {
      char curr = tolower(key[i]);

      // I and J are treated the same way in playfair
      if(curr == 'j')
        a[105]++;
      else
        a[int(curr)]++;

      if(a[int(curr)] == 1)
      {
        newKey += curr;
      }
    }
    else
    {
      cout << "Can't accept any Nonalpha characters for key!" << endl;
      return false;
    }
  }

  _key = newKey;

  if(_debug)
    cout << "Creating the martix!\nWith key: " << _key << endl;
  // Need to set the key before calling createMatrix since we need the key.
  _matrix = createMatrix();

  if(_debug)
    printMatrix();

  return true;
}

vector<vector<string> > Playfair::createMatrix()
{
  // Init our container to hold matrix
  vector<vector<string> > M(5, vector<string>(5, ""));

  // Will use to include the other characters
  int a[256];

  for(int i = 0; i < 256; ++i)
    a[i] = 0;

  // Row and column which we should insert key value
  unsigned int row = 0;
  unsigned int col = 0;
  for(unsigned int i = 0; i < _key.length(); ++i)
  {
    if(col > 4)
    {
      row++;
      col = 0;
    }

    // I and j are treated as the same character
    if(_key[i] == 'j' || _key[i] == 'i')
    {
      a[105]++;
      M[row][col++] = 'i';
    }
    else
    {
      if(_debug)
        cout << "Storing this key: " << _key[i] << " at index: " << int(_key[i]) << endl;

      a[int(_key[i])]++;
      M[row][col++] = _key[i];
    }
  }

  // Check what character we have left to use
  for(unsigned int j = 97; j < 123; ++j)
  {
    if(a[j] == 0 && j != 106)
    {
      if(col > 4)
      {
        row++;
        col = 0;
      }

      if(_debug)
      {
        cout << "Working on column: " << col << " and row: " << row  << " with letter: " << static_cast<char>(j) << endl;
      }

      M[row][col++] = char(j);
    }
  }

  return M;

}

// For debugging purposes to make sure the martix is being created successfully
void Playfair::printMatrix()
{
  cout << "Starting to print the matrix" << endl;
  for(int i = 0; i < 5; ++i)
  {
    cout << "{";
    for(int j = 0; j < 4; ++j)
    {
      cout << _matrix[i][j] << ", ";
    }
    cout << _matrix[i][4] << "}" << endl;
  }
}

// Will encrypt the plaintext
string Playfair::encrypt(const string& plaintext)
{
  string cipher_text = "";
  vector<string> groups = createGroups(plaintext);
  pair<int,int> location1;
  pair<int,int> location2;

  for(vector<string>::iterator it = groups.begin(); it != groups.end(); ++it)
  {
    if(_debug)
    {
      cout << endl << (*it) << " " << (*it)[0]  << " " << (*it)[1] << endl;
    }

    location1 = findLocation((*it), true);
    location2 = findLocation((*it), false);

    if(location1.first == -1 || location2.first == -1)
    {
      cout << "Something bad happened with finding in the matrix" << endl;
      exit(1);
    }

    if(location1.first == location2.first)
    {
      moveColumn(cipher_text, location1, location2, true);
    }
    else if(location1.second == location2.second)
    {
      moveRow(cipher_text, location1, location2, true);
    }
    else
    {
      moveNormal(cipher_text, location1, location2, true);
    }
  }

  return cipher_text;
}

// Will decrypt the ciphertext
string Playfair::decrypt(const string& ciphertext)
{
  string plain_text = "";
  vector<string> groups = createGroups(ciphertext);
  pair<int,int> location1;
  pair<int,int> location2;

  for(vector<string>::iterator it = groups.begin(); it != groups.end(); ++it)
  {
    if(_debug)
    {
      cout << endl << (*it) << " " << (*it)[0]  << " " << (*it)[1] << endl;
    }

    location1 = findLocation((*it), true);
    location2 = findLocation((*it), false);

    if(location1.first == -1 || location2.first == -1)
    {
      cout << "Something bad happened with finding in the matrix" << endl;
      exit(1);
    }

    if(location1.first == location2.first)
    {
      moveColumn(plain_text, location1, location2, false);
    }
    else if(location1.second == location2.second)
    {
      moveRow(plain_text, location1, location2, false);
    }
    else
    {
      moveNormal(plain_text, location1, location2, false);
    }
  }

  return plain_text;
}

// Will create the two pair groups and place them into a vector
// this will be used by both the encrypt and decrypt
// @param {string}
// @return {vector<string>}
vector<string> Playfair::createGroups(const string& text)
{
  string cipher_text = "";

  vector<string> groups;

  string s = "";
  for(unsigned int i = 0; i < text.length(); ++i)
  {
    if(isalpha(text[i]))
      s += text[i];
  }

  unsigned int size = s.length(), numChars = 0;
  for(unsigned int i = 0; i < size - 1; i+=2)
  {
      string currGroup = "";
      if(s[i] == s[i + 1])
      {
        currGroup += tolower(s[i]);
        currGroup += 'x';
        numChars++;
        groups.emplace_back(currGroup);
        i--;
      }
      else
      {
        currGroup += tolower(s[i]);
        currGroup += tolower(s[i + 1]);
        numChars += 2;
        groups.emplace_back(currGroup);
      }
  }

  if(_debug)
  {
    cout << "numChars: " << numChars << endl;
  }

  if(numChars < size)
  {
    string group = "";
    group += tolower(s[size-1]);
    group += 'x';
    groups.emplace_back(group);
  }

  if(_debug)
  {
    for(vector<string>::iterator it = groups.begin(); it != groups.end(); ++it)
    {
      cout << *it << ",";
    }
  }

  return groups;
}

pair<int, int> Playfair::findLocation(string& c, bool left)
{
  int index = (left) ? 0 : 1;
  if(c[index] == 'j')
    c[index] = 'i';

  for(int i = 0; i < 5; ++i)
  {
    for(int j = 0; j < 5; ++j)
    {
      string s = "";
      s += c[index];
      if(_matrix[i][j] == s)
      {
        if(_debug)
        {
          cout << "Found: " << s << " at: " << i << "," << j << endl;
        }
        return pair<int,int>(i, j);
      }
    }
  }

  return pair<int,int>(-1, -1);
}

void Playfair::moveNormal(string& text, pair<int,int>& first, pair<int,int>& second, bool direction)
{
  text += _matrix[first.first][second.second];
  text += _matrix[second.first][first.second];
}

void Playfair::moveRow(string& text, pair<int,int>& first, pair<int,int>& second, bool direction)
{
  int dir = (direction) ? 1 : -1;
  int row1 = (first.first + dir) % 5;
  int row2 = (second.first + dir) % 5;

  if(row1 < 0)
    row1 = 5 + row1;
  if(row2 < 0)
    row2 = 5 + row2;

  if(_debug)
  {
    cout << "Moving row1 to: " << row1 << endl;
    cout << "Moving row2 to: " << row2 << endl;
  }

  text += _matrix[row1][first.second];
  text += _matrix[row2][second.second];
}

void Playfair::moveColumn(string& text, pair<int,int>& first, pair<int,int>& second, bool direction)
{
  int dir = (direction) ? 1 : -1;
  int col1 = (first.second + dir) % 5;
  int col2 = (second.second + dir) % 5;

  if(col1 < 0)
    col1 = 5 + col1;
  if(col2 < 0)
    col2 = 5 + col2;

  if(_debug)
  {
    cout << "Moving col1 to: " << col1 << endl;
    cout << "Moving col2 to: " << col2 << endl;
  }
  text += _matrix[first.first][col1];
  text += _matrix[second.first][col2];
}

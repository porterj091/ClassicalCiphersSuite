#include "Caesar.h"
#include <stdexcept>
#include <iostream>
#include <ctype.h>
#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */

bool Caesar::setKey(const string& key)
{
  try
  {
    _key = stoi(key);
    _key %= 26;
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

string Caesar::rotateText(const string& text, bool direction)
{
  int dir = (direction) ? 1 : -1;
  string s = "";
  for(unsigned int i = 0; i < text.length(); ++i)
  {
    int num = text[i];
    num += (dir * _key);
    if(isalpha(text[i]) != 0)
    {
      if(isupper(text[i]) != 0)
      {
        if(num > 'Z')
          num -= 26;
        else if(num < 'A')
          num += 26;
      }
      else
      {
        if(num > 'z')
          num -= 26;
        else if (num < 'a')
          num += 26;
      }

      s += char(num);
    }
    else
    {
      s += text[i];
    }
  }

  return s;
}

string Caesar::encrypt(const string& plaintext)
{
  return rotateText(plaintext, true);
}

string Caesar::decrypt(const string& ciphertext)
{
  return rotateText(ciphertext, false);
}

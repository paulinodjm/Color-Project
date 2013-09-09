//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "zipstring.h"

bool ZIPSTRING::Read(ZIPSTREAM& stream)
{
  int size;
  char c;
  
  mStr.clear();
  
  size = stream.getSize();
  if (size < 0)
    return false;
    
  if (stream.seek(0) != 0)
    return false;  
  
  for (int i=0; i<size; i++)
  {
    if (stream.read(static_cast<void*>(&c), sizeof(char)) < 0)
    {
      mStr.clear();
      return false;
    }
    
    mStr.push_back(c);
  }
  return true;
}

const std::string& ZIPSTRING::Str() const
{
  return mStr;
}

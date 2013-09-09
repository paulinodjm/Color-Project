//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "zipstream.h"
#include <string>

class ZIPSTRING
{
public:

  bool Read(ZIPSTREAM& stream);
  const std::string& Str() const;

private:

  std::string mStr;
};

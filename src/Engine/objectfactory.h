//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "object.h"

class OBJECTFACTORY
{
public:

  virtual OBJECT* Create() const = 0;
};

template <typename T>
class TOBJECTFACTORY : public OBJECTFACTORY
{
public:

  OBJECT* Create() const
  { 
    return new T;
  }
};

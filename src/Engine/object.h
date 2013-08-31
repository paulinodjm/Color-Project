//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "contentmanager.h"

class LEVEL;

class OBJECT
{
public:

  virtual bool Load(CONTENTMANAGER& contentManager) = 0;
  virtual void Init(LEVEL& level) = 0;
};

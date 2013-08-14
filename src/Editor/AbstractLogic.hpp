//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

class AbstractLogic
{
public:

  virtual void init() = 0;

  virtual void update() = 0;
  
  virtual void draw() = 0;
  
  virtual void finalize() = 0;
};

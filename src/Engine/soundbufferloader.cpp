//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "soundbufferloader.h"

bool LOADER<SOUNDBUFFER>::Load(std::shared_ptr<SOUNDBUFFER>& res, const std::string& name)
{
  res = std::make_shared<SOUNDBUFFER>();
  if (res->loadFromFile(name))
  {
    std::cout << "SoundBuffer '" << name << "' loaded." << std::endl;
    return true;
  }
  else
  {
    res.reset();
    return false;
  }
}

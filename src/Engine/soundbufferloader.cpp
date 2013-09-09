//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "soundbufferloader.h"
#include "zipstream.h"

bool LOADER<SOUNDBUFFER>::Load(std::shared_ptr<SOUNDBUFFER>& res, const std::string& name, CONTENTMANAGER& contentManager)
{
  ZIPSTREAM zip;
  res = std::make_shared<SOUNDBUFFER>();
  if (zip.Open(name) && res->loadFromStream(zip))
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

//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "textureloader.h"

bool LOADER<TEXTURE>::Load(std::shared_ptr<TEXTURE>& res, const std::string& name, CONTENTMANAGER& contentManager)
{
  res = std::make_shared<TEXTURE>();
  if (res->loadFromFile(name))
  {
    std::cout << "Texture '" << name << "' loaded." << std::endl;
    return true;
  }
  else
  {
    res.reset();
    return false;
  }
}

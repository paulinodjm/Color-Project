//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "animationsloader.h"
#include <fstream>
#include <jsoncpp/json/json.h>

bool LOADER<ANIMATIONS>::Load(std::shared_ptr<ANIMATIONS>& res, const std::string& name)
{
  std::ifstream file(name);
  Json::Value root;
  Json::Reader reader;
  
  if (!file.is_open())
  {
    std::cout << "Failed to load animations '" << name << "' : unable to open file." << std::endl;
    return false;
  }
  if (!reader.parse(file, root))
  {
    std::cout << "Failed to load animations '" << name << "' : " << reader.getFormatedErrorMessages() << std::endl;
    return false;
  }
  
  res = std::make_shared<ANIMATIONS>();
  for (int i=0; i<root.size(); i++)
  {
    Json::Value anim = root[i];
    if ( res->find( anim["name"].asString() ) != res->end() )
    {
      std::cout << "Warning : '" << name << "->" << anim["name"].asString() << "' already exists." << std::endl;
      continue;
    }
    
    ANIMATION& newAnim = (*res)[ anim["name"].asString() ];
  }
  
  if (res->size() > 0)
  {
    std::cout << "Animations '" << name << "' loaded." << std::endl;
    return true;
  }
  else
  {
    std::cout << "Failed to load animation '" << name << "' : no valid animation in file." << std::endl;
    res.reset();
    return false;
  }
}

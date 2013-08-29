//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "animationsloader.h"
#include <fstream>
#include "contentmanager.h"

bool LOADER<ANIMATIONS>::Load(std::shared_ptr<ANIMATIONS>& res, const std::string& name, CONTENTMANAGER& contentManager)
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
      std::cout << "Warning : animation '" << name << "->" << anim["name"].asString() << "' already exists." << std::endl;
      continue;
    }
    
    // texture loading
    ANIMATION& newAnim = (*res)[ anim["name"].asString() ];
    if (!contentManager.Load(newAnim.Texture(), anim["texture"].asString()))
    {
      std::cout << "Failed to create animation '" << name << "->" << anim["name"].asString() << "' : texture not found." << std::endl;
      res->erase( res->find( anim["name"].asString() ) );
      continue;
    }
    
    newAnim.SetFirstFrame(
      sf::FloatRect(
        anim["rect"].get("left", 0).asDouble(),
        anim["rect"].get("top", 0).asDouble(),
        anim["rect"].get("width", 0).asDouble(),
        anim["rect"].get("height", 0).asDouble()
      )
    );
    newAnim.SetFrameCount( anim["frameCount"].asInt() );
    newAnim.SetOrigin(
      sf::Vector2f(
        anim["origin"].get("x", 0).asDouble(),
        anim["origin"].get("y", 0).asDouble()
      )
    );
    newAnim.SetFrameTime( sf::milliseconds( anim["frameTime"].asInt() ) );
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


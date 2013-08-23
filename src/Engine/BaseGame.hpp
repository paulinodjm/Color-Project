//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "BaseTypes.hpp"
#include "Tileset.hpp"
#include "Tilemap.hpp"

#include "staticsprite.h"
#include "contentmanager.h"

namespace e
{
  /**
  * Base class foreach game
  */
  class BaseGame
  {
  public:

    BaseGame(sf::RenderWindow& rendow);
        
        
    void addObjectFactory(const std::string& name, ObjectFactory& factory);
    
    Object* createObject(const std::string& name);
    
    bool loadTilemap(const std::string& filename, Tilemap& tilemap);
    
    bool loadObjects(const std::string& filename);
    
    
    //Level* getLevel();

  protected:

    /** process the game logic */
    bool update();
        
    
    bool loadResources();

  private:

    STATICSPRITE staticsprite;

    sf::RenderWindow&                     m_rendow;
    
    std::map<std::string, ObjectFactory*> m_objectFactory;
    
    CONTENTMANAGER  contentManager;
      
  protected:

    //Level*                                m_level;
  };
}


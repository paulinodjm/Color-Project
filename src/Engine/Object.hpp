//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "BaseTypes.hpp"
#include "Resources.hpp"

namespace e
{
  /**
  * Base class for each object in the game.
  */
  class Object
  {
  public:
    
    Object();
    
    Object(Resources& resources);

    Resources* getResources();
    
    void setResources(Resources& resources);
    
    const std::string& getName() const;
    
    void setName(const std::string& name);

  protected:

    virtual void init(Level& level) {}

    virtual void update(float deltaTime) {}

  private:

    Resources* m_resources;
    
    std::string m_name;
    
  friend class Game;
  friend class Level;
  };

  /**
  * Object factory
  */
  class ObjectFactory
  {
  public:

    virtual Object* create() = 0;
    
    Resources&  getResources();
    
  private:

    Resources m_resources;
  };//*/
}


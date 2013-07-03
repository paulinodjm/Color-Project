//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "BaseTypes.hpp"
#include "Tileset.hpp"
#include "TextureLoader.hpp"
#include "Tilemap.hpp"
#include "Drawable.hpp"
#include "Level.hpp"


class Game
{
public:

  Game();
  

  int mainLoop();
  
  
  void addObjectFactory(const std::string& name, ObjectFactory& factory);
  
  Object* createObject(const std::string& name);
  
  Tileset& getTileset();
  
  Tilemap& getTilemap();
  
  TextureLoader& getTextureLoader();
  
  
  bool loadTilemap(const std::string& filename);
  
  bool loadObjects(const std::string& filename);
  
  
  Level* getLevel();

protected:

  virtual void init() {}

  virtual bool update(float deltaTime) {return true;}

  virtual void finalize() {}
  
  
  bool loadResources();

private:

  sf::RenderWindow                      m_rendow;
  
  std::map<std::string, ObjectFactory*> m_objectFactory;
  
  Tileset                               m_tileset;
  
  Tilemap                               m_tilemap;
  
  TextureLoader                         m_textureLoader;
  
  Level*                                m_level;
};


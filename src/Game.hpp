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

class Game
{
public:

  int mainLoop();
  
  
  void addObjectFactory(const std::string& name, ObjectFactory& factory);
  
  Object* createObject(const std::string& name);
  
  Tileset& getTileset();
  
  Tilemap& getTilemap();

protected:

  virtual void init() {}

  virtual bool update(float deltaTime) {return true;}

  virtual void finalize() {}
  
  
  bool loadResources();
  
  void performCollisions();

private:

  sf::RenderWindow      m_rendow;

  std::set<Object*>     m_objects;

  std::set<Drawable*>   m_drawables;
  
  std::vector<Solid*>   m_solids;
  
  std::map<std::string, ObjectFactory*> m_objectFactory;
  
  Tileset               m_tileset;
  
  Tilemap               m_tilemap;
  
  TextureLoader         m_textureLoader;
};

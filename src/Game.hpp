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


class Game
{
public:

  int mainLoop();
  
  
  void addObjectFactory(const std::string& name, ObjectFactory& factory);
  
  Object* createObject(const std::string& name);
  
  void addObject(Object* object);
  
  Tileset& getTileset();
  
  Tilemap& getTilemap();
  
  TextureLoader& getTextureLoader();
  
  
  /** return the first Object identified by this name */
  Object* getObject(const std::string& name);
  
  /** return all the objects identified by this name */
  std::vector<Object*> getObjects(const std::string& name);
  
  
  bool loadTilemap(const std::string& filename);
  
  bool loadObjects(const std::string& filename);
  
  void deleteObjects();

protected:

  virtual void init() {}

  virtual bool update(float deltaTime) {return true;}

  virtual void finalize() {}
  
  
  bool loadResources();
  
  void performCollisions();

private:

  sf::RenderWindow                      m_rendow;
    
  std::multimap<std::string, Object*>   m_objects;

  std::multimap<int, Drawable*>         m_drawables;
  
  std::vector<Solid*>                   m_solids;
  
  std::map<std::string, ObjectFactory*> m_objectFactory;
  
  Tileset                               m_tileset;
  
  Tilemap                               m_tilemap;
  
  TextureLoader                         m_textureLoader;
};

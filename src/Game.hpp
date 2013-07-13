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
#include "SoundLoader.hpp"
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
    
  TextureLoader& getTextureLoader();
  
  SoundLoader& getSoundLoader();
  
  
  bool loadTilemap(const std::string& filename, Tilemap& tilemap);
  
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
  
  TextureLoader                         m_textureLoader;
  
  SoundLoader                           m_soundLoader;
  
  Level*                                m_level;
  
  Camera*                               m_camera;
};


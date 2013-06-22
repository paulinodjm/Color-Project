//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <cstdlib>
#include <jsoncpp/json/json.h>
#include "Game.hpp"
#include "GameObject.hpp"
#include "Solid.hpp"
#include <iostream>
#include <fstream>

void Game::addObjectFactory(const std::string& name, ObjectFactory& factory)
{
  m_objectFactory[name] = &factory;
  std::cout << "Object '" << name << "' factory added." << std::endl;
}

Object* Game::createObject(const std::string& name)
{
  std::map<std::string, ObjectFactory*>::iterator factory = m_objectFactory.find(name);
  if (factory == m_objectFactory.end())
    return nullptr;
    
  Object* obj = factory->second->create();
  m_objects.insert(obj);
  
  Drawable* drawable = dynamic_cast<Drawable*>(obj);
  if (drawable)
  {
    m_drawables.insert(drawable);
  }
  
  Solid* solid = dynamic_cast<Solid*>(obj);
  if (solid)
  {
    //m_solids.insert(solid);
    m_solids.push_back(solid);
  }
  
  return obj;
}

int Game::mainLoop()
{
  m_rendow.create(sf::VideoMode(640,480), "Colour Project");
  m_rendow.setFramerateLimit(60);
  m_rendow.setKeyRepeatEnabled(false);
  
  if (!loadResources())
  {
    std::cout << "Resources loading failed. Exiting..." << std::endl;
    m_rendow.close();
  }
  
  for (Object* obj : m_objects)
  {
    obj->init();
  }

  sf::Clock gameClock;
  sf::Event event;
  while (m_rendow.isOpen())
  {
    while (m_rendow.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        m_rendow.close();
    }

    // update objects
    for (Object* obj : m_objects)
    {
      obj->update(gameClock.getElapsedTime().asSeconds());
    }

    // collisions
    performCollisions();

    // display
    m_rendow.clear(sf::Color::White);
    m_rendow.draw(m_tilemap);
    for (Drawable* drawable : m_drawables)
    { 
      if (drawable->isVisible())
        m_rendow.draw(*drawable);
    }
    m_rendow.display();
    gameClock.restart();
  }

  return EXIT_SUCCESS;
}

/** load resources desribed in 'data/resources.json' */
bool Game::loadResources()
{
  Json::Value root;
  Json::Reader reader;
  std::ifstream resources("data/resources.json");
  
  if (!resources.is_open())
  {
    std::cerr << "Unable to open resources file!" << std::endl;
    return false;
  }
  if (!reader.parse(resources, root))
  {
    std::cerr << reader.getFormatedErrorMessages();
    return false;
  }

  sf::Texture* tex = m_textureLoader.get(root["tileset"]["texture"].asString());
  if (!tex) return false;
  m_tileset.setTexture(*tex);
  m_tileset.setTileSize(root["tileset"].get("tileSize", 32).asInt());
  
  m_tilemap.setTileset(m_tileset);

  resources.close();
  return true; 
}

void Game::performCollisions()
{
  // TODO << do it with some iterators (?)
  
  // security while using indexes.
  if (m_solids.size() == 0)
    return;
  
  for (int i=0; i<m_solids.size()-1; i++)
  {
    if (m_solids[i]->isSolid())
    {
      for (int j=i+1; j<m_solids.size(); j++)
      {
        if (m_solids[j]->isSolid() 
        && m_solids[i]->getBbox().intersects(m_solids[j]->getBbox()))
        {
          m_solids[i]->collideWith(*m_solids[j]);
          m_solids[j]->collideWith(*m_solids[i]);
        }
      }
    }    
    m_solids[i]->endCollision();
  }
  m_solids[m_solids.size()-1]->endCollision();
  //*/
}

bool Game::loadTilemap(const std::string& filename)
{
  Json::Value root;
  Json::Reader reader;
  std::ifstream resources(filename);
  
  if (!resources.is_open())
  {
    std::cerr << "Unable to open '" << filename << "'!" << std::endl;
    return false;
  }
  if (!reader.parse(resources, root))
  {
    std::cerr << reader.getFormatedErrorMessages();
    return false;
  }
  
  m_tilemap.setWidth(root.get("width", 0).asUInt());
  m_tilemap.setHeight(root.get("height", 0).asUInt());
  
  Json::Value tiles = root["tiles"];
  for (unsigned int y=0; y<m_tilemap.getHeight(); y++)
  {
    for (unsigned int x=0; x<m_tilemap.getWidth(); x++)
    {
      m_tilemap.setTile(x, y, tiles[(y*m_tilemap.getWidth())+x].asUInt());
    }
  }
  
  return false;
}

TextureLoader& Game::getTextureLoader()
{
  return m_textureLoader;
}

Tileset& Game::getTileset()
{
  return m_tileset;
}

Tilemap& Game::getTilemap()
{
  return m_tilemap;
}

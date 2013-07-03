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
    
  return factory->second->create();
}

void Game::addObject(Object* object)
{
  if (object == nullptr) return;
  
  m_objects.insert( std::pair<std::string, Object*>(object->getName(), object) );
  
  Drawable* drawable = dynamic_cast<Drawable*>(object);
  if (drawable)
  {
    m_drawables.insert(std::pair<int, Drawable*>(drawable->getDepth(), drawable) );
  }
  
  Solid* solid = dynamic_cast<Solid*>(object);
  if (solid)
  {
    m_solids.push_back(solid);
  }
}

int Game::mainLoop()
{
  m_rendow.create(sf::VideoMode(640,480), "Colour Project");
  m_rendow.setFramerateLimit(4000);
  m_rendow.setKeyRepeatEnabled(false);
  
  if (!loadResources())
  {
    std::cout << "Resources loading failed. Exiting..." << std::endl;
    m_rendow.close();
  }
  else
  {
    /// for tests only
    loadTilemap("data/tilemap.json");
    loadObjects("data/objects.json");
    ///
  }
 
  for (auto it : m_objects)
  {
    it.second->init();
  }

  sf::Event event;
  while (m_rendow.isOpen())
  {
    while (m_rendow.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        m_rendow.close();
      else if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Key::Escape)
          m_rendow.close();
      }
    }

    // update objects
    for (auto it : m_objects)
    {
      it.second->update(1.f);
    }
    
    // move solids
    for (Solid* solid : m_solids)
    {
      solid->move(m_tilemap);
    }

    // collisions
    performCollisions();
    
    // display
    m_rendow.clear(sf::Color::White);
    m_rendow.draw(m_tilemap);
    for (auto it : m_drawables)
    { 
      Drawable* drawable = it.second;
      if (drawable->isVisible())
        m_rendow.draw(*drawable);
    }
    m_rendow.display();
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

  // tileset loading
  sf::Texture* tex = m_textureLoader.get(root["tileset"]["texture"].asString());
  if (!tex) return false;
  m_tileset.setTexture(*tex);
  m_tileset.setTileSize(root["tileset"].get("tileSize", 32).asInt());
  
  m_tilemap.setTileset(m_tileset);
  
  // object ressources loading
  Json::Value objects = root["objects"];
  for (auto it : m_objectFactory)
  {
    std::cout << "chargement des sprites de '" << it.first << "'... ";
  
    // sprites loading
    Json::Value sprites = objects[it.first]["sprites"];
    std::cout << "(" << sprites.size() << " sprites)" << std::endl;
    for (int i=0; i<sprites.size(); i++)
    {
      sf::Sprite* sprite = new sf::Sprite();
      tex = m_textureLoader.get(sprites[i]["texture"].asString());
      if (!tex) return false;
      sprite->setTexture(*tex, true);
      Json::Value rect = sprites[i]["rect"];
      if (!rect.isNull())
      {
        sprite->setTextureRect(
          sf::IntRect(
            rect.get("left", 0).asInt(),
            rect.get("top", 0).asInt(),
            rect.get("width", 0).asInt(),
            rect.get("height", 0).asInt()
          )
        );
      }
      Json::Value origin = sprites[i]["origin"];
      if (!origin.isNull())
      {
        sprite->setOrigin( sf::Vector2f(origin.get("x", 0).asDouble(), origin.get("y", 0).asDouble()) );
      }
      
      std::cout << "ajout du sprite '" << sprites[i]["name"].asString() << "'" << std::endl;
      it.second->getResources().addSprite(sprites[i]["name"].asString(), *sprite);
    }
  }

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
  std::ifstream file(filename);
  
  if (!file.is_open())
  {
    std::cerr << "Unable to open '" << filename << "'!" << std::endl;
    return false;
  }
  if (!reader.parse(file, root))
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
  
  file.close();
  return false;
}

bool Game::loadObjects(const std::string& filename)
{
  Json::Value root;
  Json::Reader reader;
  std::ifstream file(filename);
  
  if (!file.is_open())
  {
    std::cerr << "Unable to open '" << filename << "'!" << std::endl;
    return false;
  }
  if (!reader.parse(file, root))
  {
    std::cerr << reader.getFormatedErrorMessages();
    return false;
  }
  
  deleteObjects();
  
  for (auto it : m_objectFactory)
  {
    Json::Value objects = root[it.first];
    for (unsigned int i=0; i<objects.size(); i++)
    {
      Object* object = createObject(it.first);
      object->setName( objects[i].get("name", "").asString() );
      
      // solid properties
      Solid* solid = dynamic_cast<Solid*>(object);
      if (solid)
      { 
        solid->setPosition(objects[i].get("x", 0).asInt(), objects[i].get("y", 0).asInt());
      }
      
      // drawable properties
      Drawable* drawable = dynamic_cast<Drawable*>(object);
      if (drawable)
      {
        drawable->setDepth(objects[i].get("z", 0).asInt());
      }
      
      addObject(object);
    }
  }
  
  file.close();
  return true;
}

Object* Game::getObject(const std::string& name)
{
  auto it = m_objects.find(name);
  
  if (it == m_objects.end())
  {
    return nullptr;
  }
  else
  {
    return it->second;
  }
}

std::vector<Object*> Game::getObjects(const std::string& name)
{
  std::vector<Object*> objects;
  auto range = m_objects.equal_range(name);
  
  for (auto it = range.first; it != range.second; it++)
  {
    objects.push_back(it->second);
  }
  
  return objects;
}

void Game::deleteObjects()
{
  for (auto it : m_objects)
  {
    delete it.second;
  }
  m_objects.clear();
  m_drawables.clear();
  m_solids.clear();
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

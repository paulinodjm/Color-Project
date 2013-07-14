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

Game::Game() : m_level(nullptr)
{}

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
    m_level = new Level();
    loadObjects("data/objects.json");
    ///
  }

  m_level->init();

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
    m_level->update();
    
    // collisions
    m_level->performCollisions();
    
    // display
    m_rendow.clear(sf::Color::White);
    m_rendow.draw(*m_level);
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
  sf::Texture* tex;
  
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
  
  // object ressources loading
  for (auto it : m_objectFactory)
  {
    // textures loading
    Json::Value textures = root[it.first]["textures"];
    for (int i=0; i<textures.size(); i++)
    {
      tex = m_textureLoader.get(textures[i]["src"].asString());
      if (tex)
      {
        it.second->getResources().addTexture(textures[i]["name"].asString(), tex);
      }
      else
      {
        return false;
      }
    }
    
    // sounds loading
    Json::Value sounds = root[it.first]["sounds"];
    for (int i=0; i<sounds.size(); i++)
    {
      sf::SoundBuffer* soundBuffer = m_soundLoader.get(sounds[i]["src"].asString());
      if (soundBuffer)
      {
        it.second->getResources().addSoundBuffer(sounds[i]["name"].asString(), soundBuffer);
      }
    }
  
    // sprites loading
    Json::Value sprites = root[it.first]["sprites"];
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
      
      it.second->getResources().addSprite(sprites[i]["name"].asString(), *sprite);
    }
    
    // animations loading
    Json::Value animations = root[it.first]["animations"];
    for (int i=0; i<animations.size(); i++)
    {
      Animation* animation = new Animation();
      tex = m_textureLoader.get(animations[i]["texture"].asString());
      if (tex)
        animation->setSpriteSheet(*tex);
      sf::IntRect rect(0,0, animations[i].get("width", 0).asInt(), animations[i].get("height", 0).asInt());
      for (int j=0; j<animations[i].get("length", 1).asInt(); j++)
      {
        rect.left = rect.width * j;
        animation->addFrame(rect);
      }
      
      it.second->getResources().addAnimation(animations[i]["name"].asString(), animation);
    }
    
    // tilesets loading
    Json::Value tilesets = root[it.first]["tilesets"];
    for (int i=0; i<tilesets.size(); i++)
    {
      Tileset* tileset = new Tileset();
      tex = m_textureLoader.get(tilesets[i]["texture"].asString());
      if (tex)
        tileset->setTexture(*tex);
      tileset->setTileSize(tilesets[i].get("tileSize", 32).asInt());
      
      it.second->getResources().addTileset( tilesets[i]["name"].asString(), tileset);
    }
  }

  resources.close();
  return true; 
}

bool Game::loadTilemap(const std::string& filename, Tilemap& tilemap)
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
  
  tilemap.setWidth(root.get("width", 0).asUInt());
  tilemap.setHeight(root.get("height", 0).asUInt());
  
  Json::Value tiles = root["tiles"];
  for (unsigned int y=0; y<tilemap.getHeight(); y++)
  {
    for (unsigned int x=0; x<tilemap.getWidth(); x++)
    {
      tilemap.setTile(x, y, tiles[(y*tilemap.getWidth())+x].asUInt());
    }
  }
  
  file.close();
  std::cout << "Tilemap '" << filename << "' loaded" << std::endl;
  return true;
}

bool Game::loadObjects(const std::string& filename)
{
  if (!m_level)
  {
    std::cout << "Object loading failed : no level exists" << std::endl;
    return false;
  }

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
  
  m_level->deleteObjects();
  
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
      
      // tilemap properties
      Tilemap* tilemap = dynamic_cast<Tilemap*>(object);
      if (tilemap)
      {
        Json::Value src = objects[i]["src"];
        if (!src.isNull())
        {
          if (!loadTilemap(src.asString(), *tilemap))
            return false;
        }
      }
      
      m_level->addObject(object);
    }
  }
  
  file.close();
  return true;
}

TextureLoader& Game::getTextureLoader()
{
  return m_textureLoader;
}

SoundLoader& Game::getSoundLoader()
{
  return m_soundLoader;
}

Tileset& Game::getTileset()
{
  return m_tileset;
}

Level* Game::getLevel()
{
  return m_level;
}

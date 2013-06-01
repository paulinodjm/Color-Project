//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <cstdlib>
#include "Game.hpp"
#include "Object.hpp"

void Game::addObjectFactory(const std::string& name, ObjectFactory& factory)
{
  m_objectFactory[name] = &factory;
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
    // < TODO add the object to the collision system
  }
  
  return obj;
}

int Game::mainLoop()
{
  m_rendow.create(sf::VideoMode(640,480), "Colour Project");
  m_rendow.setFramerateLimit(60);
  m_rendow.setKeyRepeatEnabled(false);

  sf::Clock gameClock;
  sf::Event event;
  while (m_rendow.isOpen())
  {
    while (m_rendow.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        m_rendow.close();
    }

    // update
    for (Object* obj : m_objects)
    {
      obj->update(gameClock.getElapsedTime().asSeconds());
    }

    // display
    m_rendow.clear(sf::Color::White);
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

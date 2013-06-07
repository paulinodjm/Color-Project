//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <cstdlib>
#include "Game.hpp"
#include "GameObject.hpp"
#include <iostream>

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

void Game::performCollisions()
{
  // TODO << do it with some iterators
  
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

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

using namespace e;

Game::Game() : BaseGame(m_rendow)
{}

int Game::mainLoop()
{
  m_rendow.create(sf::VideoMode(640,480), "Color Project");
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
    getLevel()->update();
    
    // collisions
    getLevel()->performCollisions();
    
    // display
    m_rendow.clear(sf::Color::White);
    m_rendow.draw(*getLevel());
    m_rendow.display();
  }

  return EXIT_SUCCESS;
}


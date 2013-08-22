//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Game.hpp"
#include <iostream>

Game::Game() : BaseGame(m_rendow)
{}

int Game::mainLoop()
{
  m_rendow.create(sf::VideoMode(640,480), "Color Project", sf::Style::Titlebar);
  m_rendow.setFramerateLimit(60);
  m_rendow.setKeyRepeatEnabled(false);
  
  if (!loadResources())
  {
    std::cout << "Resources loading failed. Exiting..." << std::endl;
    m_rendow.close();
  }
  else
  {
    /* for tests only
    m_level = new e::Level();
    loadObjects("data/objects.json");
    //*/
  }

  //m_level->init();

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

    update();
    m_rendow.display();
  }

  return EXIT_SUCCESS;
}


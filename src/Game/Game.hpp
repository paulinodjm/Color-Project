//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/BaseGame.hpp"

class Game : public e::BaseGame
{
public:

  Game();
  
  int mainLoop();
  
private:

  sf::RenderWindow                      m_rendow;
};


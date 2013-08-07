//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "BaseTypes.hpp"
#include "BaseGame.hpp"
#include "Tileset.hpp"
#include "TextureLoader.hpp"
#include "SoundLoader.hpp"
#include "Tilemap.hpp"
#include "Drawable.hpp"
#include "Level.hpp"

namespace e
{
  class Game : public BaseGame
  {
  public:

    Game();
    
    int mainLoop();
    
  private:

    sf::RenderWindow                      m_rendow;
  };
}


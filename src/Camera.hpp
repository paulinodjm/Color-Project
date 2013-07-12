//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:

  /** Called each time to set the game view */
  virtual void calcView(sf::View& view) const = 0;
  
};

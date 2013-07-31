//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "BaseTypes.hpp"
#include "Loader.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class TextureLoader : public Loader<sf::Texture>
{
public:

  sf::Texture* load(const std::string& name)
  {
    std::cout << "Loading '" << name << "'..." << std::endl;
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(name))
    {
      return texture;
    }
    else
    {
      delete texture;
      return nullptr;
    }
  }
};


//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "BaseTypes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Loader.hpp"

namespace e
{
  class SoundLoader: public Loader<sf::SoundBuffer>
  {
  public:

    sf::SoundBuffer* load(const std::string& name)
    {
      std::cout << "Loading '" << name << "'..." << std::endl;
      sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
      if (soundBuffer->loadFromFile(name))
      {
        return soundBuffer;
      }
      else
      {
        delete soundBuffer;
        return nullptr;
      }
    }
  };
}


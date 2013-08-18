//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "SoundBuffer.hpp"
#include <SFML/Audio/Sound.hpp>

namespace e
{
  class SoundPlayer : public sf::Sound
  {
  public:
  
    SoundPlayer();
    
    SoundPlayer(const e::SoundBuffer& buffer);
    
    SoundPlayer(const SoundPlayer& copy);
    
    void operator=(const SoundPlayer& other);
    
    virtual ~SoundPlayer();
    
    
    void setBuffer(const e::SoundBuffer& buffer);
    
    const SoundBuffer* getBuffer() const;
  
  private:
  
    SoundBuffer *m_buffer;
  };
}

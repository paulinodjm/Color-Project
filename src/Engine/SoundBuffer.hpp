//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <map>
#include <string>
#include <iostream>

namespace e
{
  class SoundBuffer;

  ///////////////////////////////////////////////////
  /// Hold a sf::SoundBuffer and keep a reference counter
  ///////////////////////////////////////////////////
  class SoundBufferData : public sf::SoundBuffer
  {
    friend class e::SoundBuffer;
    
  private:
  
    SoundBufferData();
  
    unsigned int m_refCount;
    
    bool m_loaded;
  };

  //////////////////////////////////
  // pointer to a SoundBufferData object
  //////////////////////////////////
  class SoundBuffer
  {
  public:
  
    SoundBuffer(const std::string& id);
    
    SoundBuffer(const e::SoundBuffer& copy);
    
    void operator=(const e::SoundBuffer& other);
    
    bool operator!() const;
    
    SoundBufferData& operator*() const;
    
    virtual ~SoundBuffer();
    
  private:
    
    std::map<std::string, SoundBufferData*>::iterator m_data;
    
    static std::map<std::string, SoundBufferData*> m_allData;
  };
}

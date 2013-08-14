//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
#include <iostream>
#include <cassert>

namespace e
{
  class Texture;

  ///////////////////////////////////////////////////
  /// Hold a sf::Texture and keep a reference counter
  ///////////////////////////////////////////////////
  class TextureData : public sf::Texture
  {
    friend class e::Texture;
    
  private:
  
    TextureData();
  
    unsigned int m_refCount;
  };

  //////////////////////////////////
  // pointer to a TextureData object
  //////////////////////////////////
  class Texture
  {
  public:
  
    Texture(const std::string& id);
    
    bool operator!() const;
    
    virtual ~Texture();
    
  private:
  
    bool m_loaded;
    
    std::map<std::string, TextureData*>::iterator m_data;
    
    static std::map<std::string, TextureData*> m_allData;
  };
}

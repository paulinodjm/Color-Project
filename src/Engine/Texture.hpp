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
  
    TextureData() : m_refCount(0) {}
  
    unsigned int m_refCount;
  };

  //////////////////////////////////
  // pointer to a TextureData object
  //////////////////////////////////
  class Texture
  {
  public:
  
    Texture(const std::string& id) : m_data(nullptr)
    {
      auto it = m_allData.find(id);
      if (it == m_allData.end())
      {
        m_data = new TextureData;
        m_allData[id] = m_data;
        std::cout << "[création de '" << id << "'";
      }
      else
      {
        m_data = it->second;
        std::cout << "[récupération de '" << id << "'";
      }
    
      std::cout << "]" << std::endl;
      assert(m_data);
      m_data->m_refCount++;
    }
    
    virtual ~Texture()
    {
      m_data->m_refCount--;
      if (m_data->m_refCount == 0)
      {
        auto it = m_allData.find(m_id);
        m_allData.erase(it);
        delete m_data;
        std::cout << "[destruction de '" << m_id << "']" << std::endl;
      }
    }
    
  private:
  
    TextureData* m_data;
  
    std::string m_id;
    
    static std::map<std::string, TextureData*> m_allData;
  };
}

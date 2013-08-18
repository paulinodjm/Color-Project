//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Texture.hpp"

using namespace e;

TextureData::TextureData() : m_refCount(0), m_loaded(false) {}


std::map<std::string, TextureData*> Texture::m_allData;

Texture::Texture(const std::string& id)
{
  auto it = m_allData.find(id);
  if (it == m_allData.end())
  {
    std::cout << "Loading '" << id << "'... ";
    TextureData *data = new TextureData;
    
    if (data->loadFromFile(id))
    {
      std::cout << "Complete." << std::endl;
      data->m_loaded = true;
    }        
    m_data = m_allData.insert( std::pair<std::string, TextureData*>(id, data) ).first;
  }
  else
  {
    m_data = it;
  }
  m_data->second->m_refCount++;
}

Texture::Texture(const Texture& copy)
{
  m_data = copy.m_data;
  m_data->second->m_refCount++;
}

void Texture::operator=(const Texture& other)
{
  m_data->second->m_refCount--;
  if (m_data->second->m_refCount == 0)
  {
    std::cout << "Deleting '" << m_data->first << "'." << std::endl;
    delete m_data->second;
    m_allData.erase(m_data);
  }
  m_data = other.m_data;
  m_data->second->m_refCount++;
}

bool Texture::operator!() const
{
  return !(m_data->second->m_loaded);
}

TextureData& Texture::operator*() const
{
  return *(m_data->second);
}

Texture::~Texture()
{
  m_data->second->m_refCount--;
  if (m_data->second->m_refCount == 0)
  {
    std::cout << "Deleting '" << m_data->first << "'." << std::endl;
    delete m_data->second;
    m_allData.erase(m_data);
  }
}

void Texture::printInfo()
{
  std::cout << "[--Textures--]" << std::endl;
  for (auto it : m_allData)
  {
    std::cout << "'" << it.first << "' : " << it.second->m_refCount << " copy";
    if (it.second->m_loaded)
      std::cout << "(loaded)";
    std::cout << std::endl;
  }
  std::cout << "[------------]" << std::endl;
}

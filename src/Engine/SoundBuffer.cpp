//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "SoundBuffer.hpp"

using namespace e;


SoundBufferData::SoundBufferData() : m_refCount(0) {}


std::map<std::string, SoundBufferData*> SoundBuffer::m_allData;

SoundBuffer::SoundBuffer(const std::string& id) : m_loaded(false)
{
  auto it = m_allData.find(id);
  if (it == m_allData.end())
  {
    std::cout << "Loading '" << id << "'... ";
    SoundBufferData *data = new SoundBufferData;
    
    if (data->loadFromFile(id))
    {
      std::cout << "Complete." << std::endl;
      m_loaded = true;
    }        
    m_data = m_allData.insert( std::pair<std::string, SoundBufferData*>(id, data) ).first;
  }
  else
  {
    m_data = it;
  }
  m_data->second->m_refCount++;
}

bool SoundBuffer::operator!() const
{
  return !m_loaded;
}

SoundBufferData& SoundBuffer::operator*() const
{
  return *(m_data->second);
}

SoundBuffer::~SoundBuffer()
{
  m_data->second->m_refCount--;
  if (m_data->second->m_refCount == 0)
  {
    std::cout << "Deleting '" << m_data->first << "'." << std::endl;
    delete m_data->second;
    m_allData.erase(m_data);
  }
}

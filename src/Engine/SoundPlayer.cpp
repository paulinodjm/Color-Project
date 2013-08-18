//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "SoundPlayer.hpp"

#include <iostream>

using namespace e;

SoundPlayer::SoundPlayer() : 
  sf::Sound(), 
  m_buffer(nullptr) 
{}

SoundPlayer::SoundPlayer(const e::SoundBuffer& buffer) : SoundPlayer()
{
  m_buffer = new e::SoundBuffer( buffer );
  sf::Sound::setBuffer( *buffer );
}

SoundPlayer::SoundPlayer(const SoundPlayer& copy) : 
  sf::Sound(copy),
  m_buffer(nullptr)
{
  if (copy.m_buffer)
  {
    m_buffer = new e::SoundBuffer( *copy.m_buffer );
  }
}

void SoundPlayer::operator=(const SoundPlayer& other)
{
  if (m_buffer)
  {
    delete m_buffer;
    m_buffer = nullptr;
  }
  if (other.m_buffer)
  {
    m_buffer = new e::SoundBuffer( *other.m_buffer );
  }
  sf::Sound::operator=(other);
}

SoundPlayer::~SoundPlayer()
{
  if (m_buffer)
    delete m_buffer;
}

void SoundPlayer::setBuffer(const e::SoundBuffer& buffer)
{
  if (m_buffer)
  {
    delete m_buffer;
  }
  
  m_buffer = new e::SoundBuffer( buffer );
  sf::Sound::setBuffer( *buffer );
}

const e::SoundBuffer* SoundPlayer::getBuffer() const
{
  return m_buffer;
}

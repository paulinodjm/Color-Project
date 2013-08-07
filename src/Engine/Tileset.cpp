//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Tileset.hpp"
#include <iostream>

using namespace e;

Tileset::Tileset() : m_tileSize(32), m_tileCount(0), m_vTileCount(0), m_hTileCount(0) {}

sf::Sprite Tileset::getTileSprite(unsigned int iTile) const
{
  sf::Sprite sprite = m_sprite;
  if (iTile < m_tileCount)
  {
    sf::IntRect textureRect;
    textureRect.left = (iTile % m_hTileCount) * m_tileSize;
    textureRect.top = (iTile / m_hTileCount) * m_tileSize;
    textureRect.width = m_tileSize;
    textureRect.height = m_tileSize;
    sprite.setTextureRect(textureRect);
  }
  return sprite;
}

const sf::Sprite& Tileset::getSprite() const
{
  return m_sprite;
}

void Tileset::setTexture(const sf::Texture& texture, bool construct)
{
  m_sprite.setTexture(texture, true); 
  if (construct)
    constructTileset();
}

const sf::Texture* Tileset::getTexture() const
{
  return m_sprite.getTexture();
}

void Tileset::setTileSize(int tileSize, bool construct)
{
  if (tileSize <= 0) return;

  m_tileSize = tileSize;
  
  if (construct)
    constructTileset();
}

int Tileset::getTileSize() const
{
  return m_tileSize;
}

unsigned int Tileset::getTileCount() const
{
  return m_tileCount;
}

void Tileset::constructTileset()
{
  const sf::Texture* texture = m_sprite.getTexture();
  if (texture)
  {
    m_hTileCount = texture->getSize().x / m_tileSize;
    m_vTileCount = texture->getSize().y / m_tileSize;
    m_tileCount = m_vTileCount * m_hTileCount;
  }
  else
  {
    m_tileCount = 0;
    m_vTileCount = 0;
    m_hTileCount = 0;
  }
}

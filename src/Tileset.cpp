//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Tileset.hpp"

Tileset::Tileset() : m_tileSize(32), m_tileCount(0), m_vTileCount(0), m_hTileCount(0) {}

sf::Sprite Tileset::getTileSprite(unsigned int iTile) const
{
  sf::Sprite sprite = m_sprite;
  
  return sprite;
}

void Tileset::setTexture(const sf::Texture& texture, bool construct)
{
  m_sprite.setTexture(texture); 
}

const sf::Texture* Tileset::getTexture() const
{
  return m_sprite.getTexture();
}

void Tileset::setTileSize(unsigned int tileSize, bool construct)
{
  m_tileSize = tileSize;
  
  if (construct)
    constructTileset();
}

unsigned int Tileset::getTileSize() const
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
    m_vTileCount = texture->getSize().x / m_tileSize;
    m_hTileCount = texture->getSize().y / m_tileSize;
    m_tileCount = m_vTileCount * m_hTileCount;
  }
  else
  {
    m_tileCount = 0;
    m_vTileCount = 0;
    m_hTileCount = 0;
  }
}

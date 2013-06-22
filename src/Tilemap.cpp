//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Tilemap.hpp"
#include <iostream>

Tilemap::Tilemap() : Drawable(),
  m_width(0),
  m_height(0),
  m_tileset(nullptr)
{}

bool Tilemap::isTileSolid(unsigned int x, unsigned int y) const
{
  return getTile(x, y) > 0;
}


void Tilemap::setTile(unsigned int x, unsigned int y, unsigned int tile)
{
  if (x < m_width && y < m_height)
    m_tiles[x][y] = tile;
}

unsigned int Tilemap::getTile(unsigned int x, unsigned int y) const
{
  if (x < m_width && y < m_height)
  {
    return m_tiles[x][y];
  }
  else
  {
    return 0;
  }
}


unsigned int Tilemap::getWidth() const
{
  return m_width;
}

unsigned int Tilemap::getHeight() const
{
  return m_height;
}

void Tilemap::setWidth(unsigned int width)
{
  m_tiles.resize(width);
  for (unsigned int i=m_width; i<width; i++)
  {
    m_tiles[i].resize(m_height, 0);
  }
  m_width = width;
}

void Tilemap::setHeight(unsigned int height)
{
  for (std::vector<unsigned int>& column : m_tiles)
  {
    column.resize(height, 0);
  }
  m_height = height;
}

const Tileset* Tilemap::getTileset() const
{
  return m_tileset;
}
  
void Tilemap::setTileset(const Tileset& tileset)
{
  m_tileset = &tileset;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (!m_tileset) return;

  unsigned int tileSize = m_tileset->getTileSize();

  for (unsigned int y=0; y<m_height; y++)
  {
    for (unsigned int x=0; x<m_width; x++)
    {
      if (m_tiles[x][y] > 0)
      {
        sf::Sprite tile = m_tileset->getTileSprite(m_tiles[x][y]-1);
        tile.setPosition(x*tileSize, y*tileSize);
        target.draw(tile);
      }
    }
  }
}

bool Tilemap::placeFree(const sf::IntRect& rect) const
{
  if (!m_tileset) return true;
  
  unsigned int xstart = rect.left / m_tileset->getTileSize();
  unsigned int xend = (rect.left + rect.width - 1) / m_tileset->getTileSize(); 
  unsigned int ystart = rect.top / m_tileset->getTileSize();
  unsigned int yend = (rect.top + rect.height - 1) / m_tileset->getTileSize();
  
  for (unsigned int x=xstart; x<=xend; x++)
  {
    for (unsigned int y=ystart; y<=yend; y++)
    {
      if (isTileSolid(x, y))
      {
        return false;
      }
    }
  }
  return true;
}

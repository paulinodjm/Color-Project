//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "BaseTypes.hpp"
#include "Tileset.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Tilemap : public sf::Drawable
{
public:

  Tilemap();

  virtual bool isTileSolid(unsigned int x, unsigned int y) const;


  void setTile(unsigned int x, unsigned int y, unsigned int tile);
  
  unsigned int getTile(unsigned int x, unsigned int y) const;
  
  
  unsigned int getWidth() const;
  
  unsigned int getHeight() const;
  
  void setWidth(unsigned int width);
  
  void setHeight(unsigned int height);
  
  
  const Tileset* getTileset() const;
  
  void setTileset(const Tileset& tileset);
  
protected:

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
private:

  unsigned int m_width, m_height;

  const Tileset* m_tileset;
  
  std::vector<std::vector<unsigned int>> m_tiles;
};

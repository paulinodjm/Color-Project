//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "BaseTypes.hpp"
#include <SFML/Graphics.hpp>

class Tileset
{
public:

  Tileset();

  virtual bool isTileSolid(unsigned int iTile) const { return false; }

  sf::Sprite getTileSprite(unsigned int iTile) const;
  
  
  void setTexture(const sf::Texture& texture, bool construct=false);
  
  const sf::Texture* getTexture() const;
  
  void setTileSize(unsigned int tileSize, bool construct=true);
  
  unsigned int getTileSize() const;
  
  unsigned int getTileCount() const;
  
  void constructTileset(); 

private:  

  unsigned int m_tileSize;
  
  unsigned int m_tileCount, m_vTileCount, m_hTileCount;

  sf::Sprite m_sprite;
};

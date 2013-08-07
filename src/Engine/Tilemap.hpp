//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "BaseTypes.hpp"
#include "Tileset.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Drawable.hpp"
#include "Object.hpp"
#include "Resources.hpp"

namespace e
{
  class Tilemap : public Drawable, public Object
  {
  public:

    Tilemap(Resources& resources);

    virtual bool isTileSolid(int x, int y) const;


    void setTile(int x, int y, unsigned int tile);
    
    unsigned int getTile(int x, int y) const;
    
    
    unsigned int getWidth() const;
    
    unsigned int getHeight() const;
    
    void setWidth(unsigned int width);
    
    void setHeight(unsigned int height);
    
    
    const Tileset* getTileset() const;
    
    void setTileset(const Tileset& tileset);
    
    
    bool placeFree(const sf::FloatRect& rect) const ;
    
    
    int getTileSize() const;
    
  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
  private:

    unsigned int m_width, m_height;

    const Tileset* m_tileset;
    
    std::vector<std::vector<unsigned int>> m_tiles;
  };
}


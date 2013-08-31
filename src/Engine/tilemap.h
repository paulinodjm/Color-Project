//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <string>
#include <memory>
#include "contentmanager.h"
#include "resources.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>

class TILEMAP : public sf::Drawable
{
public:

  TILEMAP();

  unsigned int Tile(int x, int y) const;
  void SetTile(int x, int y, unsigned int tile);
  
  bool Load(const std::string& filename, CONTENTMANAGER& contentManager);
  bool Save(const std::string& filename) const;
  
  void SetWidth(int w);
  void SetHeight(int h);
  int Width() const;
  int Height() const;
  
  void SetTileSize(int size);
  int TileSize() const;
  
  unsigned int TileCount() const;
  unsigned int TileCountPerRow() const;
  
  void SetTexture(const std::shared_ptr<TEXTURE>& tex);
  const std::shared_ptr<TEXTURE>& Texture() const;
  
  bool PlaceFree(const sf::FloatRect& rect) const ;
  
protected:

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  bool TileToRect(unsigned int iTile, sf::IntRect& rect) const;
  void ConstructTileset();
  
private:

  std::vector<std::vector<unsigned int>> tile;
  int                                    tileSize;
  std::shared_ptr<TEXTURE>               texture;
  
  int width, height;
  unsigned int tileCount, tileCountPerRow;
};


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

class TILEMAP
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
  
  void SetTileSize(unsigned int size);
  unsigned int TileSize() const;
  
  void SetTexture(const std::shared_ptr<TEXTURE>& tex);
  const std::shared_ptr<TEXTURE>& Texture() const;
  
private:

  std::vector<std::vector<unsigned int>> tile;
  unsigned int                           tileSize;
  std::shared_ptr<TEXTURE>               texture;
  
  int width, height;
};


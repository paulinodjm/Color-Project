//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "tilemap.h"
#include <fstream>
#include <jsoncpp/json/json.h>

TILEMAP::TILEMAP() : tileSize(0), width( ), height(0) {}

bool TILEMAP::Load(const std::string& filename, CONTENTMANAGER& contentManager)
{
  std::ifstream file(filename);
  Json::Value root;
  Json::Reader reader;
  
  if (!file.is_open())
  {
    std::cout << "Failed to load tilemap '" << filename << "' : unable to open file." << std::endl;
    return false;
  }
  if (!reader.parse(file, root))
  {
    std::cout << "Failed to load tilemap '" << filename << "' : " << reader.getFormatedErrorMessages() << std::endl;
    return false;
  }
  if (!contentManager.Load<TEXTURE>(texture, root["texture"].asString()))
  {
    std::cout << "Failed to load tilemap '" << filename << "' : texture not found." << std::endl;
    return false;
  }
  tileSize = root["tileSize"].asUInt();
  SetHeight( root["height"].asInt() );
  SetWidth( root["width"].asInt() );
  
  Json::Value jtiles = root["tiles"];
  for (unsigned int y=0; y<height; y++)
  {
    for (unsigned int x=0; x<width; x++)
    {
      SetTile(x, y, jtiles[(y*width)+x].asUInt());
    }
  }
  
  std::cout << "Tilemap '" << filename << "' loaded." << std::endl;
  return true;
}

bool TILEMAP::Save(const std::string& filename) const
{
  return false;
}

unsigned int TILEMAP::Tile(int x, int y) const
{
  if (x>=0 && x<width && y>=0 && y<height)
  {
    return tile[x][y];
  }
  else
  {
    return 0;
  }
}

void TILEMAP::SetTile(int x, int y, unsigned int value)
{
  if (x>=0 && x<width && y>=0 && y<height)
  {
    tile[x][y] = value;
  }
}

void TILEMAP::SetWidth(int w)
{
  if (w<0) return;
  
  tile.resize(w);
  for (unsigned int i=width; i<w; i++)
  {
    tile[i].resize(height, 0);
  }
  width = w;
}

void TILEMAP::SetHeight(int h)
{
  if (h<0) return;

  for (std::vector<unsigned int>& column : tile)
  {
    column.resize(h, 0);
  }
  height = h;
}

int TILEMAP::Width() const
{
  return width;
}

int TILEMAP::Height() const
{
  return height;
}

void TILEMAP::SetTileSize(unsigned int size)
{
  tileSize = size;
}

unsigned int TILEMAP::TileSize() const
{
  return tileSize;
}
  
void TILEMAP::SetTexture(const std::shared_ptr<TEXTURE>& tex)
{
  texture = tex;
}

const std::shared_ptr<TEXTURE>& TILEMAP::Texture() const
{
  return texture;
}

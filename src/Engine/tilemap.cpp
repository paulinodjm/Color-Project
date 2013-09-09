//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "tilemap.h"
#include "zipstream.h"
#include "zipstring.h"
#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>

TILEMAP::TILEMAP() : tileSize(0), width( ), height(0), tileCount(0), tileCountPerRow(0) {}

bool TILEMAP::Load(const std::string& filename, CONTENTMANAGER& contentManager)
{
  ZIPSTREAM zipstream;
  ZIPSTRING zipstring;
  Json::Value root;
  Json::Reader reader;
  
  if (!zipstream.Open(filename))
  {
    std::cout << "Failed to load tilemap '" << filename << "'." << std::endl;
    return false;
  }
  if (!zipstring.Read(zipstream))
  {
    std::cout << "Failed to load tilemap '" << filename << "' : stream error." << std::endl;
    return false;
  }
  if (!reader.parse(zipstring.Str(), root))
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
  
  ConstructTileset();
  
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

void TILEMAP::SetTileSize(int size)
{
  if (size < 0)
    size = 0;
  tileSize = size;
  ConstructTileset();
}

int TILEMAP::TileSize() const
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


void TILEMAP::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (!texture) return;

  sf::Sprite sprite(*texture);
  sf::IntRect rect;

  for (unsigned int y=0; y<height; y++)
  {
    for (unsigned int x=0; x<width; x++)
    {
      if ( TileToRect( (tile[x][y]), rect) )
      {
        sprite.setTextureRect(rect);
        sprite.setPosition(x*tileSize, y*tileSize);
        target.draw(sprite);
      }
    }
  }
}

void TILEMAP::ConstructTileset()
{
  unsigned int tileCountPerColumn = 0;

  if (!texture)
  {
    tileCount = 0;
    tileCountPerRow = 0;
  }
  else
  {
    tileCountPerRow = texture->getSize().x / tileSize;
    tileCountPerColumn = texture->getSize().y / tileSize;
    tileCount = tileCountPerRow * tileCountPerColumn;
  }
}

bool TILEMAP::TileToRect(unsigned int iTile, sf::IntRect& rect) const
{
  if (iTile == 0 || iTile > tileCount)
  {
    return false;
  }
  
  iTile--;
  rect.left = (iTile % tileCountPerRow) * tileSize;
  rect.top = (iTile / tileCountPerRow) * tileSize;
  rect.width = tileSize;
  rect.height = tileSize;
  
  return true;
}

unsigned int TILEMAP::TileCount() const
{
  return tileCount;
}

unsigned int TILEMAP::TileCountPerRow() const
{
  return tileCountPerRow;
}

bool TILEMAP::PlaceFree(const sf::FloatRect& rect) const
{
  if ( (rect.left+rect.width <= 0.f) || (rect.top+rect.height <= 0.f) )
    return true;
 
  int left = static_cast<int>(rect.left);
  int top = static_cast<int>(rect.top);
  int right = static_cast<int>(rect.left + rect.width);
  int bottom = static_cast<int>(rect.top + rect.height);
  
  if (right < (rect.left + rect.width))
    right++;
  if (bottom < (rect.top + rect.height))
    bottom++;
  
  int xstart = left / tileSize;
  int xend = (right-1) / tileSize; 
  int ystart = top / tileSize;
  int yend = (bottom-1) / tileSize;
  
  for (int x=xstart; x<=xend; x++)
  {
    for (int y=ystart; y<=yend; y++)
    {
      if (Tile(x,y) > 0)
      {
        return false;
      }
    }
  }
  return true;
}


//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Resources.hpp"
#include <iostream>

sf::Texture* Resources::getTexture(const std::string& name)
{
  auto it = m_textures.find(name);
  if (it != m_textures.end())
  {
    return it->second;
  }
  else
  {
    return nullptr;
  }
}

sf::Sprite* Resources::getSprite(const std::string& name)
{
  auto it = m_sprites.find(name);
  if (it != m_sprites.end())
  {
    return &(it->second);
  }
  else
  {
    return nullptr;
  }
}

Tileset* Resources::getTileset(const std::string& name)
{
  auto it = m_tileset.find(name);
  if (it != m_tileset.end())
  {
    return it->second;
  }
  else
  {
    return nullptr;
  }
}

Animation* Resources::getAnimation(const std::string& name)
{
  auto it = m_animations.find(name);
  if (it != m_animations.end())
  {
    return it->second;
  }
  else
  {
    return nullptr;
  }
}

bool Resources::addTexture(const std::string& name, sf::Texture* texture)
{
  auto it = m_textures.find(name);
  if (it == m_textures.end())
  {
    m_textures[name] = texture;
    return true;
  }
  else
  {
    return false;
  }
}

bool Resources::addSprite(const std::string& name, const sf::Sprite& sprite)
{
  auto it = m_sprites.find(name);
  if (it == m_sprites.end())
  {
    m_sprites[name] = sprite;
    return true;
  }
  else
  {
    return false;
  }
}

bool Resources::addTileset(const std::string& name, Tileset* tileset)
{
  auto it = m_tileset.find(name);
  if (it == m_tileset.end())
  {
    m_tileset[name] = tileset;
    return true;
  }
  else
  {
    return false;
  }
}

bool Resources::addAnimation(const std::string& name, Animation* animation)
{
  auto it = m_animations.find(name);
  if (it == m_animations.end())
  {
    m_animations[name] = animation;
    return true;
  }
  else
  {
    return false;
  }
}


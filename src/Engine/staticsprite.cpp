//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "staticsprite.h"
#include "contentmanager.h"
#include "jsoncpp/json/json.h"
#include <fstream>
#include <SFML/Graphics/RenderTarget.hpp>

STATICSPRITE::STATICSPRITE() {}

bool STATICSPRITE::Load(const std::string& name, CONTENTMANAGER& contentManager)
{
  std::ifstream file(name);
  Json::Reader reader;
  Json::Value root;
  
  texture.reset();
  
  if (!file.is_open())
  {
    std::cout << "Failed to load sprite '" << name << "' : unable to open file." << std::endl;
    return false;
  }
  if (!reader.parse(file, root))
  {
    std::cout << "Failed to load sprite '" << name << "' : " << reader.getFormatedErrorMessages();
    return false;
  }
  if (!contentManager.Load<TEXTURE>(texture, root["texture"].asString()) )
  {
    return false;
  }
  
  setOrigin(
    root["origin"].get("x",0).asDouble(), 
    root["origin"].get("y", 0).asDouble() 
  );
  sf::FloatRect rect(
    root["rect"].get("left",0).asDouble(),
    root["rect"].get("top", 0).asDouble(),
    root["rect"].get("width", 0).asDouble(),
    root["rect"].get("height", 0).asDouble()
  );
  
  vertex[0].position = sf::Vector2f(0,0);
  vertex[1].position = sf::Vector2f(0, rect.height);
  vertex[2].position = sf::Vector2f(rect.width, rect.height);
  vertex[3].position = sf::Vector2f(rect.width, 0);

  vertex[0].texCoords = sf::Vector2f(rect.left, rect.top);
  vertex[1].texCoords = sf::Vector2f(rect.left, rect.top+rect.height);
  vertex[2].texCoords = sf::Vector2f(rect.left+rect.width, rect.top+rect.height);
  vertex[3].texCoords = sf::Vector2f(rect.left+rect.width, rect.top);
  
  std::cout << "Sprite '" << name << "' loaded." << std::endl;
  return true;
}

bool STATICSPRITE::Save(const std::string& filename)
{
  return false;
}

void STATICSPRITE::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (texture)
  {
    states.transform *= getTransform();
    states.texture = &(*texture);
    target.draw(vertex, 4, sf::Quads, states);
  }
}

const std::shared_ptr<TEXTURE>& STATICSPRITE::Texture() const
{
  return texture;
}

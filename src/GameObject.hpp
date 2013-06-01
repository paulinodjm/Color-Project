//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "Object.hpp"
#include <SFML/Graphics.hpp>

class GameObject : public Object, public Drawable, public Solid
{
public:

  GameObject();
  
  virtual void setPosition(int x, int y);
  virtual void setPosition(const sf::Vector2i& position);
  
  const sf::Sprite& getSprite() const;
  
  void setSprite(const sf::Sprite& sprite);
  
protected:

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
private:

  sf::Sprite m_sprite;
};

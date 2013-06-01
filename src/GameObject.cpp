//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "GameObject.hpp"

GameObject::GameObject() : Drawable(), Solid() {}

void GameObject::setPosition(int x, int y)
{
  Solid::setPosition(x, y);
  m_sprite.setPosition((float)x, (float)y);
}

void GameObject::setPosition(const sf::Vector2i& position)
{
  setPosition(position.x, position.y);
}

const sf::Sprite& GameObject::getSprite() const
{
  return m_sprite;
}

void GameObject::setSprite(const sf::Sprite& sprite)
{
  m_sprite = sprite;
  m_sprite.setPosition((float)getPosition().x, (float)getPosition().y);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_sprite);
}

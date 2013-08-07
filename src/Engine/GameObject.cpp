//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "GameObject.hpp"
#include <iostream>

using namespace e;

GameObject::GameObject(Resources& resources) 
: Object(resources), Drawable(), Solid() {}

void GameObject::moved()
{
  m_sprite.setPosition(getPosition().x, getPosition().y);
}

const sf::Sprite& GameObject::getSprite() const
{
  return m_sprite;
}

void GameObject::setSprite(const sf::Sprite& sprite)
{
  m_sprite = sprite;
  m_sprite.setPosition(getPosition().x, getPosition().y);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_sprite);
}

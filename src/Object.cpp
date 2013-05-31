//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "Object.hpp"

Drawable::Drawable() : sf::Drawable(), m_visible(true) {}

void Drawable::setVisible(bool visible)
{
  m_visible = visible;
}

bool Drawable::isVisible() const
{
  return m_visible;
}


Solid::Solid() : m_solid(true) {}

void Solid::_touch(const Solid& solid)
{
}

void Solid::_untouch(const Solid& solid)
{
}

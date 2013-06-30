//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "Drawable.hpp"

Drawable::Drawable() : sf::Drawable(), m_visible(true), m_depth(0) {}

void Drawable::setVisible(bool visible)
{
  m_visible = visible;
}

bool Drawable::isVisible() const
{
  return m_visible;
}

void Drawable::setDepth(int depth)
{
  m_depth = depth;
}

int Drawable::getDepth() const
{
  return m_depth;
}

///////////////////////////////////////////////:
DrawablePtr::DrawablePtr(Drawable* drawable, int depth)
: m_drawable(drawable), m_depth(depth)
{}

Drawable* DrawablePtr::getDrawable() const
{
  return m_drawable;
}

int DrawablePtr::getDepth() const
{
  return m_depth;
}

bool DrawablePtr::operator<(const DrawablePtr& other) const
{
  return m_depth < other.m_depth;
}

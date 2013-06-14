//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "Object.hpp"
#include <iostream>

Object::Object() : m_resources(nullptr) {}

Object::Object(Resources& resources) : m_resources(&resources) {}

Resources* Object::getResources()
{
  return m_resources;
}

void Object::setResources(Resources& resources)
{
  m_resources = &resources;
}


Drawable::Drawable() : sf::Drawable(), m_visible(true) {}

void Drawable::setVisible(bool visible)
{
  m_visible = visible;
}

bool Drawable::isVisible() const
{
  return m_visible;
}

Resources& ObjectFactory::getResources()
{
  return m_resources;
}

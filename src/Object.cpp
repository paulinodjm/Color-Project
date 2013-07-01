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

const std::string& Object::getName() const
{
  return m_name;
}
  
void Object::setName(const std::string& name)
{
  m_name = name;
}

///////////////////////////////////////////
Resources& ObjectFactory::getResources()
{
  return m_resources;
}

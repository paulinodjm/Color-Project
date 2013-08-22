//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "drawable.h"

DRAWABLE::DRAWABLE() : sf::Drawable(), visible(true), depth(0) {}

void DRAWABLE::SetVisible(bool enable)
{
  visible = enable;
}

bool DRAWABLE::Visible() const
{
  return visible;
}

void DRAWABLE::SetDepth(int d)
{
  depth = d;
}

int DRAWABLE::Depth() const
{
  return depth;
}


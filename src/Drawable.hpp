//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "BaseTypes.hpp"
#include <SFML/Graphics.hpp>
#include "Object.hpp"

/**
* Base class for each visible object.
*/
class Drawable : public sf::Drawable
{
public:

  Drawable();

  void setVisible(bool visible);

  bool isVisible() const;
  
  int getDepth() const;
  
  // changing the depth after the object was added to the drawable list has no effect
  void setDepth(int depht);

private:

  bool m_visible;
  
  int m_depth;
};


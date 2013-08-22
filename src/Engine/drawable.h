//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "BaseTypes.hpp"
#include <SFML/Graphics/Drawable.hpp>

class DRAWABLE : public sf::Drawable
{
public:

  DRAWABLE();

  void SetVisible(bool visible);

  bool Visible() const;
  
  int Depth() const;
  
  // changing the depth after the object was added to the drawable list has no effect
  void SetDepth(int depht);

private:

  bool visible;
  
  int depth;
};


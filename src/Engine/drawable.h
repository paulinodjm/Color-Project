//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/Drawable.hpp>

class DRAWABLE : public sf::Drawable
{
public:

  DRAWABLE();

  void SetVisible(bool visible);

  bool Visible() const;

private:

  bool visible;
};


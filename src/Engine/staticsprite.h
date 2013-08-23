//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <memory>
#include "resources.h"

class CONTENTMANAGER;

class STATICSPRITE : public sf::Drawable, public sf::Transformable
{
public:

  STATICSPRITE();
  
  bool Load(const std::string& filename, CONTENTMANAGER& contentManager);
  bool Save(const std::string& filename);

protected:

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
private:

  sf::Vertex vertex[4];
  std::shared_ptr<TEXTURE> texture;
};

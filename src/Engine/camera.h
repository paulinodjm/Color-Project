//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/View.hpp>

typedef sf::View VIEW;

class CAMERA
{
public:

    /** Called each time to set the game view */
    virtual void calcView(VIEW& view) const = 0;
};

